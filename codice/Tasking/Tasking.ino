//#define _TASK_SLEEP_ON_IDLE_RUN
//#define _TASK_STATUS_REQUEST

#include <TaskScheduler.h>

Scheduler ts;

// globs
int t1, t2;

// Proto
void uno();
void due();
void inframezzo();
void printStatus();

// Tasks (nomi volutamente non coerenti per non dare idee strane su eventuali
// vincoli di nomenclatura)
Task tPari(TASK_SECOND,  // frequenza
           TASK_FOREVER, // span temporale
           uno,         // attività
           &ts,          // aggancio al gestore/scheduler
           true          // abilitazione
);
Task tDispari(500 * TASK_MILLISECOND, TASK_FOREVER, due, &ts, true);

// Special task, print status
Task tPrint(100 * TASK_MILLISECOND, TASK_FOREVER, printStatus, &ts, true);

////////////////////////////////////////////////
void setup() { Serial.begin(921600); }

void loop() {
  ts.execute(); // Only the scheduler should be executed in the loop

  // eventualmente OTA
}

void uno() {
  t1 = 1;

  Serial.printf("1: %d\n", millis());

  // Serial.println(F("1: for con yield"));

  for (int i = 0; i < 100; i++) {
    // Serial.printf("1: %d\n",millis());
    Serial.print(".");
    delay(50); // DA NON FARE NORMALMENTE!!!
    tPari.yield(inframezzo); // Permette esecuzione di altri task... SI FA PER DIRE!!!
  }
  Serial.println();

  // Serial.println(F("1: dopo for"));

  t1 = 0;
}

void inframezzo() {
  Serial.printf("i: %d\n", millis());
  tPari.yield(uno);
}

void due() {
  t2 = 1;

  Serial.printf("2: %d\n", millis());

  t2 = 0;
}

void printStatus() { Serial.printf("+++ t1:%d - t2:%d +++\n", t1, t2); }

// VEDI: https://chatgpt.com/c/67f001c4-43e4-8004-86b9-e56f4f55dc8b
// yield è solo un return con nuova callback
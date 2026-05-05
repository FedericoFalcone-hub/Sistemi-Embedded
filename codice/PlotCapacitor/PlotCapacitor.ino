// *** ASPETTATE A PROVARLO! lo facciamo insieme in lab ***
// nel senso: attenzione alla polarità del condensatore elettrolitico

// elaborazione di https://www.arduino.cc/en/Tutorial/CapacitanceMeter
// ho semplificato l'esempio originale, non usa più due resistenze...

#define ANALOG_PIN A0 // analog pin for measuring capacitor voltage
#define CHARGE_PIN D0 // D0 Wemos (cambiare pin per Arduino, usare ad esempio 8) pin to charge the capacitor - connected to one end of the charging resistor

// in Ohm! (gli zeri sono quelli reali) change this to whatever resistor value
// you are using
#define RESISTOR 14870.0F

#define PLOT
#define CALC

#define DELAY 50
//#define DELAY 10

// per scambiarli nel caso siano invertiti LOW/HIGH
#define CHARGE HIGH
#define DISCHARGE LOW

#define COMPLETELY_DISCHARGED 20 // volendo calcolare anche la rampa di discesa = 648*.37
//#define PARTIALLY_DISCHARGED 238		// 63.2% del PARTIALLY_CHARGED

#define PARTIALLY_CHARGED 648 // 63.2% (RC) => 648
//#define PARTIALLY_CHARGED 950

#define COMPLETELY_CHARGED 1000

// timestamps
unsigned long startCharge;
unsigned long endCharge;

// mode
boolean charge = false;

// V
float v = 0;
float pre_v = 0;

// C
float c = 0;

void charge_mode() {
  // Serial.println("charge");
  charge = true;
  digitalWrite(LED_BUILTIN, LOW); // (LOW is ON on Wemos, HIGH on Arduino)
  digitalWrite(CHARGE_PIN, CHARGE);
  startCharge = millis();
}


// "SINK"!!!
void discharge_mode() {
  // Serial.println("no charge");
  charge = false;
  digitalWrite(LED_BUILTIN, HIGH); // (HIGH is OFF on Wemos, LOW on Arduino)
  digitalWrite(CHARGE_PIN, DISCHARGE);
  endCharge = millis();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(CHARGE_PIN, OUTPUT); // set CHARGE_PIN to output

  Serial.begin(115200);
  Serial.println("booted");
  charge_mode(); // start in "unsafe" mode
}

void voltage() {
  pre_v = v;
  v = analogRead(ANALOG_PIN);
#ifdef PLOT
  Serial.print("Tensione:");
  Serial.print(v);
  Serial.print(",C:");
  Serial.println(c);
#endif
}

/** calcola uF conoscendo il tempo e la resistenza
 *
 *  prima era 'int milliseconds e su piattaforme diverse (wemos vs. arduino)
 * valuta diversamente le espressioni
 *
 *  T=RC diventa:
 *
 *  C(Farad) = T(s)/R(ohm) = (millis/1000)/RESISTOR
 *
 *  in microFarad moltiplico per 1000000:
 *
 *  C(microFarad) = 1000000(millis/1000)/RESISTOR =
 *  = 1000(millis)/RESISTOR
 *
 */
float microFarads(float milliseconds) {
  return 1000.0F * milliseconds / RESISTOR;
}

void loop() {
  delay(DELAY);
  // startTime = millis();

  voltage();

  // agli estremi cambio direzione
  if (v <= COMPLETELY_DISCHARGED) {
    charge_mode();
  }
  if (v >= COMPLETELY_CHARGED) {
    discharge_mode();
  } // questo se c'è CALC non viene mai raggiunto

#ifdef CALC
  // ero in charge, calcolo RC e mi rimetto in scarica
  if (v >= PARTIALLY_CHARGED && charge) {
    discharge_mode();
    c = microFarads(endCharge - startCharge);
    // abs in realtà era inutile, qui dovrebbe sempre essere positiva la diff
  }
#endif
}
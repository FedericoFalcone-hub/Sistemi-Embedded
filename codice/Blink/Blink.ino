const int out = 13;
const int in = 12;
const int interval = 1000;
// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(115200);  //apri seriale baudrate 115200

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(out, OUTPUT);

  pinMode(in, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(out, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  delay(interval);          // wait for a second
  digitalWrite(out, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  delay(interval);          // wait for a second

  int val = digitalRead(in);

  Serial.print("loop");
}

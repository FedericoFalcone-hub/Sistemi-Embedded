int gpio=2;
int count=0;

void IRAM_ATTR  ISR(){
  count++;
}

void setup() {
  Serial.begin(115200);
  pinMode(gpio, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(gpio),  ISR, FALLING);

}

void loop() {
  Serial.print(millis());
  Serial.print(":");
  Serial.println(count);
  delay(500);
}

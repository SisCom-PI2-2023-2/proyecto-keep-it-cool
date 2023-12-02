const int PIN_BUZZER = 0; // D3

void setup() {
  pinMode(PIN_BUZZER, OUTPUT);
}

void loop() {
  digitalWrite(PIN_BUZZER, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(PIN_BUZZER, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}

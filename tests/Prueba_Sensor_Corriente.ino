const int PIN_SENSOR = A0; // Pin D1

void setup() {
  Serial.begin(9600);
  pinMode(PIN_SENSOR, INPUT);
}

void loop() {
    delay(500);
    float voltaje = analogRead(PIN_SENSOR) * (3.3 / 1023.0);
    float corriente = (voltaje - 1.69) / 0.185;
    Serial.print("Corriente leida: ");
    Serial.println(corriente);
    Serial.print("Voltaje leido: ");\
    Serial.println(voltaje);
} 
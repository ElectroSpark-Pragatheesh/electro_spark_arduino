int hallAnalog = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("KY-024 Hall Sensor Analog Test");
}

void loop() {
  int value = analogRead(hallAnalog);
  Serial.print("Magnetic Field Strength: ");
  Serial.println(value);  // Ranges from 0 (strong field) to 1023
  delay(200);
}

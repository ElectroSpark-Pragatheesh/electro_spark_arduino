int ldrPin = 2;
int buzzerPin = 3;

void setup() {
  pinMode(ldrPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int ldrState = digitalRead(ldrPin);
  Serial.println(ldrState); // Check in Serial Monitor

  if (ldrState == HIGH) {
    digitalWrite(buzzerPin, HIGH); // Laser is present → Alarm ON
  } else {
    digitalWrite(buzzerPin, LOW);  // Laser blocked → Alarm OFF
  }

  delay(100);
}

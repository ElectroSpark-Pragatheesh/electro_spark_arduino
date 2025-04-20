#include <Servo.h>

const int waterSensorPin = A0;   // Water sensor to A0
const int servoPin = 3;          // Servo signal to pin 3
const int threshold = 10;       // You can tune this

Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);
  myservo.write(90);  // Start closed
  Serial.println("🚀 System Started – Valve is CLOSED");
}

void loop() {
  int sensorValue = analogRead(waterSensorPin);
  Serial.print("Water Sensor Value: ");
  Serial.println(sensorValue);

  if (sensorValue > threshold) {
    myservo.write(100);  // Stay closed
    Serial.println("🚫 Water detected – Valve CLOSED");
  } else {
    myservo.write(0);   // Open
    Serial.println("💧 No water – Valve OPENED");
  }

  delay(1000);  // 1 second refresh
}
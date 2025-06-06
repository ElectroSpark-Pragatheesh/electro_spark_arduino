#include <Servo.h>

const int trigPin = 3;
const int echoPin = 2;
const int redLed = 6;
const int greenLed = 5;
const int servoPin = 4;

Servo gateServo;  // <-- This line must be outside setup/loop and must end with a semicolon

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  gateServo.attach(servoPin);
  gateServo.write(0); // Start with gate closed
  Serial.begin(9600);
}

void loop() {
  long duration;
  int distance;

  // Measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance < 15) {
    // Car detected
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    gateServo.write(90);     // Open gate
    delay(2000);             // Wait 2 sec
    gateServo.write(0);      // Close gate
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  } else {
    // No car
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
    gateServo.write(0);      // Keep gate closed
  }

  delay(300);
}


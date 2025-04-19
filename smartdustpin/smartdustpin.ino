#include <Servo.h>

Servo lidServo;

const int trigPin = 5;
const int echoPin = 6;

long duration;
int distance;

void setup() {
  lidServo.attach(3);
  lidServo.write(180);  // Fully open on start

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 15) {
    closeLid();       
    delay(3000);       
    openLid();        
    delay(2000);       
  }

  delay(100);
}

void openLid() {
  lidServo.write(180);  // Open wider
  Serial.println("Lid Opened");
}

void closeLid() {
  lidServo.write(0);    // Close
  Serial.println("Lid Closed");
}




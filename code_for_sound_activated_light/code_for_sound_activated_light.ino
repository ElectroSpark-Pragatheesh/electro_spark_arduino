const int micPin = 2;     // DO from mic
const int ledPin = 3;     // LED pin
bool ledState = false;    // Current LED state

void setup() {
  pinMode(micPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int soundState = digitalRead(micPin);
  Serial.print("Sound detected: ");
  Serial.println(soundState);

  if (soundState == HIGH) {
    // Toggle LED
    ledState = !ledState;
    digitalWrite(ledPin, ledState ? HIGH : LOW);
    delay(1000);  // Debounce delay to prevent multiple toggles
  } else {
    delay(100);  // Check again after short time
  }
}

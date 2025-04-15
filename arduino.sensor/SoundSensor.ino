int soundPin = 3;  // Connect DO pin here

void setup() {
  pinMode(soundPin, INPUT);
  Serial.begin(9600);
  Serial.println("Sound Sensor Digital Mode");
}

void loop() {
  int soundState = digitalRead(soundPin);

  if (soundState == HIGH) {
    Serial.println("🤫 Silence...");
  } else {
    Serial.println("🔊 Clap or Loud Sound Detected!");
  }

  delay(300);
}




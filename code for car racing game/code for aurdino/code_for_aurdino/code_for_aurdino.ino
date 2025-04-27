 const int VRX_PIN = A0; // Joystick X-axis
const int VRY_PIN = A1; // Joystick Y-axis
const int SW_PIN = 2;   // Joystick button

void setup() {
  Serial.begin(9600);
  pinMode(SW_PIN, INPUT_PULLUP);
}

void loop() {
  int x = analogRead(VRX_PIN);
  int y = analogRead(VRY_PIN);
  int button = digitalRead(SW_PIN);

  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.println(button);

  delay(50); // Small delay
}
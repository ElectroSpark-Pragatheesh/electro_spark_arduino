#define JOY_X A0
#define JOY_Y A1

#define LED_UP     2
#define LED_DOWN   3
#define LED_LEFT   4
#define LED_RIGHT  5

int center = 512;
int threshold = 100;
String lastDirection = "";

void setup() {
  pinMode(LED_UP, OUTPUT);
  pinMode(LED_DOWN, OUTPUT);
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
  Serial.begin(9600);
  Serial.println("Joystick Direction (Fixed)");
}

void loop() {
  int xVal = analogRead(JOY_X);
  int yVal = analogRead(JOY_Y);
  String direction = "";

  int xDiff = abs(xVal - center);
  int yDiff = abs(yVal - center);

  if (xDiff < threshold && yDiff < threshold) {
    direction = ""; // joystick is centered
  } else if (xDiff > yDiff) {
    // Horizontal move
    if (xVal < center - threshold) direction = "Right"; // flipped!
    else if (xVal > center + threshold) direction = "Left"; // flipped!
  } else {
    // Vertical move
    if (yVal < center - threshold) direction = "Down"; // flipped!
    else if (yVal > center + threshold) direction = "Up"; // flipped!
  }

  if (direction != lastDirection) {
    Serial.println(direction);
    lastDirection = direction;
  }

  // LED control
  digitalWrite(LED_UP,    direction == "Up");
  digitalWrite(LED_DOWN,  direction == "Down");
  digitalWrite(LED_LEFT,  direction == "Left");
  digitalWrite(LED_RIGHT, direction == "Right");

  if (direction == "") {
    digitalWrite(LED_UP, LOW);
    digitalWrite(LED_DOWN, LOW);
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_RIGHT, LOW);
    lastDirection = "";
  }

  delay(100);
}

th const int buttonPins[] = {2, 4, 6, 8};    // Buttons
const int ledPins[]    = {3, 5, 7, 9};    // LEDs
const int feedbackLED  = 10;             // Feedback LED

int sequence[100];
int level = 0;
bool gameOverFlag = false;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(feedbackLED, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  Serial.println("Memory Game Ready!");
}

void loop() {
  if (gameOverFlag) {
    // Game is over, keep feedback LED on and do nothing
    digitalWrite(feedbackLED, HIGH);
    return;
  }

  sequence[level] = random(0, 4);
  delay(1000);
  playSequence();

  if (!getPlayerInput()) {
    triggerGameOver();
  } else {
    level++;
  }
}

void playSequence() {
  for (int i = 0; i <= level; i++) {
    int index = sequence[i];
    digitalWrite(ledPins[index], HIGH);
    delay(400);
    digitalWrite(ledPins[index], LOW);
    delay(200);
  }
}

bool getPlayerInput() {
  for (int i = 0; i <= level; i++) {
    bool correct = false;
    while (!correct) {
      for (int j = 0; j < 4; j++) {
        if (digitalRead(buttonPins[j]) == LOW) {
          digitalWrite(ledPins[j], HIGH);
          delay(100);
          digitalWrite(feedbackLED, HIGH);
          delay(200);
          digitalWrite(ledPins[j], LOW);
          delay(100);
          digitalWrite(feedbackLED, LOW);
          delay(100);
          while (digitalRead(buttonPins[j]) == LOW); // Wait for release

          if (j == sequence[i]) {
            correct = true;
          } else {
            return false;
          }
        }
      }
    }
  }
  return true;
}

void triggerGameOver() {
  Serial.println("Game Over!");
  
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) digitalWrite(ledPins[j], HIGH);
    digitalWrite(feedbackLED, HIGH);
    delay(300);
    for (int j = 0; j < 4; j++) digitalWrite(ledPins[j], LOW);
    digitalWrite(feedbackLED, LOW);
    delay(300);
  }

  // FINAL STEP: Turn ON feedback LED and set gameOverFlag
  digitalWrite(feedbackLED, HIGH);
  for (int j = 0; j < 4; j++) digitalWrite(ledPins[j], LOW);
  gameOverFlag = true; // Prevent further code from running
}


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SENSOR_PIN 2  // Vibration sensor OUT → D2
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int lastState = HIGH;
unsigned long lastShakeTime = 0;
unsigned long cooldown = 1000; // 1s delay between shakes

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600);
  while (!Serial);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED NOT FOUND");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 25);
  display.println("Shake to Roll 🎲");
  display.display();

  randomSeed(analogRead(A0)); // Better randomness
}

void loop() {
  int currentState = digitalRead(SENSOR_PIN);

  // Trigger only on falling edge & after cooldown
  if (currentState == LOW && lastState == HIGH && (millis() - lastShakeTime > cooldown)) {
    lastShakeTime = millis();
    rollDice();
  }

  lastState = currentState;
}

void rollDice() {
  // Dice roll animation
  for (int i = 0; i < 10; i++) {
    drawRandomDots();
    delay(random(80, 150));
  }

  // Final number
  int finalNumber = random(1, 7);
  drawDiceFace(finalNumber);

  delay(2000); // Show result for 2 seconds

  // Reset screen
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 25);
  display.println("Shake to Roll 🎲");
  display.display();
}

void drawRandomDots() {
  display.clearDisplay();
  display.drawRoundRect(32, 0, 64, 64, 5, SSD1306_WHITE);

  for (int i = 0; i < random(1, 7); i++) {
    int x = random(40, 88);
    int y = random(8, 56);
    display.fillCircle(x, y, 3, SSD1306_WHITE);
  }

  display.display();
}

void drawDiceFace(int num) {
  display.clearDisplay();
  display.drawRoundRect(32, 0, 64, 64, 5, SSD1306_WHITE);

  int cx = 64, cy = 32, d = 12;

  auto dot = [&](int dx, int dy) {
    display.fillCircle(cx + dx, cy + dy, 3, SSD1306_WHITE);
  };

  switch (num) {
    case 1: dot(0, 0); break;
    case 2: dot(-d, -d); dot(d, d); break;
    case 3: dot(-d, -d); dot(0, 0); dot(d, d); break;
    case 4: dot(-d, -d); dot(d, -d); dot(-d, d); dot(d, d); break;
    case 5: dot(-d, -d); dot(d, -d); dot(0, 0); dot(-d, d); dot(d, d); break;
    case 6: dot(-d, -d); dot(d, -d); dot(-d, 0); dot(d, 0); dot(-d, d); dot(d, d); break;
  }

  display.display();
}

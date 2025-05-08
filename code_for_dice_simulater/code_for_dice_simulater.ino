#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUTTON_PIN 2
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int lastButtonState = HIGH;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 25);
  display.println("Press to roll 🎲");
  display.display();

  pinMode(A0, INPUT);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && buttonState == LOW) {
    rollDice();
    delay(300);  // Debounce
  }

  lastButtonState = buttonState;
}

void rollDice() {
  randomSeed(analogRead(A0));

  // Show messy random dots as animation
  for (int i = 0; i < 10; i++) {
    drawRandomDots();
    delay(random(80, 150));
  }

  // Final proper dice face
  int finalNumber = random(1, 7);
  drawDiceFace(finalNumber);
}

void drawRandomDots() {
  display.clearDisplay();
  display.drawRoundRect(32, 0, 64, 64, 5, WHITE);

  for (int i = 0; i < random(1, 7); i++) {
    int x = random(40, 88);
    int y = random(8, 56);
    display.fillCircle(x, y, 3, WHITE);
  }

  display.display();
}

void drawDiceFace(int num) {
  display.clearDisplay();
  display.drawRoundRect(32, 0, 64, 64, 5, WHITE);

  int cx = 64, cy = 32, d = 12;

  auto dot = [&](int dx, int dy) {
    display.fillCircle(cx + dx, cy + dy, 3, WHITE);
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

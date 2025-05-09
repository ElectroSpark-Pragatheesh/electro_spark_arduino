#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buttonPin = 2;
String symbols[] = {"CH", "LE", "BE"};  // CH=Cherry, LE=Lemon, BE=Bell
int result[3];

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 25);
  display.print("Press to SPIN");
  display.display();
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    while (digitalRead(buttonPin) == LOW);  // Wait for release
    delay(50); // debounce

    display.clearDisplay();
    display.setCursor(30, 0);
    display.setTextSize(1);
    display.print("Spinning...");
    display.display();
    delay(1000);

    // Generate random symbols
    for (int i = 0; i < 3; i++) {
      result[i] = random(0, 3); // 0 to 2
    }

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(10, 10);
    display.print(symbols[result[0]]);
    display.setCursor(50, 10);
    display.print(symbols[result[1]]);
    display.setCursor(90, 10);
    display.print(symbols[result[2]]);

    display.setTextSize(1);
    display.setCursor(20, 45);
    if (result[0] == result[1] && result[1] == result[2]) {
      display.print("YOU WON!");
    } else {
      display.print("YOU LOST!");
    }
    display.display();

    delay(3000);

    // Reset
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(20, 25);
    display.print("Press to SPIN");
    display.display();
  }
}
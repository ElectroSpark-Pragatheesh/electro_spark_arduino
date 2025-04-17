#include <Adafruit_NeoPixel.h>

#define LED_PIN         2
#define NUMPIXELS       18
#define BRIGHTNESS_POT  A0
#define SPEED_POT       A1

Adafruit_NeoPixel strip(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.clear();
  strip.show();
  pinMode(BRIGHTNESS_POT, INPUT);
  pinMode(SPEED_POT, INPUT);
}

void loop() {
  int brightnessVal = analogRead(BRIGHTNESS_POT);
  int speedVal = analogRead(SPEED_POT);
  int brightness = map(brightnessVal, 0, 1023, 0, 255);
  int delayTime = map(speedVal, 0, 1023, 20, 300);

  strip.setBrightness(brightness);

  // Colorful spinning pattern
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.clear();
    uint8_t r = random(50, 255);
    uint8_t g = random(50, 255);
    uint8_t b = random(50, 255);
    strip.setPixelColor(i, strip.Color(r, g, b));
    strip.show();
    delay(delayTime);
  }
}
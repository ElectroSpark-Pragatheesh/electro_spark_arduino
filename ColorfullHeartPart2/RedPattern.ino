#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
#define NUMPIXELS 18
#define BRIGHTNESS_POT A0
#define SPEED_POT A1

Adafruit_NeoPixel strip(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.clear();
  strip.show();
}

void loop() {
  // Read live values from both potentiometers
  int brightnessVal = analogRead(BRIGHTNESS_POT);  // 0–1023
  int speedVal = analogRead(SPEED_POT);            // 0–1023

  // Map values to usable ranges
  int brightness = map(brightnessVal, 0, 1023, 0, 255);
  int delayTime = map(speedVal, 0, 1023, 20, 300); // Lower = faster

  // Set brightness
  strip.setBrightness(brightness);

  // Spinning pattern
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.clear();
    strip.setPixelColor(i, strip.Color(255, 0, 0)); // Red LED spins
    strip.show();

    // Read updated values *while spinning*
    brightnessVal = analogRead(BRIGHTNESS_POT);
    speedVal = analogRead(SPEED_POT);
    brightness = map(brightnessVal, 0, 1023, 0, 255);
    delayTime = map(speedVal, 0, 1023, 20, 300);
    strip.setBrightness(brightness);

    delay(delayTime);
  }
}

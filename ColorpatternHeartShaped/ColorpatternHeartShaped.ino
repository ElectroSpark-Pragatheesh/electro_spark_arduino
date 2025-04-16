#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
#define NUMPIXELS 18

Adafruit_NeoPixel strip(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

int currentPattern = 0;
unsigned long lastSwitch = 0;
unsigned long patternInterval = 6000;  // Switch pattern every 6 seconds

void setup() {
  strip.begin();
  strip.clear();
  strip.show();
  randomSeed(analogRead(0)); // For sparkle randomness
}

void loop() {
  if (millis() - lastSwitch > patternInterval) {
    currentPattern = (currentPattern + 1) % 8;
    lastSwitch = millis();
  }

  switch (currentPattern) {
    case 0: spinningDot(); break;
    case 1: rainbowSpin(); break;
    case 2: heartbeatPulse(); break;
    case 3: sparkleTwinkle(); break;
    case 4: fullColorWipe(); break;
    case 5: dualSpin(); break;
    case 6: breatheEffect(); break;
    case 7: waveChase(); break;
  }
}

// 🔴 Pattern 1: Spinning Dot
void spinningDot() {
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.clear();
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
    delay(80);
  }
}

// 🌈 Pattern 2: Rainbow Spin
void rainbowSpin() {
  static uint16_t j = 0;
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.ColorHSV((j + i * 65536L / NUMPIXELS) % 65536));
  }
  strip.show();
  delay(50);
  j += 256;
}

// 💓 Pattern 3: Heartbeat Pulse
void heartbeatPulse() {
  uint32_t color = strip.Color(255, 0, 0);
  for (int b = 0; b <= 255; b += 5) {
    strip.setBrightness(b);
    setAll(color);
    strip.show();
    delay(5);
  }
  for (int b = 255; b >= 0; b -= 5) {
    strip.setBrightness(b);
    setAll(color);
    strip.show();
    delay(5);
  }
}

// ✨ Pattern 4: Sparkle Twinkle
void sparkleTwinkle() {
  strip.clear();
  int i = random(NUMPIXELS);
  strip.setPixelColor(i, strip.Color(255, 255, 255));
  strip.show();
  delay(100);
}

// 🌈 Pattern 5: Full Color Wipe
void fullColorWipe() {
  static uint32_t colors[] = {
    strip.Color(255, 0, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 0, 255),
    strip.Color(255, 255, 0),
    strip.Color(0, 255, 255),
    strip.Color(255, 0, 255)
  };
  static int colorIndex = 0;

  setAll(colors[colorIndex]);
  strip.show();
  delay(400);
  colorIndex = (colorIndex + 1) % 6;
}

// 🔁 Pattern 6: Opposite Dual Spin
void dualSpin() {
  for (int i = 0; i < NUMPIXELS / 2; i++) {
    strip.clear();
    strip.setPixelColor(i, strip.Color(0, 255, 255));
    strip.setPixelColor(NUMPIXELS - 1 - i, strip.Color(0, 255, 255));
    strip.show();
    delay(100);
  }
}

// 🌬️ Pattern 7: Breathing Blue Effect
void breatheEffect() {
  uint32_t color = strip.Color(0, 0, 255);
  for (int b = 0; b <= 255; b += 5) {
    strip.setBrightness(b);
    setAll(color);
    strip.show();
    delay(8);
  }
  for (int b = 255; b >= 0; b -= 5) {
    strip.setBrightness(b);
    setAll(color);
    strip.show();
    delay(8);
  }
}

// 🌀 Pattern 8: Wave Chase
void waveChase() {
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.clear();
    strip.setPixelColor(i, strip.Color(255, 105, 180));
    strip.setPixelColor((i + 1) % NUMPIXELS, strip.Color(255, 255, 255));
    strip.setPixelColor((i + 2) % NUMPIXELS, strip.Color(255, 105, 180));
    strip.show();
    delay(80);
  }
}

// Utility: Set all LEDs to same color
void setAll(uint32_t color) {
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, color);
  }
}

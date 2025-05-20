#include <Keypad.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // Confirmed working I2C address

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {6, 7, 8, 9};    // R1–R4
byte colPins[COLS] = {5, 4, 3, 2};    // C1–C4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Servo setup
Servo myServo;
const int servoPin = A3;

// Password logic
String enteredCode = "";
String correctCode = 1998522";
bool isUnlocked = false;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(0); // Start at 0°

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  lcd.setCursor(0, 1);
  lcd.print("Enter Code:");
}

void loop() {
  if (isUnlocked) return;

  char key = keypad.getKey();
  if (key) {
    enteredCode += key;

    Serial.print("Key: ");
    Serial.println(key);
    Serial.print("Current Code: ");
    Serial.println(enteredCode);

    // Show entered digits
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Code: ");
    lcd.setCursor(6, 0);
    lcd.print(enteredCode);

    if (enteredCode.length() == 7) {
      if (enteredCode == correctCode) {
        unlock();
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Access Denied");
        Serial.println("❌ Wrong Code ❌");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Try Again");
      }
      enteredCode = "";
    }
  }
}

void unlock() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Access Granted");
  Serial.println("✅ Correct Code ✅");

  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);
    delay(50);
  }

  lcd.setCursor(0, 1);
  lcd.print("System Locked 🔒");
  isUnlocked = true;
}
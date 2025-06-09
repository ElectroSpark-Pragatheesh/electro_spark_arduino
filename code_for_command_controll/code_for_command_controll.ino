#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

const int redPin = 3;
const int greenPin = 4;
const int whitePin = 2;
const int servoPin = 5;

String input = "";
bool spinning = false; // for servo loop

void setup() {
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);

 
  pinMode(greenPin, OUTPUT);
  pinMode(whitePin, OUTPUT);

  myServo.attach(servoPin);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Ready for cmds");

  Serial.println("Type: red / white / green / spin / stop / off / show / print xyz");
}

void loop() {
  // Keep spinning servo if active
  if (spinning) {
    myServo.write(0);
    delay(500);
    myServo.write(180);
    delay(500);
  }

  if (Serial.available()) {
    input = Serial.readStringUntil('\n');
    input.trim();

    // LED controls
    if (input == "red") {
      digitalWrite(redPin, HIGH);
      lcd.clear(); lcd.print("Red LED ON");
    } 
    else if (input == "green") {
      digitalWrite(greenPin, HIGH);
      lcd.clear(); lcd.print("Green LED ON");
    } 
    else if (input == "white") {
      digitalWrite(whitePin, HIGH);
      lcd.clear(); lcd.print("White LED ON");
    }

    // Start spinning
    else if (input == "spin") {
      spinning = true;
      lcd.clear(); lcd.print("Servo Spinning");
    }

    // Stop spinning
    else if (input == "stop") {
      spinning = false;
      myServo.write(90);  // Neutral position
      lcd.clear(); lcd.print("Servo Stopped");
    }

    // Turn off all LEDs
    else if (input == "off") {
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(whitePin, LOW);
      lcd.clear(); lcd.print("All LEDs OFF");
    }

    // Show LED status
    else if (input == "show") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("R:");
      lcd.print(digitalRead(redPin));
      lcd.print(" G:");
      lcd.print(digitalRead(greenPin));
      lcd.setCursor(0, 1);
      lcd.print("W:");
      lcd.print(digitalRead(whitePin));
    }

    // Print to LCD: e.g. "print Hello"
    else if (input.startsWith("print ")) {
      String msg = input.substring(6);  // Get text after "print "
      lcd.clear();
      lcd.print(msg);
    }

    // Invalid input
    else {
      lcd.clear();
      lcd.print("Invalid cmd");
    }
  }
}

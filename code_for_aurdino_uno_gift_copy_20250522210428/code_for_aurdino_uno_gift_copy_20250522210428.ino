#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// RTC setup (DAT, CLK, RST)
ThreeWire myWire(7, 6, 8);
RtcDS1302<ThreeWire> Rtc(myWire);

// Button pins
#define BTN_SET 2
#define BTN_MODE 3
#define BTN_INC 4
#define BTN_DEC 5

// Variables
bool settingMode = false;
int settingField = 0;
int setHour, setMinute, setDay, setMonth, setYear;

const char* daysOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void setup() {
  pinMode(BTN_SET, INPUT_PULLUP);
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_INC, INPUT_PULLUP);
  pinMode(BTN_DEC, INPUT_PULLUP);

  Serial.begin(9600);
  Rtc.Begin();

  if (!Rtc.IsDateTimeValid()) {
    Serial.println("RTC invalid, setting compile time.");
    Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
  }

  if (Rtc.GetIsWriteProtected()) {
    Rtc.SetIsWriteProtected(false);
  }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  if (digitalRead(BTN_SET) == LOW) {
    delay(300);
    settingMode = !settingMode;
    if (settingMode) {
      RtcDateTime now = Rtc.GetDateTime();
      setHour = now.Hour();
      setMinute = now.Minute();
      setDay = now.Day();
      setMonth = now.Month();
      setYear = now.Year();
    } else {
      RtcDateTime newTime(setYear, setMonth, setDay, setHour, setMinute, 0);
      Rtc.SetDateTime(newTime);
    }
  }

  if (settingMode) {
    if (digitalRead(BTN_MODE) == LOW) {
      delay(300);
      settingField = (settingField + 1) % 5;
    }

    if (digitalRead(BTN_INC) == LOW) {
      delay(200);
      switch (settingField) {
        case 0: setHour = (setHour + 1) % 24; break;
        case 1: setMinute = (setMinute + 1) % 60; break;
        case 2: setDay = (setDay % 31) + 1; break;
        case 3: setMonth = (setMonth % 12) + 1; break;
        case 4: setYear = (setYear < 2099) ? setYear + 1 : 2000; break;
      }
    }

    if (digitalRead(BTN_DEC) == LOW) {
      delay(200);
      switch (settingField) {
        case 0: setHour = (setHour + 23) % 24; break;
        case 1: setMinute = (setMinute + 59) % 60; break;
        case 2: setDay = (setDay + 29) % 31 + 1; break;
        case 3: setMonth = (setMonth + 10) % 12 + 1; break;
        case 4: setYear = (setYear > 2000) ? setYear - 1 : 2099; break;
      }
    }

    // Show settings
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Set Time & Date");

    display.setCursor(0, 15);
    display.print("Time: ");
    print2(setHour); display.print(":"); print2(setMinute);

    display.setCursor(0, 30);
    display.print("Date: ");
    print2(setDay); display.print("/");
    print2(setMonth); display.print("/");
    display.print(setYear);

    display.setCursor(0, 45);
    display.print("Editing: ");
    display.print(settingField == 0 ? "Hour" :
                  settingField == 1 ? "Minute" :
                  settingField == 2 ? "Day" :
                  settingField == 3 ? "Month" : "Year");
    display.display();
  } else {
    RtcDateTime now = Rtc.GetDateTime();

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    print2(now.Hour()); display.print(":");
    print2(now.Minute()); display.print(":");
    print2(now.Second());

    display.setTextSize(1);
    display.setCursor(0, 30);
    display.print("Date: ");
    print2(now.Day()); display.print("/");
    print2(now.Month()); display.print("/");
    display.print(now.Year());

    display.setCursor(0, 45);
    display.print("Day: ");
    display.print(daysOfWeek[now.DayOfWeek() % 7]);

    display.display();
  }

  delay(100);
}

void print2(int number) {
  if (number < 10) display.print("0");
  display.print(number);
}

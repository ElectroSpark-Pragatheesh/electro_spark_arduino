#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

const int nextButton = 3;
const int volUpButton = 4;
const int volDownButton = 5;

void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);

  pinMode(nextButton, INPUT_PULLUP);
  pinMode(volUpButton, INPUT_PULLUP);
  pinMode(volDownButton, INPUT_PULLUP);

  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("Unable to begin:");
    while (true);
  }

  Serial.println("DFPlayer Mini online.");

  myDFPlayer.volume(20); // Set initial volume
  myDFPlayer.play(1);    // Start playing song 0001.mp3
}

void loop()
{
  if (digitalRead(nextButton) == LOW) {
    myDFPlayer.next(); // Immediately go to next song
    delay(500); // Debounce delay
  }

  if (digitalRead(volUpButton) == LOW) {
    myDFPlayer.volumeUp(); // Increase volume
    delay(300);
  }

  if (digitalRead(volDownButton) == LOW) {
    myDFPlayer.volumeDown(); // Decrease volume
    delay(300);
  }
}
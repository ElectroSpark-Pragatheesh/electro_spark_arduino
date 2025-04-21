#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySerial(10, 11); // RX, TX (use Pins 10 and 11 for communication)
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  Serial.begin(9600); // Debugging
  mySerial.begin(9600); // DFPlayer communication
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer Mini initialization failed!");
    while (true);
  }
  Serial.println("DFPlayer Mini ready.");
  
  myDFPlayer.volume(30); // Set volume (0 to 30)
  myDFPlayer.play(1);    // Play the first track (0001.mp3)
}

void loop() {
  // Do nothing. The audio file will play automatically.
}

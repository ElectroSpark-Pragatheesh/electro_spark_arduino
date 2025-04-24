#include <IRremote.h>

const int RECV_PIN = 2; // IR sensor signal pin

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);  // Start IR receiver
  Serial.println("IR HEX Reader Ready. Press any remote button...");
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("HEX: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX); // Show only the command part
    IrReceiver.resume(); // Ready to receive the next signal
  }
}

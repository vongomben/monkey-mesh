// monkey mesh experiments
//
// the device is a Xiao SAMD21 and 
// is receiving via serial from 
// a Seeed Xiao ESP32S2 Meshtastic kit
// and sending back the message

#include "SoftwareSerial.h"

void setup() {
  Serial.begin(19200);     // USB for debugging
  Serial1.begin(19200);    // Hardware port for receiving from another board (if used)

  mySerial.begin(19200);    // Port for the printer

  Serial.println("Ready. Waiting for text on Serial1 for upside-down printing...");
}

void loop() {
  // Receive from Serial1 (e.g., another connected board)
  if (Serial1.available()) {
    String input = Serial1.readStringUntil('\n'); // Reads a line

    Serial1.println(input); // echobot
  }
}

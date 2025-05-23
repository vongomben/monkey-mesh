// monkey mesh experiments
//
// the device is a Xiao SAMD21 and 
// is receiving via serial from 
// a Seeed Xiao ESP32S2 Meshtastic kit
// and sending back the message

//#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"

//#define TX_PIN 4  // SAMD21 → RX della stampante
//#define RX_PIN 5  // Stampante TX → SAMD21 (opzionale)

//SoftwareSerial mySerial(RX_PIN, TX_PIN);  // Porta stampante
//Adafruit_Thermal printer(&mySerial);

String cleanInput = "";
String rawInput = "";

void setup() {
  Serial.begin(19200);     // USB for debugging
  Serial1.begin(19200);    // Hardware port for receiving from another board (if used)

  mySerial.begin(19200);     // Port for the printer (if there is a printer)
  //printer.begin();
  //printer.upsideDownOn();    // Modalità testo capovolto

  Serial.println("Ready. Waiting for Serial1 inputs...");
}

void loop() {
  while (Serial1.available()) {
    char c = Serial1.read();

    if (c == '\n') {
      rawInput.trim(); // this takes out spaces and \r

      // Extract only the part after the first ':'
      int sep = rawInput.indexOf(':');
      String payload = (sep >= 0) ? rawInput.substring(sep + 1) : rawInput;
      payload.trim(); // Remove any spaces

      // Debug
      Serial.println("Received: [" + payload + "]");

      // commant "/test"

      if (payload == "/test") {
        Serial.println("Command test received");
        
        // do some testing

      } else if (payload == "/rest") {
        Serial.println("Command test received");
        
        // do some resting
     
      } else if (payload.length() > 0) {
        printer.println(payload);
        Serial.println("Printed: " + payload);
        Serial1.println(payload); // echo
      }

      rawInput = ""; // Reset buffer
    }

    // Printable characters only (ASCII 32 to 126)
    else if (c >= 32 && c <= 126) { 
      rawInput += c;
    }
    //  Otherwise, ignore the character
  }
}
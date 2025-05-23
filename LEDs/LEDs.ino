// monkey mesh experiments
// riceve da ESP32S2 Meshtastic via Serial1
// stampa su termica via SoftwareSerial
// comando "/test" è gestito separatamente

#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN 0

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


#define TX_PIN 4  // SAMD21 → RX della stampante
#define RX_PIN 5  // Stampante TX → SAMD21 (opzionale)

SoftwareSerial mySerial(RX_PIN, TX_PIN);  // Porta stampante
Adafruit_Thermal printer(&mySerial);

String cleanInput = "";
String rawInput = "";

void setup() {
  Serial.begin(19200);   // USB debug
  Serial1.begin(19200);  // Ricezione da ESP32/altro nodo

  mySerial.begin(19200);  // Stampante
  printer.begin();
  printer.upsideDownOn();  // Modalità testo capovolto

  Serial.println("Pronto. Attendo input su Serial1...");

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();             // Turn OFF all pixels ASAP
  strip.setBrightness(50);  // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {
  while (Serial1.available()) {
    char c = Serial1.read();

    if (c == '\n') {
      rawInput.trim();  // Rimuove spazi e \r

      // Estrai solo la parte dopo il primo ':'
      int sep = rawInput.indexOf(':');
      String payload = (sep >= 0) ? rawInput.substring(sep + 1) : rawInput;
      payload.trim();  // Rimuovi eventuali spazi

      // Debug
      Serial.println("Ricevuto: [" + payload + "]");

      if (payload == "/red") {
        Serial.println("Command received");
        colorWipe(strip.Color(255, 0, 0), 50);  // Red
        // Non stampare nulla
      } else if (payload.length() > 0) {
        printer.println(payload);
        Serial.println("Stampato: " + payload);
        Serial1.println(payload);  // echo
          colorWipe(strip.Color(0,   0,   0), 50); // black
      }

      rawInput = "";  // Reset buffer
    }

    // Solo caratteri stampabili (ASCII da 32 a 126)
    else if (c >= 32 && c <= 126) {
      rawInput += c;
    }
    // Altrimenti ignora il carattere
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
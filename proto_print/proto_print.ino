// monkey mesh experiments (on XIAO ESP32 S3)
// receives data from meshtastic device
// prints on thermal printer using Serial2

#include <Meshtastic.h>
#include "Adafruit_Thermal.h"

Adafruit_Thermal printer(&Serial2);

// Pins used on the Xiao ESP32S3
#define SERIAL_RX_PIN 44  // GPIO44 (RX)
#define SERIAL_TX_PIN 43  // GPIO43 (TX)
#define BAUD_RATE 19200

#define SEND_PERIOD 300  // (optional) send every 300 seconds

uint32_t next_send_time = 0;
bool not_yet_connected = true;

// Callback when connected to a Meshtastic node
void connected_callback(mt_node_t* node, mt_nr_progress_t progress) {
  if (not_yet_connected)
    Serial.println("✅ Connected to Meshtastic device!");
  not_yet_connected = false;
}

// Callback when a text message is received
void text_message_callback(uint32_t from, uint32_t to, uint8_t channel, const char* text) {

  Serial.print("📩 Received message:\n From: ");
  Serial.print(from);
  Serial.print(" → To: ");
  Serial.print(to);
  Serial.print(" | Channel: ");
  Serial.print(channel);
  Serial.print(" | Text: ");
  Serial.println(text);

  printer.print(from);
  printer.print(" → To: ");
  Serial.print(to);
  printer.print(" | Channel: ");
  printer.print(channel);
  printer.print(" | Text: ");
  printer.println(text);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("🔌 Starting Meshtastic read via Serial1 (UART)");
  printer.print(" 🐵 Starting MeshtMonkey");
  // Initialize serial communication with the Meshtastic device
  mt_serial_init(SERIAL_RX_PIN, SERIAL_TX_PIN, BAUD_RATE);
  mt_set_debug(true);  // set to true for detailed output

  // Request initial node info from the Meshtastic device
  mt_request_node_report(connected_callback);

  // Register callback for received messages
  set_text_message_callback(text_message_callback);

  // Inizialize Serial2 (UART2)  on custom pins
  Serial2.begin(19200, SERIAL_8N1, 5, 6);  //8 , 9 <-- BE CAREFUL about the cabling, I inverted those from the previous example

 // Serial2.begin(19200, SERIAL_8N1, 9, 8);  //8 , 9 <-- BE CAREFUL about the cabling, I inverted those from the previous example
  Serial.println("Serial2 initialised su TX=10, RX=9");

  printer.begin();
  printer.upsideDownOn();
  Serial.println("Ready. Send Data to be printed:");
}

void loop() {
  uint32_t now = millis();
  bool can_send = mt_loop(now);  // processes incoming messages

  // (optional) Send a message every few seconds
  if (can_send && now >= next_send_time) {
    uint32_t dest = BROADCAST_ADDR;
    uint8_t channel = 0;
    mt_send_text("Hello from Xiao ESP32!", dest, channel);
    next_send_time = now + SEND_PERIOD * 1000;
  }
}

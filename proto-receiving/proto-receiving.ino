#include <Meshtastic.h>

// Pins used on the Xiao ESP32S3
#define SERIAL_RX_PIN 44   // GPIO44 (RX)
#define SERIAL_TX_PIN 43   // GPIO43 (TX)
#define BAUD_RATE 19200

#define SEND_PERIOD 300  // (optional) send every 300 seconds

uint32_t next_send_time = 0;
bool not_yet_connected = true;

// Callback when connected to a Meshtastic node
void connected_callback(mt_node_t *node, mt_nr_progress_t progress) {
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
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("🔌 Starting Meshtastic read via Serial1 (UART)");

  // Initialize serial communication with the Meshtastic device
  mt_serial_init(SERIAL_RX_PIN, SERIAL_TX_PIN, BAUD_RATE);
  mt_set_debug(true);  // set to true for detailed output

  // Request initial node info from the Meshtastic device
  mt_request_node_report(connected_callback);

  // Register callback for received messages
  set_text_message_callback(text_message_callback);
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

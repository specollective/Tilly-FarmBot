#include <Arduino.h>
#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "Matt's_Wifi";
const char* password = "McPassword#1";

WiFiServer server(80);  // Set up the TCP server on port 80

void setup() {
  // Start Serial1 for ESP32 <-> Arduino communication
  Serial1.begin(9600, SERIAL_8N1, 16, 17);  // RX=16, TX=17 for ESP32
  
  // Start Serial for debugging (optional)
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the TCP server
  server.begin();
  Serial.println("TCP server started");
}

void loop() {
  // Check if a client is connected
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected");

    // Check if the client is still connected
    while (client.connected()) {
      // Check if the client sent data
      if (client.available()) {
        String message = client.readStringUntil('\n');  // Read TCP message
        Serial.print("Received from client: ");
        Serial.println(message);

        // Send the message to the Arduino over Serial1
        Serial1.print(message + "\n");  // Forward to Arduino

        // Optionally, respond to the client (acknowledgment)
        client.print("Message sent to Arduino: " + message + "\n");
      }
    }

    // Close the connection when the client disconnects
    client.stop();
    Serial.println("Client disconnected");
  }
}
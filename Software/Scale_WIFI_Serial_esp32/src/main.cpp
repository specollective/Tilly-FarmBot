#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "Matt's_Wifi";
const char* password = "McPassword#1";

WiFiServer server(80);  // Port 80 or any other port

void setup() {
  // Start Serial for debugging purposes
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // WiFi connected
  Serial.println("Connected to WiFi");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());  // Print ESP32 IP address

  // Start the TCP server
  server.begin();
  Serial.println("TCP server started");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("Client connected");

    // Check if the client is still connected
    while (client.connected()) {
      // Check if the client has sent data
      if (client.available()) {
        String clientMessage = client.readStringUntil('\n');
        Serial.print("Received from client: ");
        Serial.println(clientMessage);
      }

      // Send a message to the client
      String serverMessage = "Hello from ESP32!\n";
      client.print(serverMessage); // Send message to the client
      Serial.println("Message sent to client");

      delay(2000);  // Wait 2 seconds before sending again
    }

    // If client disconnects, close the connection
    client.stop();
    Serial.println("Client disconnected");
  }
}
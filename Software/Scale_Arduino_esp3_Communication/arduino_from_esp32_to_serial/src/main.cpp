#include <Arduino.h>
#include <SoftwareSerial.h>

// Define the RX and TX pins for communication with the ESP32
SoftwareSerial espSerial(6, 7);  // RX=6, TX=7

void setup() {
  // Start Serial for communication with ESP32
  espSerial.begin(9600);
  Serial.begin(9600);
  Serial.print("arduino on");
}

void loop() {
  // Check if data is available from the ESP32 (via SoftwareSerial)
  if (espSerial.available()) {
    String message = espSerial.readStringUntil('\n');
    Serial.print("Arduino received: ");
    Serial.println(message);
  }

  // Optionally, you can send data back to the ESP32 from the Arduino
  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    espSerial.print(message + "received at arduino");
  }
}
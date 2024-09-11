#include <Arduino.h>

const int motor1_in1 = 28;
const int motor1_in2 = 29;
const int motor2_in1 = 30;
const int motor2_in2 = 31;
const int motor3_in1 = 32;
const int motor3_in2 = 33;

// Function declarations
void motorControl(bool motor1_dir, bool motor2_dir, bool motor3_dir);
void motorControlStop();

void setup() {
  // Set all motor pins as outputs
  pinMode(motor1_in1, OUTPUT);
  pinMode(motor1_in2, OUTPUT);
  pinMode(motor2_in1, OUTPUT);
  pinMode(motor2_in2, OUTPUT);
  pinMode(motor3_in1, OUTPUT);
  pinMode(motor3_in2, OUTPUT);
  
  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 'w': // Up arrow key: All motors in one direction
        motorControl(true, true, true);
        break;
      case 's': // Down arrow key: All motors in opposite direction
        motorControl(false, false, false);
        break;
      case 'a': // Left arrow key: Motor 1 CW, Motor 2 & 3 CCW
        motorControl(true, false, false);
        break;
      case 'd': // Right arrow key: Motor 1 CCW, Motor 2 & 3 CW
        motorControl(false, true, true);
        break;
      case 'x': // Stop all motors
        motorControlStop();
        break;
    }
  }
}

// Function definitions
void motorControl(bool motor1_dir, bool motor2_dir, bool motor3_dir) {
  digitalWrite(motor1_in1, motor1_dir ? HIGH : LOW);
  digitalWrite(motor1_in2, motor1_dir ? LOW : HIGH);
  digitalWrite(motor2_in1, motor2_dir ? HIGH : LOW);
  digitalWrite(motor2_in2, motor2_dir ? LOW : HIGH);
  digitalWrite(motor3_in1, motor3_dir ? HIGH : LOW);
  digitalWrite(motor3_in2, motor3_dir ? LOW : HIGH);
}

void motorControlStop() {
  digitalWrite(motor1_in1, LOW);
  digitalWrite(motor1_in2, LOW);
  digitalWrite(motor2_in1, LOW);
  digitalWrite(motor2_in2, LOW);
  digitalWrite(motor3_in1, LOW);
  digitalWrite(motor3_in2, LOW);
}

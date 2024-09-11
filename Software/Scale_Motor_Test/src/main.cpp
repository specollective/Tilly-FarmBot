#include <Arduino.h>

const int motor1_in1 = 28;
const int motor1_in2 = 29;
const int motor2_in1 = 30;
const int motor2_in2 = 31;
const int motor3_in1 = 32;
const int motor3_in2 = 33;

const int motor1_pwm = 2; // PWM pin for Motor 1
const int motor2_pwm = 3; // PWM pin for Motor 2
const int motor3_pwm = 4; // PWM pin for Motor 3

// Function declarations
void motorControl(bool motor1_dir, bool motor2_dir, bool motor3_dir, int speed);
void motorControlStop();

void setup() {
  // Set all motor pins as outputs
  pinMode(motor1_in1, OUTPUT);
  pinMode(motor1_in2, OUTPUT);
  pinMode(motor1_pwm, OUTPUT);
  pinMode(motor2_in1, OUTPUT);
  pinMode(motor2_in2, OUTPUT);
  pinMode(motor2_pwm, OUTPUT);
  pinMode(motor3_in1, OUTPUT);
  pinMode(motor3_in2, OUTPUT);
  pinMode(motor3_pwm, OUTPUT);
  
  // Start serial communication
  Serial.begin(9600);
  
  // Turn on all motors immediately in one direction at full speed
  motorControl(true, true, true, 255); // 255 is the maximum PWM value (full speed)

  // Wait for 2 seconds
  delay(2000);

  // Stop all motors
  motorControlStop();
}

void loop() {
  // Your existing control logic can go here if needed
}

// Function definitions
void motorControl(bool motor1_dir, bool motor2_dir, bool motor3_dir, int speed) {
  // Motor 1 control
  digitalWrite(motor1_in1, motor1_dir ? HIGH : LOW);
  digitalWrite(motor1_in2, motor1_dir ? LOW : HIGH);
  analogWrite(motor1_pwm, speed);
  
  // Motor 2 control
  digitalWrite(motor2_in1, motor2_dir ? HIGH : LOW);
  digitalWrite(motor2_in2, motor2_dir ? LOW : HIGH);
  analogWrite(motor2_pwm, speed);
  
  // Motor 3 control
  digitalWrite(motor3_in1, motor3_dir ? HIGH : LOW);
  digitalWrite(motor3_in2, motor3_dir ? LOW : HIGH);
  analogWrite(motor3_pwm, speed);
}

void motorControlStop() {
  // Set PWM to 0 to stop the motors
  analogWrite(motor1_pwm, 0);
  analogWrite(motor2_pwm, 0);
  analogWrite(motor3_pwm, 0);
  
  // Set direction pins to LOW as a precaution
  digitalWrite(motor1_in1, LOW);
  digitalWrite(motor1_in2, LOW);
  digitalWrite(motor2_in1, LOW);
  digitalWrite(motor2_in2, LOW);
  digitalWrite(motor3_in1, LOW);
  digitalWrite(motor3_in2, LOW);
}
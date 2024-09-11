#include <Encoder.h>

// Define pins for motor 1 encoder
#define MOTOR1_ENCODER_A 2
#define MOTOR1_ENCODER_B 3

// Define pins for motor 2 encoder
#define MOTOR2_ENCODER_A 4
#define MOTOR2_ENCODER_B 5

// Define pins for motor 1 PWM control
#define MOTOR1_PWM_PIN 6
#define MOTOR1_DIRECTION_PIN 7

// Constants
#define MAX_SPEED 255 // Maximum PWM value
#define KP 1.0        // Proportional gain

// Create Encoder objects for both motors
Encoder motor1Encoder(MOTOR1_ENCODER_A, MOTOR1_ENCODER_B);
Encoder motor2Encoder(MOTOR2_ENCODER_A, MOTOR2_ENCODER_B);

// Function to set motor 1 speed based on motor 2 position
void controlMotor1() {
  // Read current positions of both motors
  long motor1Position = motor1Encoder.read();
  long motor2Position = motor2Encoder.read();

  // Calculate the error (difference in positions)
  long error = motor2Position - motor1Position;

  // Calculate PWM value based on the error and apply limits
  int pwmValue = constrain(KP * error, -MAX_SPEED, MAX_SPEED);

  // Set motor 1 speed and direction
  if (pwmValue > 0) {
    analogWrite(MOTOR1_PWM_PIN, pwmValue);
    digitalWrite(MOTOR1_DIRECTION_PIN, HIGH); // Set direction forward
  } else {
    analogWrite(MOTOR1_PWM_PIN, -pwmValue);
    digitalWrite(MOTOR1_DIRECTION_PIN, LOW); // Set direction backward
  }
}

void setup() {
  // Initialize motor control pins
  pinMode(MOTOR1_PWM_PIN, OUTPUT);
  pinMode(MOTOR1_DIRECTION_PIN, OUTPUT);

  // Set up Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Call the control function
  controlMotor1();

  // Print encoder values for debugging
  Serial.print("Motor 1: ");
  Serial.print(motor1Encoder.read());
  Serial.print("\t Motor 2: ");
  Serial.println(motor2Encoder.read());

  delay(100);
}

#include <Arduino.h>
#include <Wire.h>
#include <MPU9250.h>

MPU9250 mpu;
float pitch, roll, yaw;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(2000);
  
  if (!mpu.setup(0x68)) {
    Serial.println("MPU connection failed.");
    while (1);
  }

    delay(5000);

      // calibrate anytime you want to
    mpu.calibrateAccelGyro();
    Serial.print("Gyro Calibration Complete");
    delay(3000);
    // mpu.calibrateMag();
    // Serial.print("Mag Calibration Complete");

  // Configure MPU9250 (optional settings)
  // mpu.setAccelRange(MPU9250::ACCEL_RANGE_4G);
  // mpu.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // mpu.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // mpu.setSrd(19); // Set to read sensor data at ~50Hz
}

void loop() {
  if (mpu.update()) {
    pitch = atan2(mpu.getAccY(), sqrt(mpu.getAccX() * mpu.getAccX() + mpu.getAccZ() * mpu.getAccZ())) * 180.0 / M_PI;
    roll = atan2(-mpu.getAccX(), mpu.getAccZ()) * 180.0 / M_PI;
    yaw = atan2(mpu.getAccX(), mpu.getAccY()) * 180.0 / M_PI;

    // Send orientation data over serial
    Serial.print(pitch); Serial.print(",");
    Serial.print(roll); Serial.print(",");
    Serial.println(yaw);

    delay(100); // Delay for readability
  }
}
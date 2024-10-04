#include <Wire.h>
#include <Servo.h>
#include <MPU6050.h>  // Optional, depends on how you want to access MPU6050

// MPU6050 connections
const int MPU_ADDR = 0x68;  // I2C address of the MPU-6050

// Servo motor pin
const int servoPin = 9;

// Create a servo object
Servo myServo;

// Variables for storing MPU6050 readings
int16_t ax, ay, az;  // Accelerometer readings
int16_t gx, gy, gz;  // Gyroscope readings

void setup() {
  // Begin communication with MPU6050
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // Wake up MPU6050 from sleep mode
  Wire.write(0);
  Wire.endTransmission(true);
  
  // Attach the servo motor to the appropriate pin
  myServo.attach(servoPin);

  // Start Serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Request data from MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);  // Starting register for accelerometer data
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);  // Request accelerometer and gyroscope data

  // Read accelerometer data (2 bytes for each axis)
  ax = (Wire.read() << 8 | Wire.read());
  ay = (Wire.read() << 8 | Wire.read());
  az = (Wire.read() << 8 | Wire.read());

  // Read gyroscope data (2 bytes for each axis)
  gx = (Wire.read() << 8 | Wire.read());
  gy = (Wire.read() << 8 | Wire.read());
  gz = (Wire.read() << 8 | Wire.read());

  // Calculate angle from accelerometer data (e.g., pitch from ay)
  int pitchAngle = map(ay, -17000, 17000, 0, 90);  // Map MPU6050 accelerometer readings to 0-180

  // Move the servo based on pitch angle
  myServo.write(pitchAngle);

  // Print sensor data for debugging
  Serial.print("Pitch angle: ");
  Serial.println(pitchAngle);

  // Short delay
  delay(60);
}

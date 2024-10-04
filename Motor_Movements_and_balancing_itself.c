//C++ code for moto
#include <Arduino.h>
#include <Wire.h>
#include <PID_v1.h>

// Define the motor pins
const int motorLeft = 2;
const int motorRight = 4;

// Define the MPU6050 pins
const int mpuAddress = 0x68;
const int mpuInterruptPin = 2;

// Define the PID constants
const double kp = 10.0;
const double ki = 0.1;
const double kd = 0.5;

// Define the motor speed limits
const int minSpeed = 0;
const int maxSpeed = 255;

// Create a PID object
PID pid(&input, &output, &setpoint, kp, ki, kd, DIRECT);

// Define the setpoint (desired angle)
double setpoint = 0.0;

// Define the input (current angle)
double input = 0.0;

// Define the output (motor speed)
double output = 0.0;

void setup() {
  // Initialize the motor pins
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);

  // Initialize the MPU6050
  Wire.begin();
  Wire.beginTransmission(mpuAddress);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Initialize the PID
  pid.SetMode(AUTOMATIC);
  pid.SetSampleTime(10);
  pid.SetOutputLimits(minSpeed, maxSpeed);
}

void loop() {
  // Read the MPU6050 data
  Wire.beginTransmission(mpuAddress);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(mpuAddress, 14, true);
  int16_t ax = Wire.read() << 8 | Wire.read();
  int16_t ay = Wire.read() << 8 | Wire.read();
  int16_t az = Wire.read() << 8 | Wire.read();
  int16_t gx = Wire.read() << 8 | Wire.read();
  int16_t gy = Wire.read() << 8 | Wire.read();
  int16_t gz = Wire.read() << 8 | Wire.read();

  // Calculate the current angle
  input = atan2(ay, az) * 180 / PI;

  // Calculate the motor speed
  pid.Compute();

  // Move the robot forward or backward
  if (output > 0) {
    analogWrite(motorLeft, output);
    analogWrite(motorRight, output);
  } else {
    analogWrite(motorLeft, -output);
    analogWrite(motorRight, -output);
  }

  // Delay for 10ms
  delay(40);
}

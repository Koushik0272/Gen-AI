//Working of the Gyroscope MPU6050
Wire.h for I2C communication with the MPU6050.
MPU6050.h for reading sensor data.
PID_v1.h for implementing the PID controller

#include <Wire.h>
#include <MPU6050.h>
#include <PID_v1.h>

// MPU6050 object
MPU6050 mpu;

// PID parameters
double setpoint = 0;  // Target angle for balance (upright = 0 degrees)
double input;         // Current angle (from MPU6050)
double output;        // PID output

// PID tuning parameters
double Kp = 2;   // Proportional gain
double Ki = 5;   // Integral gain
double Kd = 1;   // Derivative gain

// PID object
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

// Motor control pins
int motorPin1 = 9;  // Motor 1 PWM pin
int motorPin2 = 10; // Motor 2 PWM pin

// Time tracking
unsigned long lastTime = 0;
const unsigned long loopTime = 10; // Loop time in ms

void setup() {
  // Start serial communication
  Serial.begin(9600);
  
  // Initialize MPU6050
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  // Initialize PID
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(loopTime);  // Set PID sample time
  myPID.SetOutputLimits(-255, 255);  // Motor PWM range

  // Motor pin setup
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

void loop() {
  unsigned long now = millis();
  
  if (now - lastTime >= loopTime) {
    lastTime = now;
    
    // Read accelerometer and gyroscope data
    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // Calculate tilt angle (simplified calculation)
    input = atan2(ax, az) * 180 / PI;

    // Compute PID output
    myPID.Compute();

    // Control motors based on PID output
    if (output > 0) {
      analogWrite(motorPin1, output);
      analogWrite(motorPin2, 0);
    } else {
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, -output);
    }
  }
}

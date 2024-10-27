#include <Arduino.h>
#include <Servo.h> // Include the Servo library

// Pin and variable definitions for LDR and servo
const int ldr_pinRight = A0; // Right LDR
const int ldr_pinLeft = A2;  // Left LDR
const int threshold = 60;    // Light detection threshold
Servo myServo;               // Create a Servo object
int currentServoPos = 90;    // Keep track of the current servo position

void setup() {
  pinMode(ldr_pinRight, INPUT);
  pinMode(ldr_pinLeft, INPUT);

  myServo.attach(9);               // Attach the servo to pin 9
  myServo.write(currentServoPos);  // Start at middle position (90 degrees)

  Serial.begin(9600);              // Start serial communication
}

void loop() {
  // ** Light Detection and Servo Adjustment **
  int rightSensorValue = analogRead(ldr_pinRight); // Read right sensor
  int leftSensorValue = analogRead(ldr_pinLeft);   // Read left sensor

  // Calculate the difference between the sensors
  int lightDifference = leftSensorValue - rightSensorValue;

  // Only move the servo if the light difference is significant
  if (abs(lightDifference) > threshold) {
    // Map the light difference to a target servo angle (0-180 degrees)
    int targetServoPos = map(lightDifference, -1023, 1023, 0, 180);

    // Move the servo gradually towards the target position
    if (currentServoPos < targetServoPos) {
      currentServoPos++; // Slowly increase the servo position
    } else if (currentServoPos > targetServoPos) {
      currentServoPos--; // Slowly decrease the servo position
    }

    // Update the servo position
    myServo.write(currentServoPos);
  }

  // Debugging output for LDR sensor values and servo position
  Serial.print("Right Sensor: ");
  Serial.println(rightSensorValue);
  Serial.print("Left Sensor: ");
  Serial.println(leftSensorValue);
  Serial.print("Servo Position: ");
  Serial.println(currentServoPos);
}
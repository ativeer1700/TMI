#include <Servo.h>

const int dirPin = 2;                                 // Direction pin
const int stepPin = 3;                                // Step pin
const float stepAngle = 1.8;                          // degrees per full step
const int stepsPerMove = int(1.0 / stepAngle + 0.5);  // round to nearest integer

// LDR pin connections
int ldrld = A0;  // Bottom Left LDR
int ldrrd = A3;  // Bottom Right LDR
int ldrlt = A1;  // Top Left LDR
int ldrrt = A2;  // Top Right LDR

Servo servoW;  // For Window movement
Servo servoX;  // For horizontal movement
Servo servoY;  // For vertical movement

int posX = 90;  // Initial horizontal servo position
int posY = 90;  // Initial vertical servo position

void setup() {

  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  Serial.begin(9600);
  servoW.attach(8);
  servoX.attach(9);
  servoY.attach(10);
  servoW.write(posX);
  servoX.write(posX);
  servoY.write(posY);
  Serial.println("Solar Tracker Initialized...");
}

void loop() {
  int lt = analogRead(ldrlt);  // Top left
  int rt = analogRead(ldrrt);  // Top right
  int ld = analogRead(ldrld);  // Bottom left
  int rd = analogRead(ldrrd);  // Bottom right

  int dtime = 10;
  int tol = 50;  // Tolerance (adjust as needed)

  // Average readings
  int avt = (lt + rt) / 2;  // Top avg
  int avd = (ld + rd) / 2;  // Bottom avg
  int avl = (lt + ld) / 2;  // Left avg
  int avr = (rt + rd) / 2;  // Right avg

  int dvert = avt - avd;   // Vertical difference
  int dhoriz = avl - avr;  // Horizontal difference

  // ----- Vertical Movement -----
  if (abs(dvert) > tol) {
    if (avt > avd) {
      posY -= 1;  // Move up
      Serial.println("Moving Down");

      // set direction (HIGH = clockwise)
      digitalWrite(dirPin, HIGH);
      // Rotate motor by ~5 degrees
      for (int i = 0; i < stepsPerMove; i++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);  // speed control
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
      }
    } else {
      posY += 1;  // Move down
      Serial.println("Moving up");

      // set direction (HIGH = clockwise)
      digitalWrite(dirPin, LOW);
      // Rotate motor by ~5 degrees
      for (int i = 0; i < stepsPerMove; i++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);  // speed control
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
      }
    }
  }

  // ----- Horizontal Movement -----
  if (abs(dhoriz) > tol) {
    if (avl > avr) {
      posX += 1;  // Move left
      Serial.println("Moving Left");


    } else {
      posX -= 1;  // Move right
      Serial.println("Moving Right");

    }
  }
  // Constrain servo angles
  posX = constrain(posX, 0, 180);
  posY = constrain(posY, 0, 180);

  // Move servos
  servoW.write(posX);
  servoX.write(posX);
  servoY.write(posY);

  delay(dtime);
}

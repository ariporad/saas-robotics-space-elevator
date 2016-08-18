#include <Servo.h>

#define LEFT_SERVO_PIN 5
#define RIGHT_SERVO_PIN 6

// D8 is a poor-man's start button. It's a jumper wire with a string attached. When this string is
// pulled, the wire disconnects, and the robot starts.
#define ACTIVATE_PIN 8

Servo left;
Servo right;

void setup() {
  pinMode(ACTIVATE_PIN, INPUT);
  left.attach(LEFT_SERVO_PIN);
  right.attach(RIGHT_SERVO_PIN);
  goStop();
}

void loop() {
  // Wait for the starting signal
  if (digitalRead(ACTIVATE_PIN) == HIGH) return;

  // Basic Demo
  goUp();
  delay(1000);
  goStop();
  delay(1000);
  goDown();
  delay(1000);
  goStop();
  delay(1000);
}

// Because the two motors are mirrored, they run in opposite directions.
void goUp() {
  left.write(0);
  right.write(180);
}

void goDown() {
  left.write(180);
  right.write(0);
}

void goStop() { // For Consistency
  left.write(90);
  right.write(90);
}


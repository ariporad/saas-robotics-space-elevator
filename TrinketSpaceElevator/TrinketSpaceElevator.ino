/*******************************************************************
  SoftServo sketch for Adafruit Trinket. 
  
  Required library is the Adafruit_SoftServo library
  available at https://github.com/adafruit/Adafruit_SoftServo
  The standard Arduino IDE servo library will not work with 8 bit
  AVR microcontrollers like Trinket and Gemma due to differences
  in available timer hardware and programming. We simply refresh
  by piggy-backing on the timer0 millis() counter
 
    Trinket:        USB+   Gnd   Pin #0  Pin #1  Pin #2 A1
  Connection:                    Servo1  Servo2   
 
 *******************************************************************/

#include <Adafruit_SoftServo.h>  // SoftwareServo (works on non PWM pins)

#define SERVO1PIN 0   // Servo control line (orange) on Trinket Pin #0
#define SERVO2PIN 1   // Servo control line (orange) on Trinket Pin #1

Adafruit_SoftServo myServo1, myServo2;  //create TWO servo objects
   
void setup() {
  // Set up the interrupt that will refresh the servo for us automagically
  // See for example https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers
  // Or https://arduinodiy.wordpress.com/2012/02/28/timer-interrupts/
  
  OCR0A = 0xAF;            // DEC = 175, this sets the number of cycles before the interrupt is triggered
  TIMSK |= _BV(OCIE0A);    // Turn on the compare interrupt (below!)
  
  myServo1.attach(SERVO1PIN);   // Attach the servo to pin 0 on Trinket
  myServo1.write(90);           // Tell servo to go to position per quirk
  myServo2.attach(SERVO2PIN);   // Attach the servo to pin 1 on Trinket
  myServo2.write(90);           // Tell servo to go to position per quirk
  delay(15);                    // Wait 15ms for the servo to reach the position
}

void loop()  {
  int servoPos = 180;
  myServo1.write(0);                    // tell servo to go to position
  myServo2.write(0);                    // tell servo to go to position

  delay(15);                              // waits 15ms for the servo to reach the position
}

// We'll take advantage of the built in millis() timer that goes off
// to keep track of time, and refresh the servo every 20 milliseconds
volatile uint8_t counter = 0;
SIGNAL(TIMER0_COMPA_vect) {
  // this gets called every 2 milliseconds
  counter += 2;
  // every 20 milliseconds, refresh the servos!
  if (counter >= 20) {
    counter = 0;
    myServo1.refresh();
    myServo2.refresh();
  }
}

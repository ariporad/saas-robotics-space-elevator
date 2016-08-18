/*
  Space Elevator Code 

  for 5V Adafruit Trinket

  Two Momentary Switches (top and bottom of robot) wired to Pin 0
  Continuous Servo wired to Pin 1
  Jumper wired to Pin 2 (used to start the robot)

*/
 
#include <Adafruit_SoftServo.h>  // SoftwareServo (works on non PWM pins)

#define SERVOPIN 1   // Servo control line (white) on Trinket Pin #1
#define STARTPIN 2    // Jumper attached to Trinket Pin #2 
#define TOPBUTTON 0  // Momentary switch wired to Trinket Pin #0

int pressed_counter = 0;  // button hasn't been pressed
unsigned long lastTimePressed = 0;
 
Adafruit_SoftServo drive;  //create a servo object
 
// the setup routine runs once when you press reset:
void setup() 
{
  // setup an interrupt timer
  OCR0A = 0xAF;            // DEC = 175, this sets the number of cycles before the interrupt is triggered
  TIMSK |= _BV(OCIE0A);    // Turn on the compare interrupt (below!)

  //setup servo
  drive.attach(SERVOPIN);   // Attach the servo to pin 1 on Trinket
  drive.write(90);           // Tell servo to go to position per quirk
  delay(15);                    // Wait 15ms for the servo to reach the position
  
  // setup momentary switched, pulled up to 5V (digital 1) by default
  pinMode(TOPBUTTON, INPUT_PULLUP);
  
  // setup start switched, pulled up to 5V.  normally will be shorted, but 
  // will go high to start program
  pinMode(STARTPIN, INPUT_PULLUP);
}
 
// the loop routine runs over and over again forever:
void loop() 
{
  // do nothing till startpin goes high
  if(digitalRead(STARTPIN) == 0)
  {
    return;
  }

  // look for pressed button which pulls input low AND that at least 1 second has passed since
  // the last time the button was pressed
  unsigned long timeSinceLastPressed = millis() - lastTimePressed;
  if(digitalRead(TOPBUTTON) == 0 && timeSinceLastPressed > 1000)
  {
      //increment a counter with a 250ms debounce
      ++pressed_counter;
      lastTimePressed = millis();
  } 
  
  // is the number of presses odd?
  if(pressed_counter%2 == 1)
  {
     drive.write(180); 
  }
  else
  {    
      drive.write(0);
  }
  
  delay(15);
}


volatile uint8_t counter = 0;
SIGNAL(TIMER0_COMPA_vect) {
  // this gets called every 2 milliseconds
  counter += 2;
  // every 20 milliseconds, refresh the servos!
  if (counter >= 20) {
    counter = 0;
    drive.refresh();
  }
}

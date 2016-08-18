  /*
  Space Elevator Code 

  for 5V Adafruit Trinket

  Momentary Switch wired to Pin 0
  Continuous Servo wired to Pin 1

*/
 
 #include <Adafruit_SoftServo.h>  // SoftwareServo (works on non PWM pins)

#define SERVO1PIN 1   // Servo control line (white) on Trinket Pin #1
 
int top_button = 0;   //momentary switch wired to Trinket Pin #0
int pressed_counter = 0;  // button hasn't been pressed
 
Adafruit_SoftServo drive;  //create a servo object
 
// the setup routine runs once when you press reset:
void setup() 
{
  // setup an interrupt timer
  OCR0A = 0xAF;            // DEC = 175, this sets the number of cycles before the interrupt is triggered
  TIMSK |= _BV(OCIE0A);    // Turn on the compare interrupt (below!)

  //setup servo
  drive.attach(SERVO1PIN);   // Attach the servo to pin 1 on Trinket
  drive.write(90);           // Tell servo to go to position per quirk
  delay(15);                    // Wait 15ms for the servo to reach the position
  
  // setup momentary switched, pulled up to 5V (digital 1) by default
  pinMode(top_button, INPUT_PULLUP);
}
 
// the loop routine runs over and over again forever:
void loop() 
{
  // look for pressed button which pulls input low
  if(digitalRead(top_button) == 0)
  {
      //increment a counter with a 250ms debounce
      ++pressed_counter;
      delay(250);
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

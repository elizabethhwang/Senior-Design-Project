/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo1; 
//Servo myservo2;   // create servo object to control a servo
                  // twelve servo objects can be created on most boards

int pos1,pos2;    // variable to store the servo position

const int flex1 = A0; 
//const int flex2 = A1;

int flexValue1,flexValue2;

void setup() {
  myservo1.attach(9);
  //myservo2.attach(10);  // attaches the servo on pin 9 to the servo object
}

void loop() {

  flexValue1 = analogRead(flex1);
  //flexValue2 = analogRead(flex2);
  
  pos1 = map(flexValue1, 800, 900, 0, 180);
  pos1 = constrain(pos1, 180, 0);
  //pos2 = map(flexValue2, 800, 900, 0, 180);
  //pos2 = constrain(pos2, 0, 180);
  
  myservo1.write(pos1);
  //myservo2.write(pos2);
  
  delay(20);

}

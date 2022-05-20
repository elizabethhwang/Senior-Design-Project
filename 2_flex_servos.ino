//This code was used to test the connection between the flex sensors and servo motors.

#include <Servo.h>

Servo myservo1; // create servo object to control a servo
Servo myservo2;   

int pos1,pos2;    // variable to store the servo position

const int flex1 = A0; //connect dflex sensors to analog pins A0 and A1
const int flex2 = A1;

int flexValue1,flexValue2; //create int variable to store flex sensor values

void setup() {
  myservo1.attach(9); // attaches the servo on pins 9 and 10 to the servo object
  myservo2.attach(10);  
}

void loop() {

  flexValue1 = analogRead(flex1); //read values from flex sensors
  flexValue2 = analogRead(flex2);
  
  pos1 = map(flexValue1, 800, 900, 0, 180); //map flex sensor values to the servo motor constraints
  pos1 = constrain(pos1, 180, 0);           //constrain max and min angle values from 0-180 degrees
  pos2 = map(flexValue2, 800, 900, 0, 180);
  pos2 = constrain(pos2, 0, 180);
  
  myservo1.write(pos1);                     //write angle values to servo motors
  myservo2.write(pos2);
  
  delay(20);

}

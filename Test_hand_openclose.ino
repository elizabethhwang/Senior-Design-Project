//This code was used to test the bending and opening of the hand, with a 2 second delay between the different positions.


#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;

int pos1 = 0;
int pos2 = 180;

void setup() {
  // put your setup code here, to run once:
  
  myservo1.attach(15);
  myservo2.attach(16);
  myservo3.attach(17);
  myservo4.attach(18);
  myservo5.attach(19);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  myservo1.write(pos1);
  myservo2.write(pos1);
  myservo3.write(pos1);
  myservo4.write(pos1);
  myservo5.write(pos1);


  delay(2000);

  myservo1.write(pos2);
  myservo2.write(pos2);
  myservo3.write(pos2);
  myservo4.write(pos2);
  myservo5.write(pos2);

  delay(2000);
}

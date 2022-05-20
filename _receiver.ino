#include "Arduino.h"
#include <SPI.h>
#include <RF24.h>
#include <Servo.h>

// This is just the way the RF24 library works:
// Hardware configuration: Set up nRF24L01 radio on SPI bus (pins 10, 11, 12, 13) plus pins 7 & 8
RF24 radio(7, 8);

byte addresses[][6] = {"1Node","2Node"};

int pos1,pos2,pos3,pos4,pos5; //position of servo
Servo myservo1; //initialize servo object
Servo myservo2; //initialize servo object
Servo myservo3; //initialize servo object
Servo myservo4; //initialize servo object
Servo myservo5; //initialize servo object

unsigned int data[5]; //data array being received

// -----------------------------------------------------------------------------
// SETUP   SETUP   SETUP   SETUP   SETUP   SETUP   SETUP   SETUP   SETUP
// -----------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  Serial.println("THIS IS THE RECEIVER CODE");

  // Initiate the radio object
  radio.begin();

  // Set the transmit power to lowest available to prevent power supply related issues
  radio.setPALevel(RF24_PA_MIN);

  // Set the speed of the transmission to the quickest available
  radio.setDataRate(RF24_2MBPS);

  // Use a channel unlikely to be used by Wifi, Microwave ovens etc
  radio.setChannel(124);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);

  // Start the radio listening for data
  radio.startListening();
  
  //attach servo to pins 
  myservo1.attach(A1); //A1
  myservo2.attach(A2); //A2
  myservo3.attach(A3); //A3
  myservo4.attach(A4); //A4
  myservo5.attach(A5); //A5
  
}

// -----------------------------------------------------------------------------
// We are LISTENING on this device only (although we do transmit a response)
// -----------------------------------------------------------------------------
void loop() {

  // This is what we receive from the other device (the transmitter)
  //unsigned int data;

  // Is there any data for us to get?
  if ( radio.available()) {

    // Go and read the data and put it into that variable
    while (radio.available()) {
      radio.read( &data, sizeof(data));
    }

    //Map data received to the servo
    pos1 = map(data[0], 0, 1023, 255, 0);
    pos2 = map(data[1], 0, 1023, 255, 0);
    pos3 = map(data[2], 0, 1023, 255, 0);
    pos4 = map(data[3], 0, 1023, 255, 0);
    pos5 = map(data[4], 0, 1023, 255, 0);

    //Write data to the servo
    myservo1.write(pos1);
    myservo2.write(pos2);
    myservo3.write(pos3);
    myservo4.write(pos4);
    myservo5.write(pos5);

    //Print voltage and position values to serial monitor
    Serial.print("Flex sensor 1 is: ");
    Serial.print(data[0]);
    Serial.print(", Servo motor 1 is: ");
    Serial.println(pos1);

    Serial.print("Flex sensor 2 is: ");
    Serial.print(data[1]);
    Serial.print(", Servo motor 2 is: ");
    Serial.println(pos2);

    Serial.print("Flex sensor 3 is: ");
    Serial.print(data[2]);
    Serial.print(", Servo motor 3 is: ");
    Serial.println(pos3);

    Serial.print("Flex sensor 4 is: ");
    Serial.print(data[3]);
    Serial.print(", Servo motor 4 is: ");
    Serial.println(pos4);

    Serial.print("Flex sensor 5 is: ");
    Serial.print(data[4]);
    Serial.print(", Servo motor 5 is: ");
    Serial.println(pos5);
    delay(50);

  }
 
}

#include "Arduino.h"
#include <SPI.h>
#include <RF24.h>

// This is just the way the RF24 library works:
// Hardware configuration: Set up nRF24L01 radio on SPI bus (pins 10, 11, 12, 13) plus pins 7 & 8
RF24 radio(7, 8);

byte addresses[][6] = {"1Node", "2Node"};

const int flex1 = A1; //flex sensor value
const int flex2 = A2; //flex sensor value
const int flex3 = A3; //flex sensor value
const int flex4 = A4; //flex sensor value
const int flex5 = A5; //flex sensor value
unsigned int data[5]; //data value to transmit

// -----------------------------------------------------------------------------
// SETUP   SETUP   SETUP   SETUP   SETUP   SETUP   SETUP   SETUP   SETUP
// -----------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  Serial.println("THIS IS THE TRANSMITTER CODE");

  // Initiate the radio object
  radio.begin();

  // Set the transmit power to lowest available to prevent power supply related issues
  radio.setPALevel(RF24_PA_MIN);

  // Set the speed of the transmission to the quickest available
  radio.setDataRate(RF24_2MBPS);

  // Use a channel unlikely to be used by Wifi, Microwave ovens etc
  radio.setChannel(124);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);

}

// -----------------------------------------------------------------------------
// LOOP     LOOP     LOOP     LOOP     LOOP     LOOP     LOOP     LOOP     LOOP
// -----------------------------------------------------------------------------
void loop() {

  // Generate a single random character to transmit
  //unsigned int data;
  data[0] = analogRead(flex1);
  data[1] = analogRead(flex2);
  data[2] = analogRead(flex3);
  data[3] = analogRead(flex4);
  data[4] = analogRead(flex5);
  
  // Ensure we have stopped listening
  radio.stopListening(); 

  // Did we manage to SUCCESSFULLY transmit the data? If not, print an error message
  if (!radio.write( &data, sizeof(data) )) {
    Serial.println("No acknowledgement of transmission - receiving radio device connected?");    
  }

  Serial.println(data[0]);
  Serial.println(data[1]);
  delay(50);


}

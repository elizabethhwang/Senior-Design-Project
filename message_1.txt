// Current Voltage Sensor with OLED
// Code by Christopher Lai
// LAST UPDATED: 5/11/2022

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int voltageRead = A0;
const int currentRead = A1;

const int LED = 3;
const int button = 9;

int settingstate = 0;

float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;

unsigned int x=0;
float AcsValue=0.0, Samples=0.0, AvgAcs=0.0, AcsValueF=0.0;

void setup() {
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Button input
  pinMode(button, INPUT_PULLUP);
  pinMode(LED, INPUT_PULLUP);

  // Initialize Code
  display.clearDisplay();
  display.setRotation(0);
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);
  display.println("WELCOME");
  display.setCursor(0,20);
  display.println("ALEX PEREZ");
  display.setCursor(0,45);
  display.println("LOADING...");
  display.display();
  delay(3000);
}

void loop() {
  // Voltage Sensor Stuff
  value = analogRead(voltageRead);
  vOUT = (value * 5) / 1024.0;
  vIN = vOUT / (R2/(R1+R2));
  Serial.print("Voltage Input = ");
  Serial.println(vIN);

  // Current Sensor Stuff
  AcsValue=0.0;
  Samples=0.0; 
  AvgAcs=0.0;
  AcsValueF=0.0;
  for (int x = 0; x < 150; x++){ //Get 150 samples
  AcsValue = analogRead(currentRead);     //Read current sensor values   
  Samples = Samples + AcsValue;  //Add samples together
  delay (3); // let ADC settle before next sample 3ms
  }
  
  AvgAcs=Samples/150.0; //Taking Average of Samples
  AcsValueF = (2.5 - (AvgAcs * (5.0 / 1024.0)) )/0.066; // 0.026

  Serial.print("Theoretical Current Through Load (mA) = ");
  Serial.println(vIN/10000*100);

  Serial.print("Experimental Current Through Load (mA) = ");
  Serial.println(AcsValueF);//Print the read current on Serial monitor

  Serial.println("Button = " + String(digitalRead(button)));
  Serial.println("Button State = " + String(settingstate) + "\n");
  
  // Display Logic
  if(!digitalRead(button))
  {
    settingstate = settingstate + 1;
    Serial.println("SS Changed!");
    delay(250);
  }

  if (settingstate == 0)
  {
    voltDisp();
  }
  else if (settingstate == 1)
  {
    EcurrentDisp();
  }
  else if (settingstate == 2)
  {
    TcurrentDisp();
  }
  else if (settingstate == 3)
  {
    ledDisp();
  }
  else
  {
    settingstate = 0;
  }
  
  delay(50);
}

void voltDisp()
{
  // Display Voltage
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Voltage:");
  display.setCursor(0,20);
  display.println(String(vIN) + "V");
  display.display();
}

void EcurrentDisp()
{
  // Display Experimental Current
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("ECurrent:");
  display.setCursor(0,20);
  display.println(String(AcsValueF) + "mA");
  display.display();
}

void TcurrentDisp()
{
  // Display Theoretical Current
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("TCurrent:");
  display.setCursor(0,20);
  display.println(String(vIN/10000*100) + "mA");
  display.display();
}

void ledDisp()
{
  // Display LED State
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("B.O.B. SDP");
  display.setCursor(0,20);
  // Serial.println("Extra State!");
  display.println("State +1!");
  display.display();
}

#include "CurieIMU.h"
#include"CurieTimerOne.h"
#include <Keypad.h>

int ledPin2 = 2;
int ledPin3 = 3;
int ledPin4 = 4;
int ledPin5 = 5;

void sendData( int x );

float ax,ay,az;  
float gx, gy, gz;

int x=0;

char key='1';

float vol=0;

int state=1;

int TimeISR=20000;
  
const int ledPin = 3;   //pin 3 has PWM funtion
const int flexPin = A0; //pin A0 to read analog input

int value; //save analog value

const byte ROWS = 4; 
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { 9, 8, 7, 6 };

byte colPins[COLS] = { 13, 12, 11, 10 }; 

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int lastOrientation = - 1; // previous orientation (for comparison)

void setup() {
  Serial.begin(9600); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open

  // initialize device
  Serial.println("Initializing IMU device...");
  CurieIMU.begin();

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(200);
  CurieIMU.setAccelerometerRange(200);
  CurieTimerOne.start(20000, &data_collection);

   pinMode(ledPin2,OUTPUT); // put your setup code here, to run once:
   pinMode(ledPin3,OUTPUT);
   pinMode(ledPin4,OUTPUT);
   pinMode(ledPin5,OUTPUT);
}



void data_collection()
{ 
  
  if(key=='1')
  {
    if(az>0)
    if(gy>140)
      x=1;

   if(az<0)
    if(gy>190)
      x=2;

  }

  if(key=='2')
  {
    if(gy>150)
      x=3;

    if(gy<-150)
      x=4;
  }

  if(key=='3')
  {
    {
    if(az>0)
    if(gy>140)
      x=5;

   if(az<0)
    if(gy>190)
      x=6;

  }
    
  }

  if(key=='4')
  {
    if(value>285)
      x=7;
    else if(value<285)
      x=8;
    
  }

  Serial.print(x);
  sendData(x);  
  x=0;
}


void loop() {
  
  CurieIMU.readGyroScaled(gx,gy,gz);
  CurieIMU.readAccelerometerScaled(ax, ay, az);

  value = analogRead(flexPin);         //Read and save analog value from potentiometer

  char key1 = kpd.getKey();

  if(key1 != '\0')
    key = key1;
  
 /*
  Serial.print(ax);
  Serial.print("\t");
  Serial.print(ay);
  Serial.print("\t");
  Serial.print(az);
  Serial.println("\t");


  Serial.print(gx);
  Serial.print("\t");
  Serial.print(gy);
  Serial.print("\t");
  Serial.print(gz);
  Serial.print("\t");
  Serial.println(value);               //Print value
*/  
}

void sendData( int x ){

  if (x == 0 ) {
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin5, LOW);
  }
  else if (x == 1 ) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin5, LOW);
  }
  else if (x == 3 ) {
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin5, LOW);
  }
  else if (x == 4 ) {
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, HIGH);
    digitalWrite(ledPin5, LOW);
  }
  else if (x == 5 ) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, HIGH);
    digitalWrite(ledPin5, LOW);
  }
  else if (x == 6 ) {
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    digitalWrite(ledPin5, LOW);
  }
  else if (x == 7 ) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    digitalWrite(ledPin5, LOW);
  }
  else if (x == 8 ) {
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin5, HIGH);
  }
  else if (x == 9 ) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin5, HIGH);
  }
  else{
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin5, LOW);
  }
}


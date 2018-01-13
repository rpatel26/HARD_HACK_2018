//flex code:
const int ledPin = 3;   //pin 3 has PWM funtion
const int flexPin = A0; //pin A0 to read analog input
int value; //save analog value

//accelerometer code:
#include <Wire.h> // Must include Wire library for I2C
#include <SFE_MMA8452Q.h> // Includes the SFE_MMA8452Q library
MMA8452Q accel;

// number pad code:
#include <Keypad.h>

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

#define ledpin 13


void setup() {
 //flex code:
  Serial.begin(9600);  
  pinMode(ledPin, OUTPUT);  //Set pin 3 as 'output'
      
//accelerometer code:
  //Serial.println("MMA8452Q Test Code!");
  accel.init();
  accel.init(SCALE_8G, ODR_6);
// number pad code:
  digitalWrite(ledpin, HIGH);
}

void loop() {
//flex sensor code: 
  value = analogRead(flexPin);         //Read and save analog value from potentiometer
  //Serial.println(value);               //Print value
  value = map(value, 700, 900, 0, 255);//Map value 0-1023 to 0-255 (PWM)
  analogWrite(ledPin, value);          //Send PWM value to led
  delay(100);                          //Small delay

//accelerometer code:
if (accel.available())
  {
    // First, use accel.read() to read the new variables:
    accel.read();
    printCalculatedAccels();
    printOrientation();
    Serial.println(); // Print new line every time.
  }

//Number pad code:
char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    switch (key)
    {
      case '*':
        digitalWrite(ledpin, LOW);
        break;
      case '#':
        digitalWrite(ledpin, HIGH);
        break;
      default:
        Serial.println(key);
    }
  }
}


void printAccels()
{
  Serial.print(accel.x, 3);
  Serial.print("\t");
  Serial.print(accel.y, 3);
  Serial.print("\t");
  Serial.print(accel.z, 3);
  Serial.print("\t");
}

void printCalculatedAccels()
{ 
  Serial.print(accel.cx, 3);
  Serial.print("\t");
  Serial.print(accel.cy, 3);
  Serial.print("\t");
  Serial.print(accel.cz, 3);
  Serial.print("\t");
}

void printOrientation()
{
  byte pl = accel.readPL();
  switch (pl)
  {
  case PORTRAIT_U:
    Serial.print("Portrait Up");
    break;
  case PORTRAIT_D:
    Serial.print("Portrait Down");
    break;
  case LANDSCAPE_R:
    Serial.print("Landscape Right");
    break;
  case LANDSCAPE_L:
    Serial.print("Landscape Left");
    break;
  case LOCKOUT:
    Serial.print("Flat");
    break;
  }
}

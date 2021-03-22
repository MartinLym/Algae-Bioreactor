#include <OneWire.h>
#include <Wire.h>
#include "DFRobot_EC.h"
#include "DFRobot_PH.h"
#include "Adafruit_MPR121.h"
#include "SparkFun_AS7265X.h" 
#include <SoftwareSerial.h>
#include <EEPROM.h>

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

///////// PINS /////////
#define CALIB_EC_BUTTON_PIN 3
#define LED_PIN 13
#define TEMP_PIN 2
#define EC_PIN 13
#define NUM_SENSORS 8
#define DO_PIN A0
#define PH_PIN A1
#define PRESSURE_PIN A2
#define COMPRESSOR_PIN 22

///////// Sensors /////////
// Conductivity
float ecVoltage, ecTemp;
int conductivityButtonState;
int lastConductivityButtonState = LOW;
unsigned long lastConductivityDebounceTime = 0;
unsigned long conductivityDebounceDelay = 50;

// pH
float phVoltage, phTemp;
int phButtonState;
int lastPhButtonState = LOW;
unsigned long lastPhDebounceTime = 0;
unsigned long phDebounceDelay = 50;


// Oxygen
const uint16_t DO_Table[41] = {
    14460, 14220, 13820, 13440, 13090, 12740, 12420, 12110, 11810, 11530,
    11260, 11010, 10770, 10530, 10300, 10080, 9860, 9660, 9460, 9270,
    9080, 8900, 8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
    7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730, 6630, 6530, 6410};

#define VREF 5000    //VREF (mv)
#define ADC_RES 1024 //ADC Resolution
#define TWO_POINT_CALIBRATION 1

//Single point calibration needs to be filled CAL1_V and CAL1_T
#define CAL1_V (1600) //mv
#define CAL1_T (25)   //℃
//Two-point calibration needs to be filled CAL2_V and CAL2_T
//CAL1 High temperature point, CAL2 Low temperature point
#define CAL2_V (1300) //mv
#define CAL2_T (15)   //℃

// CO2
SoftwareSerial co2(50,51);
unsigned char hexdata[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79}; //Read the gas density command /Don't change the order

// OBJECTS
DFRobot_EC ec;
DFRobot_PH ph;
OneWire ds(TEMP_PIN);
Adafruit_MPR121 cap = Adafruit_MPR121();
AS7265X spectrometer;

//GLOBALS
float sensorData[NUM_SENSORS];
bool readSensors = false;
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

 // Change this Later
int ledState = LOW;

//Functions
float readTemp();
float readpH();

void setup(){
  Serial.begin(115200);
  Serial1.begin(9600);
  co2.begin(115200);
  //pinMode(CALIB_BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(COMPRESSOR_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  ec.begin();
  ph.begin();
  Serial.println("MPR121 found!");
   if(spectrometer.begin() == false)
  {
    Serial.println("Sensor does not appear to be connected. Please check the wiring. Freezing...");
    while(1);
  }
}

void loop(){
  readTemp();
  readpH();
  readConductivity();
  readPressure();
  readOxygen();
  pumpPressure();
  delay(500);
  
  /*
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != calibrateButtonState) {
      calibrateButtonState = reading;

      if (calibrateButtonState == HIGH) {
        //DO SOMETHING
        ledState = !ledState;
        sensorData[0] = readTemp();
        sensorData[1] = sensorData[0]*2;
        //readConductivity();
        for (int i = 0; i<2;i++){
          Serial1.println(sensorData[i]);
          delay(1000);
        }
        
      }
    }
  }

  espSerial.println("100");
  delay(1000);
  if(readSensors){
    readTemp(); //Wait 15-20seconds for temp to become stable
    measureConductivity();
    readSensors = false;
  }
  */
}

float readTDS(){
  
}

void sendData(float sensorData){
  
}

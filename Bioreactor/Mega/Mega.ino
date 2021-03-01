#include <OneWire.h>
#include "DFRobot_EC.h"
#include "DFRobot_PH.h"
#include <EEPROM.h>

#define CALIB_BUTTON_PIN 3
#define LED_PIN 13
#define TEMP_PIN 2
#define EC_PIN 13
#define NUM_SENSORS 8

#define DO_PIN A0
#define PH_PIN A1

// OBJECTS
DFRobot_EC ec;
DFRobot_PH ph;
OneWire ds(TEMP_PIN);

//GLOBALS
String str;
float sensorData[NUM_SENSORS];
bool readSensors = false;
float voltageEC,ecValue, phVoltage,phValue,temp = 25; // Change this Later
int ledState = LOW;
int calibrateButtonState;
int lastCalibrateButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup(){
  Serial.begin(115200);
  Serial1.begin(9600);
  pinMode(CALIB_BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
  ec.begin();
  ph.begin();
}

void loop(){
  //float temperature = readTemp();
  //Serial.println(temperature);

  delay(100);
  int reading = digitalRead(CALIB_BUTTON_PIN);
  if (reading != lastCalibrateButtonState) {
    lastDebounceTime = millis();
  }

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
  digitalWrite(LED_PIN, ledState);
  lastCalibrateButtonState = reading;
  /*
  espSerial.println("100");
  delay(1000);
  if(readSensors){
    readTemp(); //Wait 15-20seconds for temp to become stable
    measureConductivity();
    readSensors = false;
  }
  */
}

float readConductivity(){
  voltageEC = analogRead(EC_PIN)/1024.0*5000;
  temp = readTemp();
  ecValue = ec.readEC(voltageEC, temp);
  return ecValue;
}

float readTemp(){
  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read Scratchpad


  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
}

float readTDS(){
  
}

float readSpectrometer(){
  
}

float readOxygen(){
  
}

float readPH(){
  static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U){                  //time interval: 1s
        timepoint = millis();
        int temperature = readTemp();         // read your temperature sensor to execute temperature compensation
        phVoltage = analogRead(PH_PIN)/1024.0*5000;  // read the voltage
        phValue = ph.readPH(phVoltage,temperature);  // convert voltage to pH with temperature compensation
        Serial.print("temperature:");
        Serial.print(temperature,1);
        Serial.print("^C  pH:");
        Serial.println(phValue,2);
    }
}

float readPressure(){
  
}

void sendData(float sensorData){
  
}

void calibratePH(){
  ph.calibration(phVoltage,temp);
}

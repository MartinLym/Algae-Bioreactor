#include <OneWire.h>  //Temperature
#include <SoftwareSerial.h>
#include "DFRobot_EC.h" //Electrical Conductivity
#include "DFRobot_PH.h" //pH
#include <EEPROM.h>
#include <Arduino.h>
#include "SparkFun_AS7265X.h"  //Spectrometer
#include <FastLED.h>
#include <Wire.h>
#include "RTClib.h"

#define NUM_LEDS 100
#define COMPRESSOR_PIN 35
#define LED_PIN 12
#define NUM_SAMPLE 23
#define NUM_REACTOR 5

float containerData[NUM_SAMPLE];
float bioreactorData[NUM_REACTOR];

//OBJECTS
SoftwareSerial co2(50, 51); //CO2 Serial
DFRobot_EC ec;
DFRobot_PH ph;
AS7265X spectrometer;
CRGB leds[NUM_LEDS];
RTC_DS1307 rtc;

//FUNCTIONS
float getTemp();
//void morning(DateTime timeNow);
//void night();
//void hourly();

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  co2.begin(9600);

  pinMode(COMPRESSOR_PIN, OUTPUT);

  ec.begin();
  ph.begin();
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  //if (spectrometer.begin() == false) {
  //  Serial.println("Spectrometer does not appear to be connected. Please check the wiring. Freezing...");
  //  while (1);
  //}
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  airPumpSetup();
  samplePumpSetup();
  buttonSetup();
  //pumpAir();
  allLightsOn();
  pumpAir(0);
}

void loop() {

  DateTime currentTime = rtc.now();
  Serial.println();
  Serial.print("Time:  ");
  Serial.print(currentTime.year(), DEC);
  Serial.print("-");
  Serial.print(currentTime.month(), DEC);
  Serial.print("-");
  Serial.print(currentTime.day(), DEC);
  Serial.print("-");
  Serial.print(currentTime.hour(), DEC);
  Serial.print("-");
  Serial.print(currentTime.minute(), DEC);
  Serial.print("-");
  Serial.print(currentTime.second(), DEC);
  Serial.println();

  if(morning(currentTime)){
    allLightsOn();
    pumpAir(250);
  }else if(night(currentTime)){
    allLightsOff();
    pumpAir(0);
  }else if(hourly(currentTime)){
    readReactor();
    //samplePumpInStart();
  }
  //float temperature = getTemp();
  //Serial.println(temperature);
  //readCO2();
  //readElectricalConductivity();
  //allLightsOn();
  //readpH();
  //pumpPressure();
  //pumpAir();
  //readCO2();
  //readElectricalConductivity();
  //readOxygen();
  //readpH();
  readPressure();
  readBlueButton();
  readBlackButton();
  readRedButton();
  readGreenButton();

  //readRedButton();
  delay(100);

}

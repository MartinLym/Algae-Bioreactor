/*
 * Alarm Sketch for DS1307 Real time clock module 
 * To turn ON or OFF AC or DC load
 * 
 * Code Written/modefied by Ahmad Shamshiri on Jun 15, 2019
 * in Ajax, Ontario, Canada @ www.Robojax.com
 Watch video instruction for this video: https://youtu.be/ykgXKUuvtbE
 * 
 * 
 * for library of this code visit http://robojax.com/
 * Original library from https://github.com/adafruit/RTClib
 */
//DateTime (uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec)

#include <Wire.h>
#include "RTClib.h"

#define alarmPin 13

const int alarm[]={0,0,0,0,0,0};
const int waitTime =4000;


RTC_DS1307 rtc;


void setup () {
  pinMode(alarmPin,OUTPUT);//set pin 2 as output
 
  while (!Serial); // for Leonardo/Micro/Zero

  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
     //rtc.adjust(DateTime(2019, 3, 3, 20, 0, 0));
  }
  //rtc.adjust(DateTime(2019, 3, 3, 20, 0, 0));
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop () {
    DateTime robojax = rtc.now();
    Serial.print("Alarm: ");
    for(int i=0;i<6;i++){
      Serial.print(alarm[i]);
      if(i !=5){
        Serial.print("-");
      }
    }
    Serial.println();
    Serial.print("Time:  ");
    Serial.print(robojax.year(), DEC);
    Serial.print("-");
    Serial.print(robojax.month(), DEC);
    Serial.print("-");
    Serial.print(robojax.day(), DEC);
    Serial.print("-");    
    Serial.print(robojax.hour(), DEC);
    Serial.print("-");
    Serial.print(robojax.minute(), DEC);
    Serial.print("-");
    Serial.print(robojax.second(), DEC);
    Serial.println();
 
   if(checkAlarm(robojax)){
    digitalWrite(alarmPin, HIGH);// 
    Serial.print("Alarm Triggered");
    delay(waitTime);
    //while (1);// wait for ever 
   }else{
    digitalWrite(alarmPin, LOW);//
   }
    Serial.println();
    delay(500);
}

/*
 * 
 * @brief returns true if alarm array matches the current time
 * @param timeNow, is the object for RTC clock
 * @return true if alarm values matches current time
 * Written by Ahmad Shamshiri for Robojax.com 
 * on Friday Jun 14th, 2019 at 20:28 in Ajax, Ontatio, Canada
 * 
 */

boolean checkAlarm(DateTime timeNow){

  if(alarm[3] == timeNow.hour()){
      return true;
   }else{
      return false;
     
   }
  
}

#define PH_PIN A1
float phVoltage, phTemp;

float readpH(){
  static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U){                  //time interval: 1s
        timepoint = millis();
        phTemp = getTemp();         // read your temperature sensor to execute temperature compensation
        phVoltage = analogRead(PH_PIN)/1024.0*5000;  // read the voltage
        float phValue = ph.readPH(phVoltage,phTemp);  // convert voltage to pH with temperature compensation
        /*
        Serial.print("phTemp:");
        Serial.print(phTemp,1);
        Serial.print("^C  pH:");
        Serial.println(phValue,2);
        */
        return phValue;
    }
    ph.calibration(phVoltage, phTemp);
    
}

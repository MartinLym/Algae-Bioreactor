#define EC_PIN A3
float ecVoltage, ecTemp;

float readElectricalConductivity(){
  static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U)  //time interval: 1s
    {
      timepoint = millis();
      ecVoltage = analogRead(EC_PIN)/1024.0*5000;
      ecTemp = getTemp();
      float ecValue = ec.readEC(ecVoltage, ecTemp);
      
      Serial.print("ectemp:");
      Serial.print(ecTemp,1);
      Serial.print("^C  EC:");
      Serial.print(ecValue,2);
      Serial.println("ms/cm");
      
      return ecValue;
    }

  ec.calibration(ecVoltage, ecTemp);
  
}

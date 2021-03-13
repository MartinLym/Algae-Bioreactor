long readCO2(){
  long hi,lo,CO2;
  co2.write(hexdata,9);

  for(int i=0,j=0;i<9;i++){
    if (co2.available()>0){
     
     int ch=co2.read();

    if(i==2){     hi=ch;   }   //High concentration
    if(i==3){     lo=ch;   }   //Low concentration
    if(i==8) {
               CO2=hi*256+lo;  //CO2 concentration
      Serial.print("CO2 concentration: ");
      Serial.print(CO2);
      Serial.println("ppm");
      }
    }
  }
  return CO2;
}

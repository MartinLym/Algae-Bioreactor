unsigned char hexdata[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79}; //Read the gas density command /Don't change the order

long readCO2() {
  co2.write(hexdata, 9);
  delay(500);

  for (int i = 0, j = 0; i < 9; i++)
  {
    if (co2.available() > 0)
    {
      long hi, lo, CO2;
      int ch = co2.read();

      if (i == 2) {
        hi = ch;    //High concentration
      }
      if (i == 3) {
        lo = ch;    //Low concentration
      }
      if (i == 8) {
        CO2 = hi * 256 + lo; //CO2 concentration
        /*
        Serial.print("CO2 concentration: ");
        Serial.print(CO2);
        Serial.println("ppm");
        */
        return CO2;
      }

    }

  }

}

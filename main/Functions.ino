void readReactor() {
  bioreactorData[0] = readCO2();
  bioreactorData[1] = readPressure();
  bioreactorData[2] = 255;
  bioreactorData[3] = 255;
  bioreactorData[4] = 255;
  Serial.println("Reactor");
  delay(1500);
  for (int i = 0; i < 5; i++) {
    Serial.println(bioreactorData[i]);
    delay(2000);
  }
}

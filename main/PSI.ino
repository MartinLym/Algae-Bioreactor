#define PRESSURE_PIN A2
#define COMPRESSOR_PIN 35

float readPressure() {
  const int pressureZero = 102.4; //analog reading of pressure transducer at 0psi
  const int pressureMax = 921.6; //analog reading of pressure transducer at 100psi
  const int pressuretransducermaxPSI = 150; //psi value of transducer being used

  float pressureValue = 0;

  pressureValue = analogRead(PRESSURE_PIN); //reads value from input pin and assigns to variable
  pressureValue = ((pressureValue - pressureZero) * pressuretransducermaxPSI) / (pressureMax - pressureZero); //conversion equation to convert analog reading to psi
  Serial.print(pressureValue, 1); //prints value from previous line to serial
  Serial.println("psi"); //prints label to serial
  //
  return pressureValue*10;
}

void pumpPressure() {

  float reactorPressure = readPressure();
  Serial.print(reactorPressure, 1); //prints value from previous line to serial
  Serial.println("psi"); //prints label to serial
  while (reactorPressure <= 30) {
    digitalWrite(COMPRESSOR_PIN, HIGH);
  }
  digitalWrite(COMPRESSOR_PIN, LOW);


}

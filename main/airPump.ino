int airEnA = 6;
int airIn1 = 24;
int airIn2 = 25;

void airPumpSetup(){
  pinMode(airEnA, OUTPUT);
  pinMode(airIn1, OUTPUT);
  pinMode(airIn2, OUTPUT);
}

void pumpAir(int pumpRate){
  analogWrite(airEnA, pumpRate);
  digitalWrite(airIn1, HIGH);
  digitalWrite(airIn2, LOW);
}

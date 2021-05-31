int sampleInENA = 5;
int sampleIn1 = 22;
int sampleIn2 = 23;

int sampleOutEnB = 4;
int sampleOut3 = 30;
int sampleOut4 = 31;

void samplePumpSetup(){
  pinMode(sampleInENA, OUTPUT);
  pinMode(sampleIn1, OUTPUT);
  pinMode(sampleIn2, OUTPUT);
  pinMode(sampleOutEnB, OUTPUT);
  pinMode(sampleOut3, OUTPUT);
  pinMode(sampleOut4, OUTPUT);

  digitalWrite(sampleIn1,LOW);
  digitalWrite(sampleIn2, HIGH);
  digitalWrite(sampleOut3, HIGH);
  digitalWrite(sampleOut4, LOW);
  
}

void samplePumpInStart(){
  analogWrite(sampleInENA, 255);
  digitalWrite(sampleIn1,LOW);
  digitalWrite(sampleIn2, HIGH);
}
void samplePumpInStartRev(){
  analogWrite(sampleInENA, 255);
  digitalWrite(sampleIn1,HIGH);
  digitalWrite(sampleIn2, LOW);
}

void samplePumpInStop(){
  analogWrite(sampleInENA, 0);
}

void samplePumpOutStart(){
  analogWrite(sampleOutEnB, 255);
}

void samplePumpOutStop(){
  analogWrite(sampleOutEnB, 0);
}

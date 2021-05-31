const int redButtonPin = 49;
const int greenButtonPin = 47; //Pump Into Sample Container
const int blueButtonPin = 48; //Read Current Sample Set
const int blackButtonPin = 46;
const int ledPin = 13;
int ledState = LOW;

int redButtonState;
int redButtonLastState = LOW;
int greenButtonState = 0;
int greenButtonLastState = LOW;
int blueButtonState;
int blueButtonLastState = LOW;
int blackButtonState = 0;
int blackButtonLastState = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void buttonSetup() {
  pinMode(redButtonPin, INPUT);
  pinMode(greenButtonPin, INPUT);
  pinMode(blueButtonPin, INPUT);
  pinMode(blackButtonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, ledState);
}

void readRedButton() {
  int redReading = digitalRead(redButtonPin);

  if (redReading != redButtonLastState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (redReading != redButtonState) {
      redButtonState = redReading;

      if (redButtonState == HIGH) {
        ledState = !ledState;
        //digitalWrite(COMPRESSOR_PIN, ledState);
      }
    }
  }
  //digitalWrite(COMPRESSOR_PIN, ledState);
  digitalWrite(ledPin, ledState);
  redButtonLastState = redReading;
}

void readGreenButton() {
  greenButtonState = digitalRead(greenButtonPin);

  if (greenButtonState == HIGH) {
    //samplePumpOutStart();
    samplePumpInStart();
  } else {
    //samplePumpInStop();
    samplePumpInStop();
  }

}

void readBlueButton() { //Sample Container Sensor Data
  int blueReading = digitalRead(blueButtonPin);

  if (blueReading != blueButtonLastState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (blueReading != blueButtonState) {
      blueButtonState = blueReading;

      if (blueButtonState == HIGH) {
        ledState = !ledState;
        containerData[0] = getTemp();
        containerData[1] = readpH();
        containerData[2] = readElectricalConductivity();
        containerData[3] = readOxygen();
        containerData[4] = 0;
        containerData[5] = readSpecA();
        containerData[6] = readSpecB();
        containerData[7] = readSpecC();
        containerData[8] = readSpecD();
        containerData[9] = readSpecE();
        containerData[10] = readSpecF();
        containerData[11] = readSpecG();
        containerData[12] = readSpecH();
        containerData[13] = readSpecI();
        containerData[14] = readSpecJ();
        containerData[15] = readSpecK();
        containerData[16] = readSpecL();
        containerData[17] = readSpecR();
        containerData[18] = readSpecS();
        containerData[19] = readSpecT();
        containerData[20] = readSpecU();
        containerData[21] = readSpecV();
        containerData[22] = readSpecW();

        Serial.println("Sample");
        delay(1500);
        for (int i = 0; i < 23; i++) {
          Serial.println(containerData[i]);
          delay(2000);
       }
      }
    }
  }
  digitalWrite(ledPin, ledState);
  blueButtonLastState = blueReading;
}

void readBlackButton() {
  int blackReading = digitalRead(blackButtonPin);

  if (blackReading != blackButtonLastState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (blackReading != blackButtonState) {
      blackButtonState = blackReading;

      if (blackButtonState == HIGH) {
        readReactor();
      }      
    }
  }
  digitalWrite(ledPin, ledState);
  blackButtonLastState = blackReading;
}

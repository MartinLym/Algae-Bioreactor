int incomingByte = 0; // for incoming serial data
const int RELAY_PIN = 7;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
}

void loop() {
  digitalWrite(RELAY_PIN, HIGH); // turn on pump 5 seconds
  delay(3000);
  digitalWrite(RELAY_PIN, LOW);  // turn off pump 5 seconds
  delay(3000);
  /*
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    if (incomingByte == 49) {
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println(incomingByte, DEC);
    } else if(incomingByte == 50){
      digitalWrite(RELAY_PIN, LOW);
      Serial.println(incomingByte, DEC);
    }

  }
  */
}

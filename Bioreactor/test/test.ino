unsigned long blinkRate = 1000; //Default 1000 milliseconds between blinks
 
void setup() {
  pinMode(13,OUTPUT); // LED on pin 13
  Serial.begin(9600);   //Start the serial port
  Serial.println("Enter the blink delay length in milliseconds (try 100)");
}

void loop() {
  
    //If there is anything on the serial port for the Maker Board to read...
  if (Serial.available() > 0){
    //set blinkRate equal to the value you typed in the serial monitor
    blinkRate = Serial.parseInt();
    Serial.println(blinkRate);
  }
    
    digitalWrite(13,HIGH);
    delay(blinkRate);
    digitalWrite(13,LOW);
    delay(blinkRate);   
 }

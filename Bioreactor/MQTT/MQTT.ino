#include <PubSubClient.h>
#include <WiFi.h>
#include <HardwareSerial.h>

HardwareSerial mySerial(0);

WiFiClient espClient;
PubSubClient client(espClient);

const char* ssid     = "Optus_46E299";
const char* password = "dearytweetabdQK";

const char* mqtt_server = "192.168.0.24";

int lastMsg = 0;
int value = 0;
String val;
char *topics[] = {"mega/temperature", "test"};

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ArduinoClient")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("test");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  if (mySerial.available()) {
    for(int i = 0; i<2; i++){
      val = Serial.readString();
      int str_len = val.length() + 1;
      char char_array[str_len];
      Serial.println(val);
      val.toCharArray(char_array, str_len);
      //client.publish(topics[i], char_array);
      //Serial.write(Serial.read());
    }
    
  }
  
}

void readSensorData(){
  if (Serial.available()){
    
  }
}

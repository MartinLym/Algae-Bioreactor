#include <PubSubClient.h>
#include <WiFi.h>
#include <HardwareSerial.h>

HardwareSerial mySerial(0);

WiFiClient espClient;
PubSubClient client(espClient);

const char* ssid     = "Optus_46E299";
const char* password = "dearytweetabdQK";

const char* mqtt_server = "192.168.0.24";

int value = 0;
String val;
char *sampleTopics[] = {"sampleSensor/temperature", "sampleSensor/pH", "sampleSensor/conductivity", "sampleSensor/DO", "sampleSensor/litre","sampleSensor/channelA",
                        "sampleSensor/channelB", "sampleSensor/channelC", "sampleSensor/channelD", "sampleSensor/channelE", "sampleSensor/channelF",
                        "sampleSensor/channelG", "sampleSensor/channelH", "sampleSensor/channelR", "sampleSensor/channelI", "sampleSensor/channelS",
                        "sampleSensor/channelJ", "sampleSensor/channelT", "sampleSensor/channelU", "sampleSensor/channelV", "sampleSensor/channelW",
                        "sampleSensor/channelK", "sampleSensor/channelL"};

char *reactorTopics[] = {"reactorSensor/CO2", "reactorSensor/pressure", "reactorSensor/R", "reactorSensor/G", "reactorSensor/B"};                     


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
    if (client.connect("ESP32")) {
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

  sendSampleData();
  sendReactorData();
  /*
  for (int j = 0; j < sizeof(reactorTopics); j++){
    val = j;
    int str_len = val.length() + 1;
    char char_array[str_len];
    val.toCharArray(char_array, str_len);
    client.publish(reactorTopics[j], char_array);
    delay(250);
  }
  for (int i = 0; i < sizeof(sampleTopics); i++){
    val = i;
    int str_len = val.length() + 1;
    char char_array[str_len];
    val.toCharArray(char_array, str_len);
    client.publish(sampleTopics[i], char_array);
    delay(250);
  }
  client.endPublish();

  
  
  /*
  if (mySerial.available()) {
    for(int i = 0; i < sizeof(sampleTopics); i++){
      val = Serial.readString();
      int str_len = val.length() + 1;
      char char_array[str_len];
      Serial.println(val);
      val.toCharArray(char_array, str_len);
      //client.publish(sampleTopics[i], char_array);
      //Serial.write(Serial.read());
    }
    
  }
  */
}

void sendSampleData(){
  int lastMsg = 0;
  unsigned long reactorTimer = millis();
  if (reactorTimer - lastMsg > 10000) {
    lastMsg = reactorTimer;
    client.publish(reactorTopics[0], "0");
    client.publish(reactorTopics[1], "1");
    client.publish(reactorTopics[2], "2");
    client.publish(reactorTopics[3], "3");
    client.publish(reactorTopics[4], "4");
    delay(200);
  }
}

void sendReactorData(){
  int lastMsg = 0;
  unsigned long sampleTimer = millis();
  if (sampleTimer - lastMsg > 10000) {
    lastMsg = sampleTimer;
    client.publish(sampleTopics[0], "0");
    client.publish(sampleTopics[1], "1");
    client.publish(sampleTopics[2], "2");
    client.publish(sampleTopics[3], "3");
    client.publish(sampleTopics[4], "4");
    client.publish(sampleTopics[5], "5");
    client.publish(sampleTopics[6], "6");
    client.publish(sampleTopics[7], "7");
    client.publish(sampleTopics[8], "8");
    client.publish(sampleTopics[9], "9");
    client.publish(sampleTopics[10], "10");
    client.publish(sampleTopics[11], "11");
    client.publish(sampleTopics[12], "12");
    client.publish(sampleTopics[13], "13");
    client.publish(sampleTopics[14], "14");
    client.publish(sampleTopics[15], "15");
    client.publish(sampleTopics[16], "16");
    client.publish(sampleTopics[17], "17");
    client.publish(sampleTopics[18], "18");
    client.publish(sampleTopics[19], "19");
    client.publish(sampleTopics[20], "20");
    client.publish(sampleTopics[21], "21");
    client.publish(sampleTopics[22], "22");
    delay(200);
  }
}

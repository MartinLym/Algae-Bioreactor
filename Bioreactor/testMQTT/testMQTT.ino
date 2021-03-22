/*
 Reconnecting MQTT example - non-blocking

 This sketch demonstrates how to keep the client connected
 using a non-blocking reconnect function. If the client loses
 its connection, it attempts to reconnect every 5 seconds
 without blocking the main loop.

*/

#include <PubSubClient.h>
#include <WiFi.h>

WiFiClient espClient;
PubSubClient client(espClient);

// Update these with values suitable for your hardware/network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
const char* ssid     = "Optus_46E299";
const char* password = "dearytweetabdQK";

const char* mqtt_server = "192.168.0.24";
char *sampleTopics[] = {"sampleSensor/temperature", "sampleSensor/pH", "sampleSensor/conductivity", "sampleSensor/DO", "sampleSensor/litre","sampleSensor/channelA",
                        "sampleSensor/channelB", "sampleSensor/channelC", "sampleSensor/channelD", "sampleSensor/channelE", "sampleSensor/channelF",
                        "sampleSensor/channelG", "sampleSensor/channelH", "sampleSensor/channelR", "sampleSensor/channelI", "sampleSensor/channelS",
                        "sampleSensor/channelJ", "sampleSensor/channelT", "sampleSensor/channelU", "sampleSensor/channelV", "sampleSensor/channelW",
                        "sampleSensor/channelK", "sampleSensor/channelL"};

char *reactorTopics[] = {"reactorSensor/CO2", "reactorSensor/pressure", "reactorSensor/R", "reactorSensor/G", "reactorSensor/B"};                     

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

String val;
long lastReconnectAttempt = 0;

boolean reconnect() {
  if (client.connect("arduinoClient")) {
    // Once connected, publish an announcement...
    client.publish("outTopic","hello world");
    // ... and resubscribe
    client.subscribe("inTopic");
  }
  return client.connected();
}

void setup()
{
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  lastReconnectAttempt = 0;
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

void loop()
{
  if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected

    client.loop();
  }

  for (int j = 0; j < sizeof(reactorTopics); j++){
    val = j;
    int str_len = val.length() + 1;
    char char_array[str_len];
    val.toCharArray(char_array, str_len);
    client.publish(reactorTopics[j], char_array);
    delay(250);
  }

}

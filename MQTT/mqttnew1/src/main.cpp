/*
SIMPLE MQTT CONNECTION
*/

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "ABA_ROBOTICS2";
const char* password = "aba1234567";
const char* mqtt_server = "192.168.0.138";

WiFiClient espClient;
PubSubClient client(espClient);
char msg[50];
int value = 0;
const char* device_name = "ESP32";

void setup_wifi() {
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
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();    

  if (String(topic) == "my_topic") {
    client.publish("my_topic2","esp32_1");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect(device_name)) {
      Serial.println("connected");
      client.subscribe("my_topic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 1 second");
      
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
#include <WiFi.h>

const char* ssid = "ABA_ROBOTICS2";
const char* password = "aba1234567";
const uint16_t port = 8090;
const char* host = "192.168.0.138"; // 138
unsigned long start;
WiFiClient client;

void setup() {
  Serial.begin(115200);
  Serial.println("starting");
  
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("...");
  }
  
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  client.connect(host, port);
  
   if (!client.connect(host, port)) {
   Serial.println("Connection to host failed");
   delay(1000);
   return;
  }
}

void loop() {
  start = millis();
  
  client.print("Hello from ESP32!");

//  while (!client.available()){
//    Serial.println("not receiving data");
//    }
  Serial.print("Receiving : ");
  Serial.println(String(client.read()));

  Serial.print("elapsed :");
  Serial.println(millis()-start);

  //Serial.println("Disconnecting...");
  //client.stop();

  delay(500);
}

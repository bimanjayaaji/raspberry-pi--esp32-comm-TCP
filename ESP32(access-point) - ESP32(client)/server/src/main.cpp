// Import required libraries
#include <Arduino.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

// Set your access point network credentials
const char* ssid = "ABA_ROBOTICS"; // "ESP32-Access-Point"
const char* password = "aba1234567"; // "12345678"

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // WiFi.begin(ssid, password);

  // Serial.print("Connecting");
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println();

  // Serial.print("Connected, IP address: ");
  // Serial.println(WiFi.localIP());

  server.on("/var1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "1");
  });
  server.on("/var2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "2");
  });
  server.on("/var3", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "3");
  });
  
  // Start server
  server.begin();
}
 
void loop(){
  
}

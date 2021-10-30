#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ABA_ROBOICS2"; // "ESP32-Access-Point"
const char* password = "aba1234567"; // "12345678"

//Your IP address or domain name with URL path
const char* serverNameVar1 = "http://192.168.4.1/var1";
const char* serverNameVar2 = "http://192.168.4.1/var2";
const char* serverNameVar3 = "http://192.168.4.1/var3";

String var1;
String var2;
String var3;

unsigned long previousMillis = 0;
const long interval = 500; 
unsigned long start;
unsigned long end;

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval) {
    // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED ){
      start = millis(); 
      var1 = httpGETRequest(serverNameVar1);
      var2 = httpGETRequest(serverNameVar2);
      var3 = httpGETRequest(serverNameVar3);
      Serial.println(var1);
      Serial.println(var2);
      Serial.println(var3);
      Serial.println(millis()-start);

      // save the last HTTP GET Request
      previousMillis = currentMillis;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
}
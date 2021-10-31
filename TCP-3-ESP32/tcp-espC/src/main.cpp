/*
Source Code ESP32 TCP-Communication
ESP - C
*/

/* 
    kurang fitur detect message
    -> 'A' : respon ping - ...
    -> 'B' : print time - ...
*/

#include <Arduino.h>
#include <WiFi.h>

const char* ssid     = "ABA_ROBOTICS2";
const char* password = "aba1234567";

const char* host_target = "192.168.0.151";
const int port_target = 8088;

WiFiServer server(8000);
WiFiClient client;
String local_IP;
IPAddress sender_IP;
uint16_t sender_port;

unsigned long loop_start;
unsigned long start;
uint8_t data[30];

void connect2wifi(){
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected with IP address: ");
    Serial.println(WiFi.localIP());
    local_IP = WiFi.localIP().toString();
}

void connect2default(){
    Serial.print("Connecting to : "); Serial.println(host_target);
    while (!client.connect(host_target,port_target)) {
        delay(500);
    }
    Serial.print("Connected to : "); Serial.println(host_target);
}

void disconnect(){
    client.stop();
    Serial.println("Disconnected");
}

void initiator(){
    loop_start = millis();
    client.print("ping from " + local_IP);
    Serial.print("PING sent to"); Serial.println(host_target);
}

void get_ping(){
    Serial.print("Waiting to get msg ... ");
    int x = 0;
    while (x == 0){
        WiFiClient client = server.available(); 

        if (client) {
            Serial.println("Msg incoming"); 
            while (client.connected()) {   
                if (client.available()) {
                    int len = client.read(data, 30);    
                    client.print("response from " + local_IP);
                    Serial.print("Msg : "); Serial.println((char *)data);
                    Serial.print("Response sent to :"); Serial.println(client.remoteIP());
                    x = 1;
                    break; 
                }
            } 
        }
    }
}

void get_response(){
    Serial.println("Waiting for response...");
    int x = 0;
    while (x == 0){
        if (client.available()) {
            int len = client.read(data, 30);    
            Serial.print("C Y C L E - T I M E: "); Serial.println(millis()-loop_start);
            Serial.print("Res : "); Serial.println((char *)data);
            x = 1;
        }
    }
    disconnect();
    delay(10);
}

void delaying(){
    Serial.println("Delaying 10secs");
    unsigned long start = millis();
    unsigned long timeout = start + 10000;
    while (millis() < timeout);
}

void setup()
{
    Serial.begin(115200);
    connect2wifi();
    server.begin();
}

void loop()
{
    Serial.println("");
    get_ping();

    Serial.println("");
    disconnect();

    Serial.println("");
    delaying();

    Serial.println("");
    connect2default();

    Serial.println("");
    initiator();

    Serial.println("");
    get_response();
}



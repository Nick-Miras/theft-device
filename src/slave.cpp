#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUDP.h>

const char* ssid = "ESP32-AP";
const char* password = "12345678";

WiFiUDP udp;
const char* hostIP = "192.168.4.1"; // Default IP of ESP32 SoftAP
unsigned int hostPort = 4210;

unsigned long lastSendTime = 0;
const unsigned long interval = 1000; // Send heartbeat every 1 sec

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to AP...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to AP");
  udp.begin(WiFi.localIP());
}

void loop() {
  if (millis() - lastSendTime > interval) {
    udp.beginPacket(hostIP, hostPort);
    udp.print("HEARTBEAT");
    udp.endPacket();
    Serial.println("Heartbeat sent");
    lastSendTime = millis();
  }

  // Optional: detect disconnection from AP
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Disconnected from AP!");
    // Optionally: try reconnecting here
  }
}
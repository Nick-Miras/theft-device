#include <Arduino.h>
#include "master.h"

const char* ssid = "ESP32-AP";
const char* password = "12345678";

HeartbeatReceiver heartbeat(4210);

void setup() {
    Serial.begin(115200);
    WiFi.softAP(ssid, password);
    Serial.println("Started AP");
    heartbeat.begin();
}

void loop() {
    heartbeat.loop();
    if (heartbeat.isDisconnected()) {
        Serial.println("Client disconnected!");
        delay(5000); // Avoid spamming
    }
}
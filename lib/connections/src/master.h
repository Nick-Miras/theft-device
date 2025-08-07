#ifndef CONNECTION_H
#define CONNECTION_H

#include <WiFi.h>
#include <WiFiUDP.h>

class HeartbeatReceiver {
public:
    HeartbeatReceiver(unsigned int port, unsigned long timeoutMs = 5000)
      : _port(port), _timeout(timeoutMs), _lastReceived(0) {}

    void begin() {
        _udp.begin(_port);
    }

    bool loop() {
        int packetSize = _udp.parsePacket();
        if (packetSize) {
            char incoming[255];
            int len = _udp.read(incoming, 255);
            if (len > 0) incoming[len] = 0;
            _lastReceived = millis();
            return true;
        }
        return false;
    }

    bool isDisconnected() {
        return (millis() - _lastReceived) > _timeout;
    }

private:
    WiFiUDP _udp;
    unsigned int _port;
    unsigned long _timeout;
    unsigned long _lastReceived;
};

#endif
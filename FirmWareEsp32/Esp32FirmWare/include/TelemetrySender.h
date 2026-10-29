#pragma once

#include <WiFi.h>
#include <WiFiUdp.h>
#include <cstdint>

class TelemetrySender {
  public:
    TelemetrySender(IPAddress ip, uint16_t port)
        : destination_ip_(ip), destination_port_(port) {}

    bool sendAttitude(float roll, float pitch, float yaw);

  private:
    WiFiUDP udp_;

    IPAddress destination_ip_;
    uint16_t destination_port_;
};
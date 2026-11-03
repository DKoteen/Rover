#pragma once

#include <WiFi.h>
#include <WiFiUdp.h>
#include <cstdint>

class TelemetrySender {
  public:
    TelemetrySender(uint16_t port)
        : destination_port_(port) {}

    void setDestination(IPAddress ip);

    bool sendAttitude(float roll, float pitch, float yaw);

  private:
    WiFiUDP udp_;

    std::optional<IPAddress> destination_ip_;
    uint16_t destination_port_;
};
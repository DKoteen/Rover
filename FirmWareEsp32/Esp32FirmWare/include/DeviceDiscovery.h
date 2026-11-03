#pragma once

#include <WiFi.h>
#include <WiFiUdp.h>
#include <cstdint>
#include <optional>

class DeviceDiscovery {
public:
    bool begin(uint16_t port = 45455);

    bool update();

    std::optional<IPAddress> getDeviceIP() const;

private:
    WiFiUDP udp_;

    std::optional<IPAddress> device_ip_;
};
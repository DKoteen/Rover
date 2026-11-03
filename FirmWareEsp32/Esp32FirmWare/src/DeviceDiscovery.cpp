#include "DeviceDiscovery.h"
#include <cstring>

bool DeviceDiscovery::begin(uint16_t port) {
    return udp_.begin(port) == 1;
}

bool DeviceDiscovery::update() {
    if (udp_.parsePacket() <= 0) {
        return false;
    }

    char buffer[32]{};

    int bytes_read = udp_.read(
        buffer,
        sizeof(buffer) - 1
    );

    if (bytes_read != 14 ||
        std::strcmp(buffer, "ROVER_DISCOVER") != 0) {
        return false;
    }

    IPAddress sender_ip = udp_.remoteIP();
    uint16_t sender_port = udp_.remotePort();

    udp_.beginPacket(sender_ip, sender_port);
    udp_.print("ROVER_HERE");
    udp_.endPacket();

    device_ip_ = sender_ip;

    return true;
}

std::optional<IPAddress> DeviceDiscovery::getDeviceIP() const {
    return device_ip_;
}

#include "TelemetrySender.h"

bool TelemetrySender::sendAttitude(float roll, float pitch, float yaw) {
    char packet[80];

    int length = snprintf(
        packet,
        sizeof(packet),
        "ATTITUDE:%.2f,%.2f,%.2f\n",
        roll,
        pitch,
        yaw
    );

    if (length <= 0 || static_cast<size_t>(length) >= sizeof(packet)) {

        return false;
    }

    if (WiFi.status() != WL_CONNECTED) {
        return false;
    }

    if (!udp_.beginPacket(destination_ip_, destination_port_)) {
        return false;
    }

    size_t written = udp_.write(
        reinterpret_cast<const uint8_t *>(packet),
        static_cast<size_t>(length)
    );

    bool sent = udp_.endPacket() == 1;

    return written == static_cast<size_t>(length) && sent;
}

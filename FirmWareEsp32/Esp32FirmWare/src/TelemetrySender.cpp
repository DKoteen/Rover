#include "TelemetrySender.h"

void TelemetrySender::setDestination(IPAddress ip) {
    destination_ip_ = ip;
}

bool TelemetrySender::sendAttitude(int sequence_number, float roll, float pitch, float yaw) {
    if (!destination_ip_.has_value()) {
        return false;
    }

    char packet[80];

    int length = snprintf(
        packet,
        sizeof(packet),
        "ATTITUDE:%lu,%.2f,%.2f,%.2f\n",
        sequence_number,
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

    if (!udp_.beginPacket(*destination_ip_, destination_port_)) {
        return false;
    }

    size_t written = udp_.write(
        reinterpret_cast<const uint8_t *>(packet),
        static_cast<size_t>(length)
    );

    bool sent = udp_.endPacket() == 1;

    return written == static_cast<size_t>(length) && sent;
}

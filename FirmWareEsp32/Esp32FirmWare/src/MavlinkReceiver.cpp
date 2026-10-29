#include "MavlinkReceiver.h"

#include "../lib/mavlink/ardupilotmega/mavlink.h"

void MavlinkReceiver::begin() { fc_serial_.begin(115200, SERIAL_8N1, 16, 17); }

bool MavlinkReceiver::readAttitude() {
    mavlink_message_t message{};
    mavlink_status_t status{};

    while (fc_serial_.available() > 0) {

        uint8_t byte = fc_serial_.read();

        if (mavlink_parse_char(MAVLINK_COMM_0, byte, &message, &status)) {

            if (message.msgid == MAVLINK_MSG_ID_ATTITUDE) {

                mavlink_attitude_t attitude{};

                mavlink_msg_attitude_decode(&message, &attitude);

                telemetry_.roll = attitude.roll * 180.0f / PI;
                telemetry_.pitch = attitude.pitch * 180.0f / PI;
                telemetry_.yaw = attitude.yaw * 180.0f / PI;

                telemetry_.attitude_valid = true;

                return true;
            }
        }
    }

    return false;
}

const TelemetryData &MavlinkReceiver::getData() const { return telemetry_; }

#include <Arduino.h>
#include <mavlink/ardupilotmega/mavlink.h>

HardwareSerial fcSerial(2);

mavlink_message_t message{};
mavlink_status_t status{};

void setup() {
    Serial.begin(115200);
    fcSerial.begin(115200, SERIAL_8N1, 16, 17);
}

void loop() {
    while (fcSerial.available() > 0) {

        uint8_t byte = fcSerial.read();

        if (mavlink_parse_char(
                MAVLINK_COMM_0,
                byte,
                &message,
                &status)) {

            if (message.msgid == MAVLINK_MSG_ID_ATTITUDE) {

                mavlink_attitude_t attitude{};

                mavlink_msg_attitude_decode(
                    &message,
                    &attitude
                );

                float roll = attitude.roll * 180.0f / PI;
                float pitch = attitude.pitch * 180.0f / PI;
                float yaw = attitude.yaw * 180.0f / PI;

                Serial.print("ATTITUDE:");
                Serial.print(roll, 2);
                Serial.print(",");
                Serial.print(pitch, 2);
                Serial.print(",");
                Serial.println(yaw, 2);
            }
        }
    }
}
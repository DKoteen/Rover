#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiManager.h>
#include <Arduino.h>
#include <mavlink/ardupilotmega/mavlink.h>

HardwareSerial fcSerial(2);
WiFiUDP udp;

constexpr uint16_t TELEMETRY_PORT = 45454;
IPAddress pcIp(192, 168, 0, 104);

mavlink_message_t message{};
mavlink_status_t status{};

void setup() {
    Serial.begin(115200);
    fcSerial.begin(115200, SERIAL_8N1, 16, 17);

    WiFiManager wifiManager;

    wifiManager.setConfigPortalTimeout(180);

    bool connected = wifiManager.autoConnect(
        "Rover-Setup",
        "esp32pass"
    );
    if (connected) {
        Serial.println("WiFi connected!");
        Serial.print("ESP32 IP: ");
        Serial.println(WiFi.localIP());

        Serial.print("PC IP: ");
        Serial.println(pcIp);

        Serial.print("Gateway: ");
        Serial.println(WiFi.gatewayIP());
    } else {
        Serial.println("WiFi not connected");
    }
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

                char packet[80];

                int length = snprintf(
                    packet,
                    sizeof(packet),
                    "ATTITUDE:%.2f,%.2f,%.2f\n",
                    roll,
                    pitch,
                    yaw
                );

                if (length <= 0 ||
                    static_cast<size_t>(length) >= sizeof(packet)) {

                    Serial.println("Packet formatting error");

                } else {
                    Serial.print(packet);

                    if (WiFi.status() == WL_CONNECTED) {

                        if (udp.beginPacket(
                                pcIp,
                                TELEMETRY_PORT)) {

                            udp.write(
                                reinterpret_cast<const uint8_t*>(packet),
                                static_cast<size_t>(length)
                            );

                            udp.endPacket();
                        }
                    }
                }
            }
        }
    }
}
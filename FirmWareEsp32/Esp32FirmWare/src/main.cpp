#include "DeviceDiscovery.h"
#include "MavlinkReceiver.h"
#include "TelemetrySender.h"
#include "WifiConnection.h"
#include <Arduino.h>

constexpr uint16_t CONNECTION_PORT = 45455;
constexpr uint16_t TELEMETRY_PORT = 45454;

// Подключение wifi
WifiConnection wifi_connection;

// Подключение mavlink -> esp32
MavlinkReceiver mavlink_receiver;

// Находим pc_ip
DeviceDiscovery dev_disc;

// Подключение отправки телеметрии esp32 -> Qt
TelemetrySender telemetry_sender(TELEMETRY_PORT);

void setup() {
    WiFi.setSleep(false);
    
    Serial.begin(115200);

    mavlink_receiver.begin();

    if (wifi_connection.begin()) {
        Serial.println("WiFi connected");

        Serial.print("Local IP: ");
        Serial.println(WiFi.localIP());

        if (dev_disc.begin(CONNECTION_PORT)) {
            Serial.println("Discovery UDP ready");
        } else {
            Serial.println("Discovery UDP ERROR");
        }
    }
}

void loop() {
    if (dev_disc.update()) {
        auto ip = dev_disc.getDeviceIP();
        if (ip.has_value()) {
            telemetry_sender.setDestination(*ip);
            Serial.println("PC connected!");
        }
    }

while (mavlink_receiver.readAttitude()) {
    static uint32_t last_attitude_ms = 0;

    uint32_t now = millis();

    if (last_attitude_ms != 0) {
        uint32_t interval = now - last_attitude_ms;

        if (interval > 200) {
            Serial.printf(
                "ESP32 ATTITUDE interval: %lu ms\n",
                static_cast<unsigned long>(interval)
            );
        }
    }

    last_attitude_ms = now;

    const TelemetryData& data = mavlink_receiver.getData();

    bool send = telemetry_sender.sendAttitude(
        data.sequence_number,
        data.roll,
        data.pitch,
        data.yaw
    );
    if (!send) {
        Serial.println("UDP send error");
    }
}
}
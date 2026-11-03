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
    Serial.begin(115200);

    mavlink_receiver.begin();

    if (wifi_connection.begin()) {
        dev_disc.begin(CONNECTION_PORT);
        Serial.println("Wifi connected");
    } else {
        Serial.println("Wifi not connected");
    }
}

void loop() {
    if (dev_disc.update()) {
        auto ip = dev_disc.getDeviceIP();

        if (ip.has_value()) {
            telemetry_sender.setDestination(*ip);
        }
    }

    while (mavlink_receiver.readAttitude()) {
        const TelemetryData& data = mavlink_receiver.getData();

        telemetry_sender.sendAttitude(
            data.roll,
            data.pitch,
            data.yaw
        );
    }
}
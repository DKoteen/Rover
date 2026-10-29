#include <Arduino.h>
#include "WifiConnection.h"
#include "TelemetrySender.h"
#include "MavlinkReceiver.h"

// Подключение wifi
WifiConnection wifi_connection;

// Подключение mavlink -> esp32
MavlinkReceiver mavlink_receiver;

// Подключение отправки телеметрии esp32 -> Qt
constexpr uint16_t TELEMETRY_PORT = 45454;
IPAddress pcIp(192, 168, 0, 108);
TelemetrySender telemetry_sender(pcIp, TELEMETRY_PORT);

void setup() {
    Serial.begin(115200);

    mavlink_receiver.begin();

    if (wifi_connection.begin()) {
        Serial.println("Wifi connected");
    } else {
        Serial.println("Wifi not connected");
    }
}

void loop() {
    while (mavlink_receiver.readAttitude()) {
        const TelemetryData& data = mavlink_receiver.getData();

        telemetry_sender.sendAttitude(
            data.roll,
            data.pitch,
            data.yaw
        );
    }
}
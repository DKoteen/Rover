#include "WifiConnection.h"

#include <WiFi.h>
#include <WiFiManager.h>

bool WifiConnection::begin() {
    WiFiManager wifi_manager;
    wifi_manager.setConfigPortalTimeout(180);

    bool connected = wifi_manager.autoConnect(
        "Rover-Setup",
        "esp32pass"
    );

    return connected;
}

bool WifiConnection::isConnected() const {
    return WiFi.status() == WL_CONNECTED;
}

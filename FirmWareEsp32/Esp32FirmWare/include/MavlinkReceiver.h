#pragma once

#include <Arduino.h>
#include "TelemetryData.h"

class MavlinkReceiver {
public:
    void begin();

    bool readAttitude();

    const TelemetryData& getData() const;
private:
    HardwareSerial fc_serial_{2};

    TelemetryData telemetry_;
};
#pragma once

struct TelemetryData {
    float roll = 0.0f;
    float pitch = 0.0f;
    float yaw = 0.0f;

    bool attitude_valid = false;
};
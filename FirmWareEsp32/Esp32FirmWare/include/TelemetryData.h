#pragma once

struct TelemetryData {
    uint32_t sequence_number = 0;

    float roll = 0.0f;
    float pitch = 0.0f;
    float yaw = 0.0f;

    bool attitude_valid = false;
};
#pragma once

struct RoverState {
    // Координаты ровера в метрах
    double x = 0.0;
    double y = 0.0;

    // Ориентация ровера в градусах
    float roll = 0.0f;
    float pitch = 0.0f;
    float yaw = 0.0f;

    // Состояние
    bool connected = false;
    bool positionValid = false;
};
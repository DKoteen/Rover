#include "rovercontroller.h"

RoverController::RoverController(QObject* parent)
    : QObject(parent) {
}

void RoverController::setAttitude(float roll, float pitch, float yaw) {
    if (state_.roll != roll) {
        state_.roll = roll;
        emit rollChanged();
    }
    if (state_.pitch != pitch) {
        state_.pitch = pitch;
        emit pitchChanged();
    }
    if (state_.yaw != yaw) {
        state_.yaw = yaw;
        emit yawChanged();
    }
}

float RoverController::GetRoll() const{
    return state_.roll;
}

float RoverController::GetPitch() const{
    return state_.pitch;
}

float RoverController::GetYaw() const{
    return state_.yaw;
}
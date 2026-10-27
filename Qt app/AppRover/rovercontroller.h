#pragma once

#include <QObject>
#include "roverstate.h"

class RoverController : public QObject {
    Q_OBJECT

    Q_PROPERTY(float roll_qml READ GetRoll NOTIFY rollChanged)
    Q_PROPERTY(float pitch_qml READ GetPitch NOTIFY pitchChanged)
    Q_PROPERTY(float yaw_qml READ GetYaw NOTIFY yawChanged)

public:
    explicit RoverController(QObject* parent = nullptr);

    Q_INVOKABLE void setAttitude(float roll, float pitch, float yaw);

    float GetRoll() const;
    float GetPitch() const;
    float GetYaw() const;

signals:
    void rollChanged();
    void pitchChanged();
    void yawChanged();

private:
    RoverState state_;
};
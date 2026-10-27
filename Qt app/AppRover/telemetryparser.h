#pragma once

#include <QObject>
#include <QByteArray>

class TelemetryParser : public QObject {
    Q_OBJECT

public:
    explicit TelemetryParser(QObject* parent = nullptr);

    void addData(const QByteArray& data);

signals:
    void attitudeReceived(float roll, float pitch, float yaw);

private:
    void parseLine(const QByteArray& line);

    QByteArray buffer_;
};
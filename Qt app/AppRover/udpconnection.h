#pragma once

#include <QObject>
#include <QByteArray>
#include <QUdpSocket>

class UdpConnection : public QObject {
    Q_OBJECT

public:
    explicit UdpConnection(QObject* parent = nullptr);

    bool start(quint16 port = 45454);

signals:
    void dataReceived(const QByteArray& data);

private:
    void readPendingDatagrams();

    QUdpSocket socket_;
};
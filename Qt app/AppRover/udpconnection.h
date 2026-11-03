#pragma once

#include <QObject>
#include <QByteArray>
#include <QUdpSocket>
#include <QTimer>

struct Ports {
    static constexpr quint16 port_read_data = 45454;
    static constexpr quint16 port_write_find_esp32 = 45455;
};

class UdpConnection : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)

public:
    explicit UdpConnection(QObject* parent = nullptr);

    bool start(quint16 port = Ports::port_read_data);
    bool isConnected();

signals:
    void dataReceived(const QByteArray& data);
    void connectedChanged();

private:
    void readPendingDatagrams();
    void sendDiscovery();
    void connectionTimeout();

    QUdpSocket socket_;
    QTimer discovery_timer_;
    QTimer connection_timer_;

    bool device_found_ = false;

    QHostAddress device_ip_;
};
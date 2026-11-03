#include "udpconnection.h"

#include <QHostAddress>
#include <QNetworkDatagram>
#include <QDebug>

UdpConnection::UdpConnection(QObject *parent) : QObject(parent) {
    QObject::connect(
        &socket_,
        &QUdpSocket::readyRead,
        this,
        &UdpConnection::readPendingDatagrams
        );

    QObject::connect(
        &discovery_timer_,
        &QTimer::timeout,
        this,
        &UdpConnection::sendDiscovery
        );

    connection_timer_.setSingleShot(true);

    QObject::connect(
        &connection_timer_,
        &QTimer::timeout,
        this,
        &UdpConnection::connectionTimeout
        );
}

bool UdpConnection::start(quint16 port) {
    // Начинаем слушать UDP-порт
    bool success = socket_.bind(
        QHostAddress::AnyIPv4,
        port
        );

    if (success) {
        qDebug() << "UDP listening on port:" << port;
        sendDiscovery();
        discovery_timer_.start(2000);
    } else {
        qWarning() << "UDP error:"
                   << socket_.errorString();
    }

    return success;
}

void UdpConnection::readPendingDatagrams() {
    while (socket_.hasPendingDatagrams()) {

        QNetworkDatagram datagram = socket_.receiveDatagram();

        if (!datagram.isValid()) {
            qWarning() << "Invalid UDP datagram";
            continue;
        }

        QByteArray message = datagram.data();

        if (message == "ROVER_HERE") {
            device_found_ = true;
            device_ip_ = datagram.senderAddress();

            discovery_timer_.stop();
            connection_timer_.start(1000);

            qDebug() << "ESP32 found:"
                     << datagram.senderAddress();

            continue;
        }

        if (device_found_ &&
            datagram.senderAddress() == device_ip_) {

            connection_timer_.start(1000);

            emit dataReceived(message);
        }
    }
}

void UdpConnection::sendDiscovery() {
    if (device_found_) {
        return;
    }

    QByteArray message = "ROVER_DISCOVER";

    qint64 written = socket_.writeDatagram(
        message,
        QHostAddress::Broadcast,
        Ports::port_write_find_esp32
        );

    if (written == message.size()) {
        qDebug() << "Discovery request sent";
    } else {
        qWarning() << "Discovery error:"
                   << socket_.errorString();
    }
}

void UdpConnection::connectionTimeout() {
    device_found_ = false;
    device_ip_ = QHostAddress();

    qWarning() << "ESP32 connection lost";

    sendDiscovery();
    discovery_timer_.start(2000);
}
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
}

bool UdpConnection::start(quint16 port) {
    // Начинаем слушать UDP-порт
    bool success = socket_.bind(
        QHostAddress::AnyIPv4,
        port
        );

    if (success) {
        qDebug() << "UDP listening on port:" << port;
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

        emit dataReceived(datagram.data());
    }
}

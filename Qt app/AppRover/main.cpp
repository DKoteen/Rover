
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "rovercontroller.h"
#include "telemetryparser.h"
#include "udpconnection.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    RoverController rover_controller;
    TelemetryParser parser;
    UdpConnection udp_connect;

    QObject::connect(
        &udp_connect,
        &UdpConnection::dataReceived,
        &parser,
        &TelemetryParser::addData
        );

    // Парсер сообщает новые углы контроллеру
    QObject::connect(
        &parser,
        &TelemetryParser::attitudeReceived,
        &rover_controller,
        &RoverController::setAttitude
        );

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(
        "roverController",
        &rover_controller
        );

    udp_connect.start();

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() {
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
        );

    engine.loadFromModule("AppRover", "Main");

    return app.exec();
}

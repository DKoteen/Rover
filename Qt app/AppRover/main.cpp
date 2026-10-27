#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QByteArray>
#include "telemetryparser.h"
#include "rovercontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QSerialPort serial;
    RoverController rover_controller;
    TelemetryParser mavlink_parser;


    serial.setPortName("COM7");
    serial.setBaudRate(115200);
    if (serial.open(QIODevice::ReadOnly)) {
        qDebug() << "ESP32 connected!";
    } else {
        qDebug() << "Connection error:" << serial.errorString();
    }

    // QSerialPort → TelemetryParser
    QObject::connect(
        &serial,
        &QSerialPort::readyRead,
        &mavlink_parser,
        [&serial, &mavlink_parser]() {
            QByteArray data = serial.readAll();
            qDebug() << "readyRead:"
                     << data.size()
                     << "bytes:"
                     << data;

            mavlink_parser.addData(data);
        }
        );

    // TelemetryParser → RoverController
    QObject::connect(&mavlink_parser,
                     &TelemetryParser::attitudeReceived,
                     &rover_controller,
                     &RoverController::setAttitude);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(
        "roverController",
        &rover_controller
        );

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("AppRover", "Main");

    return QGuiApplication::exec();
}

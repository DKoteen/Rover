#include "telemetryparser.h"

TelemetryParser::TelemetryParser(QObject *parent) : QObject(parent) {}

void TelemetryParser::addData(const QByteArray& data) {

    // Добавляем новые байты в буфер
    buffer_.append(data);

    // Ищем символ конца строки
    qsizetype pos = buffer_.indexOf('\n');

    while (pos != -1) {

        // Извлекаем готовую строку
        QByteArray line = buffer_.left(pos).trimmed();

        // Удаляем обработанную строку из буфера
        buffer_.remove(0, pos + 1);

        // Отправляем строку на разбор
        parseLine(line);

        // Ищем следующее сообщение
        pos = buffer_.indexOf('\n');
    }

    // Ограничиваем размер неполного сообщения
    if (buffer_.size() > 128) {
        buffer_.clear();
    }
}

void TelemetryParser::parseLine(const QByteArray& line) {
    if (line.startsWith("ATTITUDE:")) {
        QByteArray values = line.mid(9);
        QList list = values.split(',');
        if (list.size() != 4) {
            return;
        }
        bool okSequenceNumber = false;
        bool okRoll = false;
        bool okPitch = false;
        bool okYaw = false;
        int sequence_number = list[0].toInt(&okSequenceNumber);
        float roll = list[1].toFloat(&okRoll);
        float pitch = list[2].toFloat(&okPitch);
        float yaw = list[3].toFloat(&okYaw);

        if (!okSequenceNumber || !okRoll || !okPitch || !okYaw) {
            return;
        }

        emit attitudeReceived(sequence_number, roll, pitch, yaw);
    }
}
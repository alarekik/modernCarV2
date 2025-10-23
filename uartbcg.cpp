#include "uartbcg.h"
#include "qdebug.h"
uartBCG::uartBCG(QObject *parent)
    : QObject(parent)
    ,m_serialport(new QSerialPort(this))
    ,magicWord{0x0F, 0x0F}
{
    connect(m_serialport, &QSerialPort::readyRead, this, &uartBCG::Readbcg);
}

bool uartBCG::openPort()
{
    QByteArray datatestbcg;
    QString messagetestbcg;
    bool foundbcg = false;
    QString portname;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Port:" << info.portName()
        << "| Description:" << info.description()
        << "| Vendor ID:" << info.vendorIdentifier()
        << "| Product ID:" << info.productIdentifier();
        if (info.vendorIdentifier() == 4292 && info.productIdentifier() == 60016) {
        QSerialPort *testPort = new QSerialPort(info);
        testPort->setBaudRate(QSerialPort::Baud115200);
        testPort->setDataBits(QSerialPort::Data8);
        testPort->setParity(QSerialPort::NoParity);
        testPort->setStopBits(QSerialPort::OneStop);
        testPort->setFlowControl(QSerialPort::NoFlowControl);
            if (testPort->open(QIODevice::ReadOnly)) {
                qDebug() << "Testing port:" << info.portName();
                if (testPort->waitForReadyRead(200)) {
                    datatestbcg = testPort->readAll();
                    messagetestbcg = QString::fromLatin1(datatestbcg.toHex(' ').toUpper());
                    qDebug() << "Received data:" << messagetestbcg;
                    if (!messagetestbcg.isEmpty() ) {
                        qDebug() << "Communication port found:" << info.portName();
                        testPort->close();
                        delete testPort;
                        m_serialport->setPortName(info.portName());
                        m_serialport->setBaudRate(QSerialPort::Baud115200);
                        m_serialport->setDataBits(QSerialPort::Data8);
                        m_serialport->setParity(QSerialPort::NoParity);
                        m_serialport->setStopBits(QSerialPort::OneStop);
                        m_serialport->setFlowControl(QSerialPort::NoFlowControl);
                        if (m_serialport->open(QIODevice::ReadOnly)) {
                            foundbcg = true;
                            break;
                        }
                        else {
                            qDebug() << "Failed to open m_serialport.";
                        }

                    }
                }
                testPort->close();
            }
            else {
                qDebug() << "Failed to open test port" <<info.portName();
            }
            delete testPort;
        }
    }
    if (!foundbcg) {
        qDebug() << "No communication port found.";
        return false;
    }
    else {
        qDebug() << "communication port found";
        return true;
    }
}
QString uartBCG::lastheartValue() const
{
    return heartValue;
}

QString uartBCG::lastbreathValue() const
{
    return breathValue;
}



void uartBCG::Readbcg()
{
    buffer += m_serialport->readAll();
    qDebug() << "bufeer"<<QString::fromLatin1(buffer.toHex(' ').toUpper());;
    while (true) {
        int index = buffer.indexOf(QByteArray::fromRawData(reinterpret_cast<const char*>(magicWord), 2));
        if (index == -1) {
            // No magic word found yet
            break;
        }

        if (buffer.size() < index + 2 + 16) {
            // Wait until full frame is available
            break;
        }
        QByteArray frame = buffer.mid(index + 2, 16);
        qDebug() << "Frame received:" << frame.toHex(' ');
        // Extract bytes 11, 10, 12, 13 from the frame
        quint8 byte11 = static_cast<quint8>(frame[11]);
        quint8 byte10 = static_cast<quint8>(frame[10]);
        quint8 byte12 = static_cast<quint8>(frame[12]);
        quint8 byte13 = static_cast<quint8>(frame[13]);

        // Combine bytes 11 and 10 for heart rate (high byte first)
        quint16 heartRate = (byte11 << 8) | byte10;

        // Combine bytes 13 and 12 for breath rate (high byte first)
        quint16 breathRate = (byte13 << 8) | byte12;

        // Convert to QString for display
        heartValue  = QString::number(heartRate);
        breathValue = QString::number(breathRate);

        // Debug output
        qDebug() << "[SERIAL] Heart Rate:" << heartRate;
        qDebug() << "[SERIAL] Breath Rate:" << breathRate;


        emit bcgdatarecived(heartValue,breathValue);

        // Remove processed data from buffer
        buffer.remove(0, index + 2 + 16);
    }


}

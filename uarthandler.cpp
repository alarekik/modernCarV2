#include "uarthandler.h"
#include "qdebug.h"

uarthandler::uarthandler(QObject *parent)
    : QObject(parent)
    ,m_serialport(new QSerialPort(this))
{
    connect(m_serialport, &QSerialPort::readyRead, this, &uarthandler::onReadyRead);

}

bool uarthandler::openPort()
{
    QByteArray datatest;
    QString messagetest;
    bool found = false;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Port:" << info.portName()
        << "| Description:" << info.description()
        << "| Vendor ID:" << info.vendorIdentifier()
        << "| Product ID:" << info.productIdentifier();
        if (info.vendorIdentifier() == 4292 && info.productIdentifier() == 60016) {
            QSerialPort *testPort = new QSerialPort(info);
            testPort->setBaudRate(QSerialPort::Baud9600);
            testPort->setDataBits(QSerialPort::Data8);
            testPort->setParity(QSerialPort::NoParity);
            testPort->setStopBits(QSerialPort::OneStop);
            testPort->setFlowControl(QSerialPort::NoFlowControl);
            if (testPort->open(QIODevice::ReadOnly)) {
                qDebug() << "Testing port:" << info.portName();
                if (testPort->waitForReadyRead(200)) {
                    datatest = testPort->readAll();
                    messagetest = QString::fromLatin1(datatest.toHex(' ').toUpper());
                    qDebug() << "Received data:" << messagetest;
                    if (!messagetest.isEmpty()) {
                        qDebug() << "Communication port found:" << info.portName();
                        testPort->close();
                        delete testPort;
                        m_serialport->setPortName(info.portName());
                        m_serialport->setBaudRate(QSerialPort::Baud9600);
                        m_serialport->setDataBits(QSerialPort::Data8);
                        m_serialport->setParity(QSerialPort::NoParity);
                        m_serialport->setStopBits(QSerialPort::OneStop);
                        m_serialport->setFlowControl(QSerialPort::NoFlowControl);
                        if (m_serialport->open(QIODevice::ReadOnly)) {
                            found = true;
                            break;  // ✅ Stop testing once a valid port is found
                        } else {
                            qDebug() << "Failed to open m_serialport.";
                        }
                    }
                }
                testPort->close();
            } else {
                qDebug() << "Failed to open test port:" << info.portName();
            }
            delete testPort;
        }
    }
    if (!found) {
        qDebug() << "No communication port found.";
        return false;
    }
    return true;
}

QString uarthandler::lastMessage() const
{
    return m_lastMessage;
}

void uarthandler::onReadyRead()
{
    QByteArray data = m_serialport->readAll();
    QString message = QString::fromLatin1(data.toHex(' ').toUpper());
    m_lastMessage = message;
    qDebug() << "[SERIAL]" << "Received:" << message;
    emit dataReceived(message);
}

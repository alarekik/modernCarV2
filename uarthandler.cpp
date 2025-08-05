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
    // foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
    //     if (info.hasProductIdentifier() && info.productIdentifier() == 60016) {
    //         m_serialport->setPort(info);
    //         break;
    //     }
    // }
    //---------------------------------------------------------------------------

        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            qDebug() << "Port:" << info.portName()
            << "| Description:" << info.description()
            << "| Vendor ID:" << info.vendorIdentifier()
            << "| Product ID:" << info.productIdentifier();

            // Match by Product ID and Vendor ID
            if (info.vendorIdentifier() == 4292 && info.productIdentifier() == 60016) {
                m_serialport->setPort(info);
                m_serialport->setBaudRate(QSerialPort::Baud9600);
                m_serialport->setDataBits(QSerialPort::Data8);
                m_serialport->setParity(QSerialPort::NoParity);
                m_serialport->setStopBits(QSerialPort::OneStop);
                m_serialport->setFlowControl(QSerialPort::NoFlowControl);

                if (m_serialport->open(QIODevice::ReadOnly)) {
                    qDebug() << "Connected to" << info.portName();
                    return true;
                } else {
                    qDebug() << "Failed to open port" << info.portName();
                    return false;
                }
                qDebug() << "Target device not found.";
            }


        }
        qDebug() << "Target device not found.";
        return false;





    //-----------------------------------------------------------------------------
    // foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
    //     if (info.vendorIdentifier()==4292 && info.productIdentifier() == 60016){
    //         m_serialport->setPort(info);
    //         m_serialport->setBaudRate(QSerialPort::Baud9600);
    //         m_serialport->setDataBits(QSerialPort::Data8);
    //         m_serialport->setParity(QSerialPort::NoParity);
    //         m_serialport->setStopBits(QSerialPort::OneStop);
    //         m_serialport->setFlowControl(QSerialPort::NoFlowControl);
    //         m_serialport->open(QIODevice::ReadOnly);
    //     }

    // }
    //------------------------------------------------
    // m_serialport->setPortName("/dev/ttyUSB2");
    // m_serialport->setBaudRate(QSerialPort::Baud9600);
    // m_serialport->setDataBits(QSerialPort::Data8);
    // m_serialport->setParity(QSerialPort::NoParity);
    // m_serialport->setStopBits(QSerialPort::OneStop);
    // m_serialport->setFlowControl(QSerialPort::NoFlowControl);
    // m_serialport->open(QIODevice::ReadOnly);
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

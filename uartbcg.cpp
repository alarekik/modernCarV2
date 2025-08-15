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
    QString portname;
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){

        if (info.vendorIdentifier() == 1027 && info.productIdentifier() == 24577) {

            portname = info.portName();

        }
    }
    m_serialport->setPortName(portname);
    m_serialport->setBaudRate(QSerialPort::Baud9600);
    m_serialport->setDataBits(QSerialPort::Data8);
    m_serialport->setParity(QSerialPort::NoParity);
    m_serialport->setStopBits(QSerialPort::OneStop);
    m_serialport->setFlowControl(QSerialPort::NoFlowControl);
    if (m_serialport->open(QIODevice::ReadWrite)) {
        qDebug() << "Connected to BCG!";
        return true;
    }
    else {
        qDebug() << "not Connected to BCG!";
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

        // Extract 16-byte payload after magic word
        QByteArray frame = buffer.mid(index + 2, 16);
        qDebug() << "Frame received:" << frame.toHex(' ');
        //-----extract the byte of heart and breath ----------
        QByteArray segmentheart = frame.mid(10, 2);
        QByteArray segmentbreath = frame.mid(12, 2);
        //---------convert to dec value ----------------
        quint16 valueB = static_cast<quint8>(segmentheart[0]) << 8 | static_cast<quint8>(segmentheart[1]);
        quint16 valueH = static_cast<quint8>(segmentbreath[0]) << 8 | static_cast<quint8>(segmentbreath[1]);

        heartValue      =QString::number(valueH);
        breathValue     =QString::number(valueB) ;
        emit bcgdatarecived();

        // Remove processed data from buffer
        buffer.remove(0, index + 2 + 16);
    }


}

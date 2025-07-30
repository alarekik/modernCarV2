#include "canhandler.h"
#include <QCanBus>
#include <QCanBusFrame>
#include <QDebug>
//quint32 frameId, const QByteArray &data
CanHandler::CanHandler(QObject *parent)
    : QObject(parent)
    , m_canDevice(nullptr)
{
}

bool CanHandler::Connected() const
{
    return m_canDevice && m_canDevice->state() == QCanBusDevice::ConnectedState;
}

void CanHandler::connectToCanBus(const QString &interfaceName)
{
    if (m_canDevice) {
        disconnectFromCanBus();
    }

    QString pluginName = "socketcan";
    m_canDevice = QCanBus::instance()->createDevice(pluginName, interfaceName);
    m_canDevice->setConfigurationParameter(QCanBusDevice::BitRateKey, 125000);
    m_canDevice->setConfigurationParameter(QCanBusDevice::CanFdKey, false);
    if (!m_canDevice) {
        emit errorMessage("Failed to create CAN device");
        qDebug() << "failed";
        return;
    }

    connect(m_canDevice, &QCanBusDevice::framesReceived, this, [this]() {
        while (m_canDevice && m_canDevice->framesAvailable()) {
            const QCanBusFrame frame = m_canDevice->readFrame();
            if (frame.frameType() == QCanBusFrame::DataFrame) {
                QString id = QString::number(frame.frameId(), 16);
                QString data;
                for (int i = 0; i < frame.payload().size(); ++i) {
                    data += QString::number(static_cast<uchar>(frame.payload().at(i)), 16).rightJustified(2, '0');
                }
                emit messageReceived(id, data);
            }
        }
    });

    connect(m_canDevice, &QCanBusDevice::errorOccurred, this, [this]() {
        if (m_canDevice) {
            emit errorMessage(m_canDevice->errorString());
        }
    });

    if (!m_canDevice->connectDevice()) {
        emit errorMessage("Failed to connect: " + m_canDevice->errorString());
        delete m_canDevice;
        m_canDevice = nullptr;
    } else {
        emit connectionChanged();
    }
}

void CanHandler::disconnectFromCanBus()
{
    if (m_canDevice) {
        m_canDevice->disconnectDevice();
        delete m_canDevice;
        m_canDevice = nullptr;
        emit connectionChanged();
    }
}

bool CanHandler::sendCanMessage()
{

    quint32 frameId=0x123;
    QByteArray data;
    data.append(10);


    if (!m_canDevice || !m_canDevice->state() == QCanBusDevice::ConnectedState) {
        emit errorMessage("CAN device not connected");
        return false;
    }

    QCanBusFrame frame;
    frame.setFrameId(frameId);
    frame.setPayload(data);
    frame.setFrameType(QCanBusFrame::DataFrame);

    return m_canDevice->writeFrame(frame);
}

void CanHandler::sendMessage(const QString &id, const QString &data)
{
    bool ok;
    quint32 frameId = id.toUInt(&ok, 16);
    if (!ok) {
        emit errorMessage("Invalid frame ID");
        return;
    }

    QByteArray payload;
    QString cleanData = data.simplified().remove(' ');

    for (int i = 0; i < cleanData.length(); i += 2) {
        QString byteString = cleanData.mid(i, 2);
        bool byteOk;
        uchar byte = static_cast<uchar>(byteString.toUInt(&byteOk, 16));
        if (!byteOk) {
            emit errorMessage("Invalid data format");
            return;
        }
        payload.append(byte);
    }

    if (!sendCanMessage()) {
        emit errorMessage("Failed to send message");
    }
}

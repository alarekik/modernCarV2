#include "canhandler.h"

canhandler::canhandler(QObject *parent)
    : QObject{parent}
{}

void canhandler::sendCanMessage()
{

        QCanBusDevice *canDevice = QCanBus::instance()->createDevice("socketcan", "can0");

        if (canDevice && canDevice->connectDevice()) {
            // qDebug() << "Connected to CAN bus";

            // Create a CAN frame
            QCanBusFrame frame;
            frame.setFrameId(0x123); // Set the frame ID
            frame.setPayload(QByteArray("Hello")); // Set payload data

            // Send the frame
            if (canDevice->writeFrame(frame)) {
                //qDebug() << "CAN frame sent successfully";
            } else {
                //qWarning() << "Failed to send CAN frame:" << canDevice->errorString();
            }

            // Disconnect from the CAN bus
            canDevice->disconnectDevice();
        } else {
            //qWarning() << "Failed to connect to CAN bus:" ;
        }

        // Delete the CAN
        delete canDevice;

}

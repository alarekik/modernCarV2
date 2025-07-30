#ifndef CANHANDLER_H
#define CANHANDLER_H

#include <QObject>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>

class CanHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool Connected READ isConnected NOTIFY connectionChanged)

public:
    explicit CanHandler(QObject *parent = nullptr);

    Q_INVOKABLE bool isConnected() const;

public slots:
    Q_INVOKABLE void connectToCanBus(const QString &interfaceName = "can0");
    Q_INVOKABLE void disconnectFromCanBus();
    Q_INVOKABLE bool sendCanMessage();
    Q_INVOKABLE void sendMessage(const QString &id, const QString &data);

signals:
    void connectionChanged();
    void messageReceived(const QString &id, const QString &data);
    void errorMessage(const QString &error);


//creat a canbus device instance
private:
    QCanBusDevice *m_canDevice;
};

#endif // CANHANDLER_H

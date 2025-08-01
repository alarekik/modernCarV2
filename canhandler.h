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
    Q_PROPERTY(QString lastMessageId READ lastMessageId NOTIFY messageUpdated)
    Q_PROPERTY(QString lastMessageData READ lastMessageData NOTIFY messageUpdated)
public:
    explicit CanHandler(QObject *parent = nullptr);

    Q_INVOKABLE bool isConnected() const;
    QString lastMessageId() const;
    QString lastMessageData() const;
public slots:
    Q_INVOKABLE void connectToCanBus(const QString &interfaceName = "can0");
    Q_INVOKABLE void disconnectFromCanBus();
    Q_INVOKABLE bool sendCanMessage();
    Q_INVOKABLE void sendMessage(const QString &id, const QString &data);

signals:
    void connectionChanged();
    void messageReceived(const QString &id, const QString &data);
    void errorMessage(const QString &error);
    void messageUpdated();

//creat a canbus device instance
private:
    QCanBusDevice *m_canDevice;
    QString messageid;
    QString messagedata;
};

#endif // CANHANDLER_H

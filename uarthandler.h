#ifndef UARTHANDLER_H
#define UARTHANDLER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class uarthandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString lastMessage READ lastMessage NOTIFY dataReceived)
public:
    explicit uarthandler(QObject *parent = nullptr);
    bool openPort();
    QString lastMessage() const;
private slots :
    void onReadyRead();
private :
    QSerialPort *m_serialport;
    QString m_lastMessage;
signals:
    void dataReceived(const QString &message);
};

#endif // UARTHANDLER_H

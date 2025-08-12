#ifndef UARTHANDLER_H
#define UARTHANDLER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class uarthandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString lastMessage READ lastMessage NOTIFY dataReceived)
    //-----------------bcg
    // Q_PROPERTY(QString lastMessagebcg READ lastMessagebcg NOTIFY dataRecivedBCG)
public:
    explicit uarthandler(QObject *parent = nullptr);
    bool openPort();
    QString lastMessage() const;
    //-----------bcg--
    // QString lastMessagebcg() const;
private slots :
    void onReadyRead();
    //--------------bcg
    // void onReadyReadbcg();

private :
    QSerialPort *m_serialport;

    QString m_lastMessage;
    //----bcg-----
    // QSerialPort *m_BCGport;
    // QString m_lastMessageBCG;
signals:
    void dataReceived(const QString &message);
    //----------bcg--------
    // void dataRecivedBCG(const QString &message_bcg);
};

#endif // UARTHANDLER_H

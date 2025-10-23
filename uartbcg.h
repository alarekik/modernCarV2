#ifndef UARTBCG_H
#define UARTBCG_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class uartBCG : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString lastheartValue READ lastheartValue NOTIFY bcgdatarecived)
    Q_PROPERTY(QString lastbreathValue READ lastbreathValue NOTIFY bcgdatarecived)
public:
    explicit uartBCG(QObject *parent = nullptr);
    bool openPort();
    QString lastheartValue() const;
    QString lastbreathValue() const;
private slots :
    void Readbcg();
private :
    QSerialPort *m_serialport;

    QString heartValue;
    QString breathValue;
    const char magicWord[2];
    QByteArray buffer;

signals:
    void bcgdatarecived(const QString &messageH,const QString &messageB);

};

#endif // UARTBCG_H

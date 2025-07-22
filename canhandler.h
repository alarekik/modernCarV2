#ifndef CANHANDLER_H
#define CANHANDLER_H

#include <QObject>
#include <QtDebug>
#include<QCanBusDevice>
#include <QCanBus>

class canhandler : public QObject
{
    Q_OBJECT

public:
    explicit canhandler(QObject *parent = nullptr);
    void sendCanMessage();
signals:
};

#endif // CANHANDLER_H

#ifndef GPIOHANDLER_H
#define GPIOHANDLER_H

#include <QObject>
#include <QTimer>

class gpiohandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int gpioValue READ gpioValue NOTIFY gpioValueChanged)

public:
    explicit gpiohandler(QObject *parent = nullptr);
    ~gpiohandler();

    int gpioValue() const { return m_gpioValue; }

public slots:
    void readGpio();

signals:
    void gpioValueChanged();

private:
    struct gpiod_chip *m_chip = nullptr;
    struct gpiod_line *m_line = nullptr;
    int m_gpioValue = 0;
    QTimer *m_timer;
};
#endif

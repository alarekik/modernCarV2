#include "gpiohandler.h"

#include <QDebug>

#define GPIO_CHIP "/dev/gpiochip6"
#define GPIO_LINE 14

gpiohandler::gpiohandler(QObject *parent)
    : QObject(parent)
{
    // Open chip and get line
    m_chip = gpiod_chip_open(GPIO_CHIP);
    if (!m_chip) {
        qWarning() << "Failed to open" << GPIO_CHIP;
        return;
    }

    m_line = gpiod_chip_get_line_info(m_chip, GPIO_LINE);
    if (!m_line) {
        qWarning() << "Failed to get line" << GPIO_LINE;
        gpiod_chip_close(m_chip);
        return;
    }

    if (gpiod_line_request_get_fd(m_line, "qml_gpio_reader") < 0) {
        qWarning() << "Failed to request input line";
        gpiod_line_request(m_line);
        gpiod_chip_close(m_chip);
        return;
    }

    // Setup periodic reading
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &gpiohandler::readGpio);
    m_timer->start(200); // read every 200 ms
}

gpiohandler::~gpiohandler()
{
    if (m_line)
        gpiod_line_request(m_line);
    if (m_chip)
        gpiod_chip_close(m_chip);
}

void gpiohandler::readGpio()
{
    if (!m_line) return;

    int val = gpiod_line_value(m_line);
    if (val < 0) {
        qWarning() << "Failed to read GPIO value";
        return;
    }

    if (val != m_gpioValue) {
        m_gpioValue = val;
        emit gpioValueChanged();
    }
}

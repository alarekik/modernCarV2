#include "gpiohandler.h"
#include <gpiod.h>
#include <QDebug>

gpiohandler::gpiohandler(QObject *parent)
    : QObject(parent)
{
    try {
        // Open the GPIO chip
        m_chip = std::make_unique<gpiod::chip>(GPIO_CHIP_NAME);

        // Configure the line for input
        gpiod::line_settings settings;
        settings.set_direction(gpiod::line::direction::INPUT);
        // Optional: set bias if needed (e.g., PULL_UP)
        // settings.set_bias(gpiod::line::bias::PULL_UP);

        gpiod::line_config config;
        config.add_line_settings({GPIO_LINE_OFFSET}, settings);

        // Request the line
        m_lineRequest = std::make_unique<gpiod::line_request>(
            m_chip->request_lines(config, "qml_gpio_reader")
            );

        // Set up timer
        m_timer = new QTimer(this);
        connect(m_timer, &QTimer::timeout, this, &gpiohandler::readGpio);
        m_timer->start(200); // every 200 ms

        // Initial read
        readGpio();

    } catch (const std::exception& e) {
        qWarning() << "GPIO init failed:" << e.what();
        // You may want to emit an error signal here
    }
}

gpiohandler::~gpiohandler()
{
    // No manual cleanup needed — unique_ptr and RAII handle everything
    // The line is released automatically when m_lineRequest is destroyed
}

void gpiohandler::readGpio()
{
    if (!m_lineRequest) {
        return;
    }

    try {
        int newValue = m_lineRequest->get_value(GPIO_LINE_OFFSET);
        if (newValue != m_gpioValue) {
            m_gpioValue = newValue;
            emit gpioValueChanged();
        }
    } catch (const std::exception& e) {
        qWarning() << "Failed to read GPIO:" << e.what();
    }
}

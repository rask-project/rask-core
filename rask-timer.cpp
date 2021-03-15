#ifdef __cpp_exceptions

#include "rask-timer.h"
#include <iostream>

namespace Rask {
namespace Object {

Timer::Timer(const char *objName) : 
    m_args(),
    m_callback(nullptr),
    m_interval(0)
{
    m_args.callback = onTimeout;
    m_args.arg = this;
    m_args.name = objName;
    m_args.dispatch_method = ESP_TIMER_TASK;

    esp_timer_create(&m_args, &m_handler);
}

Timer::~Timer()
{
    esp_timer_stop(m_handler);
    esp_timer_delete(m_handler);
}

void Timer::onTimeout(void *arg)
{
    auto *timer = static_cast<Timer *>(arg);
    try {
        if (timer->m_callback == nullptr)
            throw RaskException::ObjectException(RaskException::Error::NoFunctionDefined);
        timer->m_callback();
    } catch (const RaskException::ObjectException& e) {
        std::cerr << "Error: " << timer->getObjectName() << " - " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Error: " << timer->getObjectName() << " - " << e.what() << '\n';
    }
}

void Timer::start()
{
    try {
        if (m_interval.count() == 0)
                throw RaskException::ObjectException(RaskException::Error::TimerIntervalInvalid);
            esp_timer_start_periodic(m_handler, m_interval.count());
    } catch (const RaskException::ObjectException& e) {
        std::cerr << "Error: " << getObjectName() << " - " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Error: " << getObjectName() << " - " << e.what() << '\n';
    }
}

} // Object
} // Rask

#endif
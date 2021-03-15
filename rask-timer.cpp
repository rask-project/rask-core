#ifdef __cpp_exceptions

#include "rask-timer.h"
#include <iostream>

namespace Rask {
namespace Object {

Timer::Timer(const char *objName) : 
    m_args(),
    m_callback(),
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
    try {
        auto *timer = static_cast<Timer *>(arg);
        timer->m_callback();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

} // Object
} // Rask

#endif
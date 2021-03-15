#pragma once

#ifdef __cpp_exceptions

#include <esp_timer.h>
#include <functional>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include "rask-object-exception.h"

namespace Rask {
namespace Object {
/**
 * @brief Timer Object
 */
class Timer
{
    esp_timer_create_args_t m_args;
    esp_timer_handle_t m_handler;
    std::function<void()> m_callback;
    std::chrono::microseconds m_interval;

public:
    /**
     * @brief Construct a new Timer object
     * @param objName - Timer name
     * @param callback - lambda to be executed when timeout
     */
    explicit Timer(const char *objName = "");

    /**
     * @brief Destroy the Timer object
     */
    ~Timer();

    Timer(const Timer&) = delete;
    Timer &operator=(const Timer&) = delete;

    inline void setCallback(std::function<void()> callback)
    {
        m_callback = callback;
    }

    template <typename Rep, typename Period>
    inline void setInterval(std::chrono::duration<Rep, Period> interval)
    {
        m_interval = std::chrono::microseconds(interval);
    }

    /**
     * @brief Start timer
     */
    inline void start()
    {
        if (m_interval.count() == 0)
            throw RaskException::ObjectException(RaskException::Error::TimerIntervalInvalid);
        esp_timer_start_periodic(m_handler, m_interval.count());
    }

    /**
     * @brief Start timer with interval
     * @param interval std::chrono::duration
     */
    template <typename Rep, typename Period>
    inline void start(std::chrono::duration<Rep, Period> interval)
    {
        setInterval(interval);
        start();
    }

    /**
     * @brief Start single shot timer
     * @param interval std::chrono::duration
     */
    template <typename Rep, typename Period>
    void singleShot(std::chrono::duration<Rep, Period> interval)
    {
        esp_timer_start_once(m_handler, std::chrono::microseconds(interval).count());
    }

    /**
     * @brief Stop timer
     */
    inline void stop()
    {
        std::cout << "Stop timer\n";
        esp_timer_stop(m_handler);
    }

private:
    /**
     * @brief onTimeout - Take this as an argument and execute the callback function
     * @param arg - this class
     */
    static void onTimeout(void *arg);
};

} // Object
} // Rask

#endif
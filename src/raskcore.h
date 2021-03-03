#pragma once

#include <map>
#include <Arduino.h>
#include "raskobject.h"

/**
 * @brief Loops event for execution of timers and pseudo-threads
 */
class RaskCore
{
public:
    /**
     * @brief Construct a new Rask Core object
     */
    RaskCore() = default;
    /**
     * @brief Destroy the Rask Core object
     */
    ~RaskCore() = default;

    /**
     * @brief Run the events queue
     */
    static void exec();

    /**
     * @brief Create an event loop and execute the queue
     */
    [[ noreturn ]] static void loop();

    /**
     * @brief Adds a timer event
     * @param event pointer of RaskObject
     */
    static void addEvent(RaskObject *event);

    /**
     * @brief Removes a timer event
     * @param event pointer of RaskObject
     */
    static void removeEvent(RaskObject *event);

private:
    static std::map<std::string, RaskObject *> m_events;
};

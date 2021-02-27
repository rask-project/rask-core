#pragma once

#include <map>
#include "raskobject.h"

/**
 * @brief Event loop
 */
class RaskCore
{
public:
    RaskCore() = default;
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

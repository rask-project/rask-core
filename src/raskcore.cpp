#include "raskcore.h"
#include <sstream>

std::string pointerStr(RaskObject *event)
{
    const void *address = static_cast<const void *>(event);
    std::stringstream addr;
    addr << address;

    return addr.str();
}

std::map<std::string, RaskObject *> RaskCore::m_events {};

void RaskCore::exec()
{
    for (auto it = m_events.begin(); it != std::end(m_events); ++it) {
        auto &event = it->second;

        if (!event->running())
            continue;

        if (millis() - event->lastRun() >= event->interval()) {
            event->setLastRun(millis());
            event->timeout.emit();

            if (event->isSingleShot()) {
                event->stopTimer();
                m_events.erase(it);
                continue;
            }
        }
    }
}

void RaskCore::loop()
{
    while (true) {
        exec();
    }
}

void RaskCore::addEvent(RaskObject *event)
{
    m_events[pointerStr(event)] = event;
}

void RaskCore::removeEvent(RaskObject *event)
{
    auto item = std::find_if(std::begin(m_events), std::end(m_events), [&](const std::pair<std::string, RaskObject *> &item) { return item.first == pointerStr(event); });
    if (item != std::end(m_events))
        m_events.erase(item);
}

#pragma once

#include <map>
#include "raskobject.h"

std::string pointerStr(RaskObject *event);

class RaskCore
{
public:
    RaskCore() = default;
    ~RaskCore() = default;

    [[ noreturn ]] static void exec();

    static void addEvent(RaskObject *event);

    static void removeEvent(RaskObject *event);

private:
    static std::map<std::string, RaskObject *> m_events;
};

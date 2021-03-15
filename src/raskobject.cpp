#include "raskobject.h"
#include "raskcore.h"

RaskObject::RaskObject():
    m_interval(0),
    m_lastRun(0),
    m_isSingleShot(false),
    m_running(false)
{}

RaskObject::~RaskObject()
{
    removeEventFromLoop();
}

unsigned long RaskObject::interval() const
{
    return m_interval;
}

void RaskObject::setInterval(unsigned long value)
{
    m_interval = value;
}

void RaskObject::startTimer()
{
    m_lastRun = millis();
    setRunning(true);
}

void RaskObject::startTimer(unsigned long value)
{
    m_interval = value;
    m_lastRun = millis();
    setRunning(true);
}

void RaskObject::stopTimer()
{
    setRunning(false);
}

unsigned long RaskObject::lastRun() const
{
    return m_lastRun;
}

void RaskObject::setLastRun(unsigned long value)
{
    if (m_running)
        m_lastRun = value;
}

bool RaskObject::isSingleShot() const
{
    return m_isSingleShot;
}

void RaskObject::singleShot(unsigned long value)
{
    m_interval = value;
    m_isSingleShot = true;
    m_running = true;
}

bool RaskObject::running() const
{
    return m_running;
}

void RaskObject::setRunning(bool value)
{
    m_running = value;
}

void RaskObject::removeEventFromLoop()
{
    RaskCore::removeEvent(this);
}

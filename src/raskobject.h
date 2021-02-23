#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>
#include <iostream>

template <typename ...Args>
class RaskSlot;

template <typename ...Args>
class RaskSignal
{
    RaskSignal(const RaskSignal &) = delete;
    RaskSignal(RaskSignal &&) = delete;
    RaskSignal &operator=(const RaskSignal &) = delete;

public:
    RaskSignal() = default;
    ~RaskSignal() = default;

    void emit(Args... args) { for (auto &it: m_slots) (*it)(args...); }

    inline void connect(RaskSlot<Args...> *slot) { m_slots.push_back(slot); }
    void disconnect(RaskSlot<Args...> *slot)
    {
        for (auto it = m_slots.begin(); it != m_slots.end(); ++it) {
            if (*it == slot) {
                m_slots.erase(it);
                break;
            }
        }
    }
    inline void disconnect() { m_slots.clear(); }

private:
    std::vector<RaskSlot<Args...> *> m_slots;
};

template <typename ...Args>
class RaskSlot
{
    RaskSlot(const RaskSlot &) = delete;
    RaskSlot(RaskSlot &&) = delete;
    RaskSlot &operator=(const RaskSlot &) = delete;

public:
    RaskSlot(RaskSignal<Args...> *parent = nullptr): 
        m_init(false), 
        m_signalParent(parent)
    {}
    RaskSlot(std::function<void(Args...)> callback, RaskSignal<Args...> *parent = nullptr): 
        m_init(true), 
        m_callback(callback),
        m_signalParent(parent)
    {}
    ~RaskSlot() 
    {
        if (m_signalParent != nullptr)
            m_signalParent->disconnect(this);
    };
    
    void operator()(Args... args) { call(args...); }
    inline void call(Args... args) { if (m_init) m_callback(args...); }

    inline void setCallback(std::function<void(Args...)> callback)
    {
        m_init = true;
        m_callback = callback;
    }

    inline void setSignalParent(RaskSignal<Args...> *parent) { m_signalParent = parent; }

private:
    bool m_init;
    std::function<void(Args...)> m_callback;
    RaskSignal<Args...> *m_signalParent;
};

/**
 * @brief The RaskObject class
 */
class RaskObject
{
    unsigned long m_interval;
    unsigned long m_lastRun;
    bool m_isSingleShot;
    bool m_running;

public:
    RaskObject();
    ~RaskObject();

    /**
     * @brief interval for timer
     * @return interval in ms
     */
    unsigned long interval() const;
    /**
     * @brief Set the Interval value
     * @param value unsigned long(ms)
     */
    void setInterval(unsigned long value);

    /**
     * @brief startTimer
     */
    void startTimer();
    /**
     * @brief startTimer
     * @param value unsigned long(ms)
     */
    void startTimer(unsigned long value);

    /**
     * @brief stopTimer
     */
    void stopTimer();

    /**
     * @brief lastRun get timer from last run
     * @return unsigned long(ms)
     */
    unsigned long lastRun() const;
    /**
     * @brief setLastRun set last timer run
     * @param value unsigned long)ms_
     */
    void setLastRun(unsigned long value);

    /**
     * @brief isSingleShot return if timer is single shot
     * @return boolean
     */
    bool isSingleShot() const;
    /**
     * @brief singleShot set interval and define with single shot
     * @param value unsigned long(ms)
     */
    void singleShot(unsigned long value);

    /**
     * @brief running return if timer is running
     * @return boolean
     */
    bool running() const;
    /**
     * @brief setRunning define wheter the timer should continue to run
     * @param value boolean
     */
    void setRunning(bool value);

// signals
    /**
     * @brief signal timeout
     */
    RaskSignal<> timeout;

private:
    RaskObject(const RaskObject &) = delete;
    RaskObject(RaskObject &&) = delete;
    RaskObject operator=(const RaskObject &) = delete;
    RaskObject operator=(RaskObject &&) = delete;

    void removeEventFromLoop();
};

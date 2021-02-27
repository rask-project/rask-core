#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>
#include <iostream>

template <typename ...Args>
class RaskSlot;

/**
 * @brief Signal emission template
 * @tparam Args
 */
template <typename ...Args>
class RaskSignal
{
    RaskSignal(const RaskSignal &) = delete;
    RaskSignal(RaskSignal &&) = delete;
    RaskSignal &operator=(const RaskSignal &) = delete;

public:
    RaskSignal() = default;
    ~RaskSignal() = default;

    /**
     * @brief Signal emission
     * @param args 
     */
    void emit(Args... args) { for (auto &it: m_slots) (*it)(args...); }

    /**
     * @brief Connects the slot to the signal
     * @param slot
     */
    inline void connect(RaskSlot<Args...> *slot) { m_slots.push_back(slot); }

    /**
     * @brief  Disconnect the slot of the signal
     * @param slot 
     */
    void disconnect(RaskSlot<Args...> *slot)
    {
        for (auto it = m_slots.begin(); it != m_slots.end(); ++it) {
            if (*it == slot) {
                m_slots.erase(it);
                break;
            }
        }
    }

    /**
     * @brief Disconnect all slots
     */
    inline void disconnect() { m_slots.clear(); }

private:
    std::vector<RaskSlot<Args...> *> m_slots;
};

/**
 * @brief Slot / callback to be executed when the signal is emitted
 * @tparam Args 
 */
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

    /**
     * @brief Set the Callback object to be executed
     * @param callback 
     */
    inline void setCallback(std::function<void(Args...)> callback)
    {
        m_init = true;
        m_callback = callback;
    }

    /**
     * @brief Set the Signal Parent object to remove slot when it is deleted
     * @param parent 
     */
    inline void setSignalParent(RaskSignal<Args...> *parent) { m_signalParent = parent; }

private:
    bool m_init;
    std::function<void(Args...)> m_callback;
    RaskSignal<Args...> *m_signalParent;
};

/**
 * @brief Contains properties to run the timer, 
 * often at intervals or single shot.
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
     * @brief Interval time defined
     * @return interval in ms
     */
    unsigned long interval() const;
    /**
     * @brief Set the Interval value
     * @param value unsigned long(ms)
     */
    void setInterval(unsigned long value);

    /**
     * @brief Start running the timer
     */
    void startTimer();
    /**
     * @brief startTimer
     * @param value unsigned long(ms)
     */
    void startTimer(unsigned long value);

    /**
     * @brief  Stop running the timer
     */
    void stopTimer();

    /**
     * @brief lastRun get timer from last run
     * @return unsigned long(ms)
     */
    unsigned long lastRun() const;
    /**
     * @brief Last timer run
     * @param value unsigned long(ms)
     */
    void setLastRun(unsigned long value);

    /**
     * @brief Return whether the timer is single shot
     * @return boolean
     */
    bool isSingleShot() const;
    /**
     * @brief Set timer as single shot
     * @param value unsigned long(ms)
     */
    void singleShot(unsigned long value);

    /**
     * @brief Returns whether the timer is running
     * @return boolean
     */
    bool running() const;
    /**
     * @brief Set whether the timer is running
     * @param value boolean
     */
    void setRunning(bool value);

/**
 * signals 
 */

    /**
     * @brief signal timeout
     */
    RaskSignal<> timeout;

private:
    RaskObject(const RaskObject &) = delete;
    RaskObject(RaskObject &&) = delete;
    RaskObject operator=(const RaskObject &) = delete;
    RaskObject operator=(RaskObject &&) = delete;

    /**
     * @brief Removes RaskObject from the event loop
     */
    void removeEventFromLoop();
};

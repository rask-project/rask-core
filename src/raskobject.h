#pragma once

#include <Arduino.h>
#include <string>
#include <vector>
#include <functional>

template <typename ...Args>
class RaskSlot;

/**
 * @brief Signal emission template
 * @tparam Arguments template. Ex: <int, bool, const char *>
 */
template <typename ...Args>
class RaskSignal
{
    RaskSignal(const RaskSignal &) = delete;
    RaskSignal(RaskSignal &&) = delete;
    RaskSignal &operator=(const RaskSignal &) = delete;

public:
    /**
     * @brief Construct a new Rask Signal object
     */
    RaskSignal() = default;
    /**
     * @brief Destroy the Rask Signal object
     */
    ~RaskSignal() = default;

    /**
     * @brief Signal emission
     * @param args Arguments template. Ex: <int, bool, const char *>
     */
    void emit(Args... args) { for (auto &it: m_slots) (*it)(args...); }

    /**
     * @brief Connects the slot to the signal
     * @param slot RaskSlot object reference
     */
    inline void connect(RaskSlot<Args...> *slot) { m_slots.push_back(slot); }

    /**
     * @brief Disconnect the slot of the signal
     * @param slot RaskSlot object reference
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
 * @tparam Arguments template. Ex: <int, bool, const char *>
 */
template <typename ...Args>
class RaskSlot
{
    RaskSlot(const RaskSlot &) = delete;
    RaskSlot(RaskSlot &&) = delete;
    RaskSlot &operator=(const RaskSlot &) = delete;

public:
    /**
     * @brief Construct a new Rask Slot object
     * @param parent Parent signal object
     */
    RaskSlot(RaskSignal<Args...> *parent = nullptr): 
        m_init(false), 
        m_signalParent(parent)
    {}
    /**
     * @brief Construct a new Rask Slot object
     * @param callback Function called when the signal is emitted
     * @param parent Parent signal object
     */
    RaskSlot(std::function<void(Args...)> callback, RaskSignal<Args...> *parent = nullptr): 
        m_init(true), 
        m_callback(callback),
        m_signalParent(parent)
    {}
    /**
     * @brief Destroy the Rask Slot object
     */
    ~RaskSlot() 
    {
        if (m_signalParent != nullptr)
            m_signalParent->disconnect(this);
    };
    
    void operator()(Args... args) { call(args...); }
    inline void call(Args... args) { if (m_init) m_callback(args...); }

    /**
     * @brief Set the Callback object to be executed
     * @param callback Function called when the signal is emitted
     */
    inline void setCallback(std::function<void(Args...)> callback)
    {
        m_init = true;
        m_callback = callback;
    }

    /**
     * @brief Set the Signal Parent object to remove slot when it is deleted
     * @param parent Parent signal object
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
    /**
     * @brief Construct a new Rask Object object
     */
    RaskObject();
    /**
     * @brief Destroy the Rask Object object
     */
    ~RaskObject();

    /**
     * @brief Interval time defined
     * @return interval in ms
     */
    unsigned long interval() const;
    /**
     * @brief Set the Interval value
     * @param value Timer interval in ms
     */
    void setInterval(unsigned long value);

    /**
     * @brief Start running the timer
     */
    void startTimer();
    /**
     * @brief Start running the timer at the specified interval
     * @param value Timer interval in ms
     */
    void startTimer(unsigned long value);

    /**
     * @brief Stop running the timer
     */
    void stopTimer();

    /**
     * @brief Last execution time
     * @return Last execution time in ms
     */
    unsigned long lastRun() const;
    /**
     * @brief Set last execution time
     * @param value Timer interval in ms
     */
    void setLastRun(unsigned long value);

    /**
     * @brief Return whether the timer is single shot
     * @return boolean
     */
    bool isSingleShot() const;
    /**
     * @brief Set timer as single shot
     * @param value Timer interval in ms
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

/** signals **/
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

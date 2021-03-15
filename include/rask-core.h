#pragma once

#include <vector>
#include <functional>
#include <iostream>

namespace Rask
{

template <typename ...Args>
class Slot;

/**
 * @brief Signal emission template
 * @tparam Arguments template. Ex: <int, bool, const char *>
 */
template <typename ...Args>
class Signal
{
    Signal(const Signal &) = delete;
    Signal(Signal &&) = delete;
    Signal &operator=(const Signal &) = delete;

public:
    /**
     * @brief Construct a new Rask Signal object
     */
    Signal() = default;
    /**
     * @brief Destroy the Rask Signal object
     */
    ~Signal() = default;

    /**
     * @brief Signal emission
     * @param args Arguments template. Ex: <int, bool, const char *>
     */
    void emit(Args... args) { for (auto &it: m_slots) (*it)(args...); }

    /**
     * @brief Connects the slot to the signal
     * @param slot Slot object reference
     */
    inline void connect(Slot<Args...> *slot) { m_slots.push_back(slot); }

    /**
     * @brief Disconnect the slot of the signal
     * @param slot Slot object reference
     */
    void disconnect(Slot<Args...> *slot)
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
    std::vector<Slot<Args...> *> m_slots;
};

/**
 * @brief Slot / callback to be executed when the signal is emitted
 * @tparam Arguments template. Ex: <int, bool, const char *>
 */
template <typename ...Args>
class Slot
{
    Slot(const Slot &) = delete;
    Slot(Slot &&) = delete;
    Slot &operator=(const Slot &) = delete;

public:
    /**
     * @brief Construct a new Rask Slot object
     * @param parent Parent signal object
     */
    Slot(Signal<Args...> *parent = nullptr): 
        m_init(false), 
        m_signalParent(parent)
    {}
    /**
     * @brief Construct a new Rask Slot object
     * @param callback Function called when the signal is emitted
     * @param parent Parent signal object
     */
    Slot(std::function<void(Args...)> callback, Signal<Args...> *parent = nullptr): 
        m_init(true), 
        m_callback(callback),
        m_signalParent(parent)
    {}
    /**
     * @brief Destroy the Rask Slot object
     */
    ~Slot() 
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
    inline void setSignalParent(Signal<Args...> *parent) { m_signalParent = parent; }

private:
    bool m_init;
    std::function<void(Args...)> m_callback;
    Signal<Args...> *m_signalParent;
};

} // namespace Rask

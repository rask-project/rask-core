#pragma once

#include <raskobject.h>

/**
 * @brief Serial Led - class to send on and off signal to serial pin
 */
class RaskSerialLed
{
    uint8_t m_pin;
    RaskObject m_blinkObject;

public:
    /**
     * @brief Construct a new Rask Serial Led object
     * @param pin Output pin
     * @param blinkInterval Interval to blink the led
     */
    RaskSerialLed(uint8_t pin, unsigned long blinkInterval = 1000);

    /**
     * @brief Turn on the led
     */
    void on();
    /**
     * @brief Turn off the led
     */
    void off();

    /**
     * @brief Turn on the flashing led
     */
    void blinkOn();
    /**
     * @brief Turn off the flashing led
     */
    void blinkOff();
    /**
     * @brief Set the Interval Blink object
     * @param interval unsigned long in ms
     */
    void setIntervalBlink(unsigned long interval);

private:
/* private slots */
    RaskSlot<> slotBlink;
};
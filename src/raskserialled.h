#pragma once
#include <raskobject.h>

class RaskSerialLed
{
    uint8_t m_pin;
    RaskObject m_blinkObject;

public:
    RaskSerialLed(uint8_t pin, unsigned long blinkInterval = 1000);

    void on();
    void off();

    void blinkOn();
    void blinkOff();
    void setIntervalBlink(unsigned long interval);

private:
/* private slots */
    RaskSlot<> slotBlink;
};
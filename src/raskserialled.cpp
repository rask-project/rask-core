#include "raskserialled.h"
#include "raskcore.h"
#include <Arduino.h>

RaskSerialLed::RaskSerialLed(uint8_t pin, unsigned long blinkInterval) : 
    m_pin(pin)
{
    pinMode(m_pin, OUTPUT);

    m_blinkObject.setInterval(blinkInterval);
    slotBlink.setSignalParent(&m_blinkObject.timeout);
    slotBlink.setCallback([&]() { digitalWrite(m_pin, !digitalRead(m_pin)); });
    
    m_blinkObject.timeout.connect(&slotBlink);
}

void RaskSerialLed::on()
{
    digitalWrite(m_pin, HIGH);
}

void RaskSerialLed::off()
{
    digitalWrite(m_pin, LOW);
}

void RaskSerialLed::blinkOn()
{
    m_blinkObject.startTimer();
    RaskCore::addEvent(&m_blinkObject);
}

void RaskSerialLed::blinkOff()
{
    m_blinkObject.stopTimer();
    RaskCore::removeEvent(&m_blinkObject);
}

void RaskSerialLed::setIntervalBlink(unsigned long interval)
{
    m_blinkObject.setInterval(interval);
}

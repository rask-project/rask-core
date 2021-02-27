#include <Arduino.h>
#include <raskcore.h>
#include <raskobject.h>

RaskObject obj;
RaskSlot<> slot;

void setup() {
    constexpr auto interval {1000};
    obj.setInterval(interval);
    obj.timeout.connect(&slot);
    obj.startTimer();

    slot.setCallback([]() { Serial.println("Timeout callback"); });
    slot.setSignalParent(&obj.timeout);
}

void loop() {
    RaskCore::exec();
}
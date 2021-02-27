#include <Arduino.h>
#include <raskcore.h>
#include <raskobject.h>

RaskObject obj;
RaskSlot<> slot;

void setup() {
    delay(1000);
    Serial.begin(115200);
    
    constexpr auto interval {1000};
    obj.setInterval(interval);
    obj.timeout.connect(&slot);
    obj.startTimer();

    slot.setCallback([]() { Serial.println("Timeout callback"); });
    slot.setSignalParent(&obj.timeout);

    RaskCore::addEvent(&obj);
}

void loop() {
    RaskCore::exec();
}
#include <Arduino.h>
#include <raskcore.h>
#include <raskobject.h>

class ClassObj : public RaskObject
{
public:
    ClassObj()
    {
        slotExample.setCallback([&](int i)
        {
            Serial.print("Number received from emission signal: ");
            Serial.println(i);
        });
        slotExample.setSignalParent(&signalExample);
        signalExample.connect(&slotExample);
    }

    ~ClassObj() = default;

    RaskSignal<int> signalExample;
    RaskSlot<int> slotExample;
};

void setup() {
    delay(1000);
    Serial.begin(115200);
}

void loop() {
    constexpr auto interval {1000};
    int i = 0;

    ClassObj basedClass;
    RaskObject timer;
    RaskSlot<> timeoutSlot([&]()
    {
        basedClass.signalExample.emit(i++);
    }, &timer.timeout);

    timer.timeout.connect(&timeoutSlot);
    timer.startTimer(interval);

    RaskCore::addEvent(&timer);
    RaskCore::loop();
}
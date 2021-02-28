# Rask Core
This library implements an event loop, which allows the execution of timers on pseudo-threads and resources for signals and slots for Arduino.

## Examples

Simple Timer
```cpp
#include <raskcore.h>
#include <raskobject.h>

RaskObject obj;
RaskSlot<> slot;

obj.setInterval(1000);
obj.timeout.connect(&slot);
obj.startTimer();

slot.setCallback([]() {
    Serial.println("Timeout");
});

RaskCore::addEvent(&obj);

void loop() {
    RaskCore::exec();
}
```

Single Shot
```cpp
#include <raskcore.h>
#include <raskobject.h>

RaskObject obj;
RaskSlot slot;

obj.timeout.connect(&slot);
obj.startTimer();
obj.singleShot(interval);

slot.setCallback([]() {
    Serial.println("Timeout");
});

RaskCore::addEvent(&obj);

void loop() {
    RaskCore::exec();
}
```

Signals and Slots
```cpp
#include <raskobject.h>

int i = 0;
bool b = false;

RaskSignal<int, bool> signal;
RaskSlot<int, bool> slot([&](int i, bool b)
{
    Serial.print("Integer: ");
    Serial.print(i);

    Serial.print(" - Boolean: ");
    Serial.println(b);
}, &signal);

void setup() {
    delay(1000);
    Serial.begin(115200);

    signal.connect(&slot);
}

void loop() {
    i = millis();
    b = !b;

    signal.emit(i, b);
    delay(1000);
}
```

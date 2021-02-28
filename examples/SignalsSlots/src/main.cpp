#include <Arduino.h>
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

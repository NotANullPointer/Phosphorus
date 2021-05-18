#include "light.h"

void light_init(light &lt, uint8_t pin) {
    lt = {pin};
    pinMode(pin, OUTPUT);
}

void light_set_state(light &lt, bool state) {
    digitalWrite(lt.pin, state);
}

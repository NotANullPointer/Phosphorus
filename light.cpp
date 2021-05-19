#include "light.h"

Light::Light(uint8_t pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void Light::set_state(bool state) {
    digitalWrite(pin, state);
}

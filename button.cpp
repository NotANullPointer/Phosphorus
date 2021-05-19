#include "button.h"

Button::Button(uint8_t pin) {
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
}

bool Button::read() {
    return !digitalRead(pin);
}

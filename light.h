#pragma once

#include <Arduino.h>

class Light {
    private:
        uint8_t pin;
    public:
        Light(uint8_t pin);
        void set_state(bool state);
};

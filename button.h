#pragma once

#include <Arduino.h>

class Button {
    private:
        uint8_t pin;
    public:
        Button(uint8_t pin);
        bool read();
};

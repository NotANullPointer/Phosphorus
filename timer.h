#pragma once

#include <Arduino.h>

class Timer {
    private:
        uint32_t start_time;
        uint32_t time;
        uint32_t seconds_to_millis(uint8_t seconds);
    public:
        Timer(uint8_t seconds);
        void start();
        bool check();
};

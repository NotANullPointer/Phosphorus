#pragma once

#include <Arduino.h>
#include <math.h>

#define SENSOR_READINGS 4

class LightSensor {
    private:
        uint8_t pin;
        uint8_t readings[SENSOR_READINGS];
        uint8_t curr_idx = 0;
        uint8_t avg_reading;
        uint8_t compute_average();
    public:
        LightSensor(uint8_t pin);
        void add_reading(uint8_t reading);
        uint8_t get_avg_reading();
        uint8_t read();
};

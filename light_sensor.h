#pragma once

#include <math.h>

#define SENSOR_READINGS 4
#define NORMALIZE_CONSTANT 1.00452f

typedef struct __light_sensor {
    uint8_t pin;
    uint8_t readings[SENSOR_READINGS];
    uint8_t avg_reading;
    uint8_t curr_read_idx;
} light_sensor;

void light_sensor_init(light_sensor &sensor, uint8_t pin);

void light_sensor_add_reading(light_sensor &sensor, uint8_t reading);

uint8_t light_sensor_read(light_sensor sensor);

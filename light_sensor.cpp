#include "light_sensor.h"

LightSensor::LightSensor(uint8_t pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
}

void LightSensor::add_reading(uint8_t reading) {

    //add the reading
    readings[curr_idx] = reading;
    
    //recalculate the average
    uint16_t avg = 0;
    for(int i = 0; i < SENSOR_READINGS; i++)
        avg += readings[i];
    avg_reading = (uint8_t)(avg /= SENSOR_READINGS);
    
    //increment the index
    curr_idx++;
    if(curr_idx > SENSOR_READINGS) {
        curr_idx = 0;
    }
}

uint8_t LightSensor::get_avg_reading() {
    return avg_reading;
}

uint8_t LightSensor::read() {
    uint16_t sensor_read = analogRead(pin);
    sensor_read = log(sensor_read-1)*NORMALIZE_CONSTANT;
    return (uint8_t) sensor_read; 
}

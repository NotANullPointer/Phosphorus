#include "light_sensor.h"

LightSensor::LightSensor(uint8_t pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
}

void LightSensor::add_reading(uint8_t reading) {

    //aggiungo la lettura
    readings[curr_idx] = reading;
    
    //ricalcolo della media
    avg_reading = compute_average();

    //aumento l'index (porto a zero)
    curr_idx++;
    if(curr_idx > SENSOR_READINGS) {
        curr_idx = 0;
    }
}

uint8_t LightSensor::compute_average() {

    uint16_t avg = 0;

    for(int i = 0; i < SENSOR_READINGS; i++)
        avg += readings[i];

    return (uint8_t)(avg /= SENSOR_READINGS);
}

uint8_t LightSensor::get_avg_reading() {
    return avg_reading;
}

uint8_t LightSensor::read() {
    uint16_t sensor_read = analogRead(pin);
    sensor_read = map(sensor_read, 0, 1023, 0, 100);
    return (uint8_t) sensor_read; 
}

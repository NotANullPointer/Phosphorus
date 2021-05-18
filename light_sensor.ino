#include "light_sensor.h"

void light_sensor_init(light_sensor &sensor, uint8_t pin) {
    sensor = {pin, {0}, 0, 0};
    pinMode(pin, INPUT);
}

void light_sensor_add_reading(light_sensor &sensor, uint8_t reading) {
    //add the reading
    sensor.readings[sensor.curr_read_idx] = reading;
    
    //recalculate the average
    uint16_t avg = 0;
    for(int i = 0; i < SENSOR_READINGS; i++)
        avg += sensor.readings[i];
    sensor.avg_reading = (char)(avg /= SENSOR_READINGS);
    
    //increment the index
    sensor.curr_read_idx++;
    if(sensor.curr_read_idx > SENSOR_READINGS) {
        sensor.curr_read_idx = 0;
    }
}

uint8_t light_sensor_read(light_sensor sensor) {
  int sensor_read = analogRead(sensor.pin);
  sensor_read = pow(NORMALIZE_CONSTANT, sensor_read);
  return (uint8_t) sensor_read; 
}

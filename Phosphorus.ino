#include "Phosphorus.h"

mode current_mode = OFF;

light_sensor sensors[3];

button btn_on, btn_off, btn_auto;

light lights[1];


void setup() {
    Serial.begin(9600);
  
    button_init(btn_on, BTN_ON);
    button_init(btn_off, BTN_OFF);
    button_init(btn_auto, BTN_AUTO);

    light_sensor_init(sensors[0], SNS1);
    light_sensor_init(sensors[1], SNS2);
    light_sensor_init(sensors[2], SNS3);

    light_init(lights[0], LT1);
}

void loop() {
    if(current_mode == AUTO) {
         read_sensors();
    }
}

void read_sensors() {
    for(int i = 0; i < SNS_SIZE; i++) {
        uint8_t reading = light_sensor_read(sensors[i]);
        light_sensor_add_reading(sensors[i], reading);
    }
}

uint8_t average_sensors() {
    uint16_t average = 0;
    for(int i = 0; i < SNS_SIZE; i++) {
        average += sensors[i].avg_reading;
    }
    return (uint8_t)(average/SNS_SIZE);
}

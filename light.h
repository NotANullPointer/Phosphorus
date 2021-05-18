#pragma once

typedef struct __light {
    uint8_t pin;
} light;

void light_init(light &lt, uint8_t pin);

void light_set_state(light &lt, bool state);

#pragma once

typedef struct __button {
    uint8_t pin;
    bool prev;
    bool state;
} button;

void button_init(button &btn, uint8_t pin);

bool button_read(button &btn);

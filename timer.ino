#include "timer.h"

uint32_t start_time = 0;
uint32_t target_millis = 0;

void timer_start(uint8_t target_seconds) {
    start_time = millis();
    target_millis = target_seconds*1000;
}

bool timer_check() {
    return (millis()- start_time) >= target_millis;
}

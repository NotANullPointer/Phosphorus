#include "timer.h"

Timer::Timer(uint8_t seconds) {
    this->time = seconds_to_millis(seconds);
}

uint32_t Timer::seconds_to_millis(uint8_t seconds) {
    return seconds * 1000;
}

void Timer::start() {
    this->start_time = millis();
}

bool Timer::check() {
    return (millis() - start_time >= time);
}

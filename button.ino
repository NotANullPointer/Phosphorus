#include "button.h"

void button_init(button &btn, uint8_t pin) {
    btn = {pin, true, false};
    pinMode(pin, INPUT_PULLUP);
}

bool button_read(button &btn) {
    if(digitalRead(btn.pin) != btn.prev) {
      btn.prev = !btn.prev;
      if(!btn.prev)
        btn.state = !btn.state;
    }
    return btn.state;
}

#include "Phosphorus.h"

mode current_mode = M_OFF;
trigger current_trigger = T_NONE;
Timer timer(TG_TIME);
bool lights_on = false;

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
LightSensor sensors[SNS_SIZE] = {
    LightSensor(SNS1),
    LightSensor(SNS2),
    LightSensor(SNS3) 
};
Light lights[LT_SIZE] = {
    Light(LT1)
};
Button btn_on(BTN_ON), btn_off(BTN_OFF), btn_auto(BTN_AUTO);

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    display_mode(current_mode);
}

void loop() {
    process_input();
    process_mode();
}

void process_input() {
    input in = I_NONE;
    mode in_mode = current_mode; 
    in = phys_input();
    
    if(in == I_NONE)
        in = remote_input();
        
    if(in == I_NONE)
        return;

    switch(in) {
        case I_ON:
            Serial.println("Modalità: ON");
            in_mode = M_ON;
            break;
        case I_OFF:
            Serial.println("Modalità: OFF");
            in_mode = M_OFF;
            break;
        case I_AUTO:
            Serial.println("Modalità: CREPUSCOLARE");
            in_mode = M_AUTO;
            break;
        case I_AVG:
            Serial.println("Media dei sensori: " + String(average_sensors()) + "%");
            break;
    }

    if(in_mode != current_mode) {
        current_mode = in_mode;
        current_trigger =  T_NONE;
        display_mode(current_mode);
    }
}

void process_mode() {
    if((current_mode == M_ON && !lights_on) || (current_mode == M_OFF && lights_on)) {
        set_lights(!lights_on);
    } else if (current_mode == M_AUTO) {
        read_sensors();
        uint8_t average = average_sensors();
        if(current_trigger != T_NONE) {
            if(timer.check()) {
                if(current_trigger == T_HIGH && average > SNS_HIGH_THRESHOLD)
                    set_lights(false);
                else if(current_trigger == T_LOW && average <= SNS_LOW_THRESHOLD)
                    set_lights(true);
                current_trigger = T_NONE;
            }
        } else {
            if(lights_on && average <= SNS_LOW_THRESHOLD) {
                current_trigger = T_LOW;
                timer.start();
            } else if (!lights_on && average > SNS_HIGH_THRESHOLD) {  
                current_trigger = T_HIGH;
                timer.start(); 
            }
        }
    }
}

void set_lights(bool state) {
    lights_on = state;
    for(int i = 0; i < LT_SIZE; i++) {
        lights[i].set_state(lights_on);
    }
}

void read_sensors() {
    for(int i = 0; i < SNS_SIZE; i++) {
        uint8_t reading = sensors[i].read();
        sensors[i].add_reading(reading);
    }
}

uint8_t average_sensors() {
    uint16_t average = 0;
    for(int i = 0; i < SNS_SIZE; i++) {
        average += sensors[i].get_avg_reading();
    }
    return (uint8_t)(average/SNS_SIZE);
}

input phys_input() {
    input res = I_NONE;
    if(btn_on.read())
        res = I_ON;
    else if(btn_off.read())
        res = I_OFF;
    else if(btn_auto.read())
        res = I_AUTO;
    return res;
}

input remote_input() {
    input res = I_NONE;
    if(Serial.available()) {
        char c = Serial.read();
        switch(c) {
            case CMD_ON: res = I_ON; break;
            case CMD_OFF: res = I_OFF; break;
            case CMD_AUTO: res = I_AUTO; break;
            case CMD_AVG: res = I_AVG; break;
        }
    }
    return res;
}

void display_mode(mode m) {
    lcd.setCursor(0, 0);
    lcd.print(" Illuminazione  ");
    lcd.setCursor(0, 1);
    switch(m) {
        case M_ON:
            lcd.print("       ON       ");
            break;
        case M_OFF:
            lcd.print("       OFF      ");
            break;
        case M_AUTO:
            lcd.print("  CREPUSCOLARE  ");
    }
    current_mode = m;
}

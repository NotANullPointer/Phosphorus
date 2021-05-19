#include "Phosphorus.h"

mode current_mode = OFF;

bool lights_on = false;

trigger current_trigger = NONE;

Timer timer(TG_TIME);

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
    input in = NONE;
    mode in_mode = current_mode; 
    in = phys_input();
    
    if(in == NONE)
        in = remote_input();
    else
        return;
        
    if(in == NONE)
        return;

    switch(in) {
        case ON:
            Serial.println("Modalità: ON");
            in_mode = ON;
            break;
        case OFF:
            Serial.println("Modalità: OFF");
            in_mode = OFF;
            break;
        case AUTO:
            Serial.println("Modalità: CREPUSCOLARE");
            in_mode = AUTO;
            break;
        case AVG:
            Serial.println("Media dei sensori: " + String(average_sensors() + "%"));
            break;
    }

    if(in_mode != current_mode) {
        current_mode = in_mode;
        display_mode(current_mode);
    }
}

void process_mode() {
    if((current_mode == ON && !lights_on) || (current_mode == OFF && lights_on)) {
        lights_on = !lights_on
        for(int i = 0; i < LT_SIZE; i++) {
            lights[i].set_state(lights_on);
        }
    } else if (current_mode = AUTO) {
        read_sensors();
        uint8_t average = average_sensors();
        if(trigger != NONE) {
            if(timer.check()) {
                if(trigger == HIGH_TRIGGER && average > LT_THRESHOLD)
                    current_mode = ON;
                else if(trigger == LOW_TRIGGER && average <= LT_THRESHOLD )
                    current_mode = OFF;
                else {
                    trigger = NONE;
                    return;
                }
                trigger = NONE;
                process_mode();
                current_mode = AUTO;
            }
        } else {
            if(lights_on && average <= LT_THRESHOLD) {
                trigger = LOW_TRIGGER;
                timer.start();
            } else if (!lights_on && average > LT_THRESHOLD) {  
                trigger = HIGH_TRIGGER;
                timer.start(); 
            }
        }
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
    input res = NONE;
    if(btn_on.read())
        res = ON;
    else if(btn_off.read())
        res = OFF;
    else if(btn_auto.read())
        res = AUTO;
    return res;
}

input remote_input() {
    input res = NONE;
    if(Serial.available()) {
        char c = Serial.read();
        switch(c) {
            case '+': res = ON; break;
            case '-': res = OFF; break;
            case '/': res = AUTO; break;
            case ':': res = AVG; break;
        }
    }
    return res;
}

void display_mode(mode m) {
    lcd.setCursor(0, 0);
    lcd.print(" Illuminazione  ");
    lcd.setCursor(0, 1);
    switch(m) {
        case ON:
            lcd.print("       ON       ");
            break;
        case OFF:
            lcd.print("       OFF      ");
            break;
        case AUTO:
            lcd.print("  CREPUSCOLARE  ");
    }
    current_mode = m;
}

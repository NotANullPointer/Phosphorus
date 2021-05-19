#include "Phosphorus.h"

mode current_mode = OFF;

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
    if(current_mode == AUTO) {
         read_sensors();
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

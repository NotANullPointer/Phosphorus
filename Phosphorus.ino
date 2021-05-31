#include "Phosphorus.h"

Timer timer(TG_TIME);
bool lights_on = false;
mode current_mode = M_OFF;
trigger current_trigger = T_NONE;

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
    in = phys_input(); //input fisico (pulsanti)
    
    if (in == I_NONE) //se non c'è input fisico
        in = remote_input(); //input remoto
        
    if (in == I_NONE) //se non c'è input remoto
        return; //nessun input

    switch (in) {
        case I_ON:    in_mode = M_ON;
                      break;
        case I_OFF:   in_mode = M_OFF;
                      break;
        case I_AUTO:  in_mode = M_AUTO;
                      break;
        case I_AVG:   display_average();
                      break;
    }

    if(in_mode != current_mode) { //se c'è un cambio di modalità
        current_mode = in_mode;
        current_trigger = T_NONE; //cancello il trigger in caso ci sia
        display_mode(current_mode); //aggiorno l'LCD
    }
}

void process_mode() {

    if ((current_mode == M_ON && !lights_on) || (current_mode == M_OFF && lights_on)) { //modalità on e led spento o modalità off e led acceso
        set_lights(!lights_on); //inverto lo stato del led (spento se acceso, acceso se spento)
    } else if (current_mode == M_AUTO) { //modalità crepuscolare
        read_sensors();
        uint8_t average = average_sensors();

        if (average <= SNS_LOW_THRESHOLD) { //se siamo sotto la soglia bassa
            process_trigger(T_LOW, true);
        } else if (average > SNS_HIGH_THRESHOLD) { //se siamo sopra la soglia alta
            process_trigger(T_HIGH, false);
        }
    }
}

void process_trigger(trigger trigger_type, bool light) {

    if (timer.check() && current_trigger == trigger_type) { //se siamo nel trigger trigger_type e sono passati X secondi
        set_lights(light); //setto la luce a light
        current_trigger = T_NONE; //non siamo più in alcun trigger
    } else if (lights_on == !light && current_trigger == T_NONE) { //se la luce è opposta a light e non siamo in tempo di trigger
        timer.start(); //avvio il timer
        current_trigger = trigger_type; //siamo nel trigger trigger_type
    }
}

void set_lights(bool state) {

    lights_on = state;

    for (int i = 0; i < LT_SIZE; i++) {
        lights[i].set_state(lights_on);
    }
}

void read_sensors() {

    for (int i = 0; i < SNS_SIZE; i++) {
        uint8_t reading = sensors[i].read();
        sensors[i].add_reading(reading);
    }
}

uint8_t average_sensors() {

    uint16_t average = 0;

    for (int i = 0; i < SNS_SIZE; i++) {
        average += sensors[i].get_avg_reading();
    }

    return (uint8_t)(average/SNS_SIZE);
}

void display_average() {

    Serial.println("Media dei sensori:");

    for (int i = 0; i < SNS_SIZE; i++) {
        uint8_t reading = sensors[i].get_avg_reading();

        Serial.println("#" + String(i) + ": " + String(reading) + "%");
    }

    Serial.println("Media totale: " + String(average_sensors()) + "%");
}

input phys_input() {

    input res = I_NONE;

    if (btn_on.read())
        res = I_ON;
    else if (btn_off.read())
        res = I_OFF;
    else if (btn_auto.read())
        res = I_AUTO;

    return res;
}

input remote_input() {

    input res = I_NONE;

    if (Serial.available()) {

        char c = Serial.read();

        switch (c) {
            //converto da enum dei CMD a enum degli input, printando anche sul seriale 
            case CMD_ON:    res = I_ON; 
                            Serial.println("Modalita': ON");
                            break;
            case CMD_OFF:   res = I_OFF; 
                            Serial.println("Modalita': OFF");
                            break;
            case CMD_AUTO:  res = I_AUTO; 
                            Serial.println("Modalita': CREPUSCOLARE");
                            break;
            case CMD_AVG:   res = I_AVG; 
                            break;
        }
    }
    return res;
}

void display_mode(mode m) {

    lcd.setCursor(0, 0); //prima linea
    lcd.print(" Illuminazione  ");

    lcd.setCursor(0, 1); //seconda linea
    switch (m) {
        case M_ON:
            lcd.print("       ON       ");
            break;
        case M_OFF:
            lcd.print("       OFF      ");
            break;
        case M_AUTO:
            lcd.print("  CREPUSCOLARE  ");
    }
}

#pragma once

#include "button.h"
#include "light_sensor.h"
#include "light.h"
#include "timer.h"

#include <LiquidCrystal.h>

//Lights
#define LT_SIZE 1
#define LT1 5

//Sensors
#define SNS_SIZE 3
#define SNS1 A3
#define SNS2 A4
#define SNS3 A5

//Buttons
#define BTN_ON 2
#define BTN_OFF 3
#define BTN_AUTO 4

//LCD
#define LCD_RS 6
#define LCD_EN 7
#define LCD_D4 8
#define LCD_D5 9
#define LCD_D6 10
#define LCD_D7 11

//Trigger time
#define TG_TIME 10

enum mode {ON, OFF, AUTO};
enum trigger {LOW_TRIGGER, HIGH_TRIGGER};

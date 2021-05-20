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
#define SNS_LOW_THRESHOLD 20
#define SNS_HIGH_THRESHOLD 60

//Buttons
#define BTN_ON 2
#define BTN_OFF 3
#define BTN_AUTO 4

//LCD
#define LCD_RS 6
#define LCD_EN 7
#define LCD_D4 11
#define LCD_D5 10
#define LCD_D6 9
#define LCD_D7 8

//Trigger time
#define TG_TIME 10

//CMDs
#define CMD_ON '+'
#define CMD_OFF '-'
#define CMD_AUTO '/'
#define CMD_AVG ':'

enum mode {M_ON, M_OFF, M_AUTO};
enum input {I_ON, I_OFF, I_AUTO, I_AVG, I_NONE};
enum trigger {T_LOW, T_HIGH, T_NONE};

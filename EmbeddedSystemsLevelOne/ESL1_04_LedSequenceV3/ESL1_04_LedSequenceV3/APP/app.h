/*
 * app.h
 *
 * Created: 4/8/2023 9:05:07 PM
 *  Author: sharb
 */ 


#ifndef APP_H_
#define APP_H_


#include "../ECUAL/LED/led.h"
#include "../ECUAL/Button/button.h"


void app_init(void);
void app_start(void);
void Blink(void);
void timer_check(void);
void flagCount(void);
void callBlink(uint16_t T_ON,uint16_t T_OFF);

#endif /* APP_H_ */
/*
 * timer.h
 *
 * Created: 4/10/2023 5:52:58 PM
 *  Author: sharb
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "../../Utilities/BitMath.h"
#include "../../Utilities/Registers.h"


void timer0_init(void);
void timer0_start(void);
void timer0_stop(void);
void timer0_set_delay(uint32_t delay_ms);
void TIMER_INT_CallBack(void(*ptrfunc)(void));



#endif /* TIMER_H_ */
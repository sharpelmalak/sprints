/*
 * timer.c
 *
 * Created: 4/10/2023 5:53:09 PM
 *  Author: sharb
 */ 
#include "timer.h"
#include <avr/interrupt.h>
uint32_t NUM_OVF = 0;
uint8_t INIT_VAL = 0;
void (*ptrT0)(void) = 0;


void timer0_init(void)
{
	//Select Normal Mode
	CLEAR_BIT(TCCR0,3);
	CLEAR_BIT(TCCR0,6);
	
	// Enable Interrupt
	SET_BIT(SREG,7); // global
	SET_BIT(TIMSK,0); // overflow interrupt
	
}
void timer0_start(void)
{
	
	// clkio/no prescaler
	SET_BIT(TCCR0,0);
	CLEAR_BIT(TCCR0,1);
	CLEAR_BIT(TCCR0,2);
}
void timer0_stop(void)
{
	// stop the timer
	CLEAR_BIT(TCCR0,0);
	CLEAR_BIT(TCCR0,1);
	CLEAR_BIT(TCCR0,2);
}
void timer0_set_delay(uint32_t delay_ms)
{
	// tick_time = 1 micro second
	
	uint32_t totalticks = (delay_ms * 1000);
	NUM_OVF = totalticks/256;
	INIT_VAL = 256 - (totalticks%256);
	TCNT0 = INIT_VAL;
	NUM_OVF++;
}

void TIMER_INT_CallBack(void(*ptrfunc)(void))
{
	ptrT0 = ptrfunc;
}


ISR(TIMER0_OVF_vect)
{
	
	if(ptrT0) ptrT0();
}
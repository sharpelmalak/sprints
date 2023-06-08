/*
 * timer.h
 *
 * Created: 4/10/2023 5:52:58 PM
 *  Author: sharb
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "BitMath.h"
#include "Registers.h"

typedef enum 
{
	TIMER_OK,
	TIMER_NULL_PTR_REFERANCE,
	TIMER_WRONG_MODE,
	TIMER_NULL_PTR_CALL_BACK
}enu_timer_status_t;

typedef enum
{
	TIMER_NORMAL_MODE,
	TIMER_CTC_MODE,
	TIMER_FAST_PWM_MODE,
	TIMER_PWM_PHASE_CORRECT_MODE,
}enu_timer_mode_t;

typedef enum
{
	TIMER_ENABLE_INTERRUPT,
	TIMER_DISABLE_INTERRUPT,
}enu_timer_interrupt_option_t;

typedef struct
{
	enu_timer_mode_t               enu_timer_mode;
	enu_timer_interrupt_option_t   enu_timer_interrupt_option;
	void                           (*ptr_call_back)(void);
}str_timer_configs_t;
enu_timer_status_t timer0_init(str_timer_configs_t *arg_str_timer_configs_t);
void timer0_start(void);
void timer0_stop(void);
void timer0_set_delay(uint32_t delay_ms);




#endif /* TIMER_H_ */
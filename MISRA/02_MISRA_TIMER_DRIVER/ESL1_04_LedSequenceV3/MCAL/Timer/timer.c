/*
 * timer.c
 *
 * Created: 4/10/2023 5:53:09 PM
 *  Author: sharb
 */ 

#include "vect_table.h"
#include "StdTypes.h"
#include "timer.h"

uint32_t gl_NUM_OVF  = FALSE;
void (*ptrT0)(void)  = null;


enu_timer_status_t timer0_init(str_timer_configs_t *arg_str_timer_configs_t)
{
	enu_timer_status_t enu_timer_status_retVal = TIMER_OK;
	
	if(arg_str_timer_configs_t == null)
	{
		enu_timer_status_retVal = TIMER_NULL_PTR_REFERANCE;
	}
	else
	{
	  switch (arg_str_timer_configs_t->enu_timer_mode)
	  {
		  case TIMER_NORMAL_MODE :
		  {
			  //Select Normal Mode
			  CLEAR_BIT(TCCR0,3);
			  CLEAR_BIT(TCCR0,6);
			  break;
		  }
		  
		  case TIMER_CTC_MODE :
		  {
			  //Select CTC Mode
			  SET_BIT(TCCR0,3);
			  CLEAR_BIT(TCCR0,6);
			  break;
		  }
		  
		  case TIMER_FAST_PWM_MODE :
		  {
			  //Select FAST PWM Mode
			  SET_BIT(TCCR0,3);
			  SET_BIT(TCCR0,6);
			  break;
		  }
		  
		  case TIMER_PWM_PHASE_CORRECT_MODE :
		  {
			   //Select FAST PWM Mode
			   CLEAR_BIT(TCCR0,3);
			   SET_BIT(TCCR0,6);
			   break;
		  }
		  
		  default:
		  {
			   enu_timer_status_retVal = TIMER_WRONG_MODE;
		       break;
		  }
		   
	  }	//end switch for mode
	  
	  if(enu_timer_status_retVal == TIMER_OK)
	  {
		  switch(arg_str_timer_configs_t->enu_timer_interrupt_option)
		  {
		    case TIMER_ENABLE_INTERRUPT:
			{
				if(arg_str_timer_configs_t->enu_timer_mode == TIMER_NORMAL_MODE)
				{
				   if(arg_str_timer_configs_t->ptr_call_back == null)
				   {
					   enu_timer_status_retVal = TIMER_NULL_PTR_CALL_BACK;
				   }
				   
				   else
				   {
					   // set call back
					   ptrT0 = arg_str_timer_configs_t->ptr_call_back;
					   // Enable Interrupt
					   SET_BIT(SREG,7); // global
					   SET_BIT(TIMSK,0); // overflow interrupt
				   }
				}
				else
				{
					// handle rest interrupt options
				}
			    break;
			}
			
			case TIMER_DISABLE_INTERRUPT:
			{
				//do nothing
				break;
			}
			
			default :
			{
				break;
			}
		  }
	  }
	  else
	  {
		  //do nothing
	  }
	}
	
	
	return enu_timer_status_retVal;
	
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
	
	uint32_t totalticks = FALSE;
	uint8_t loc_init_value = FALSE;
	
	// calculate number of ticks needed in micro second
	totalticks = (delay_ms * 1000);
	
	gl_NUM_OVF = totalticks/256;
	
	//calculate mod number as init value
	loc_init_value = 256 - (totalticks%256);
	
	TCNT0 = loc_init_value;
	
	gl_NUM_OVF++;
}




ISR(TIM0_OVF_INT)
{
	static uint32_t counter = 0;
	
	if(counter == gl_NUM_OVF)
	{
		counter=0;
		timer0_stop();
		if(ptrT0 != null)
		{
			ptrT0();
		}
		else
		{
			//do nothing
		}
	}
	else
	{
		counter++;
	}
}
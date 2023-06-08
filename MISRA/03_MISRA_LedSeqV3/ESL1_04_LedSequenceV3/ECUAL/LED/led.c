/*
 * led.c
 *
 * Created: 4/5/2023 2:09:49 PM
 *  Author: sharpel
 */ 

#include "led.h"

// initialize LED as output 
EN_LED_Error_t LED_init(str_led_t *ptr_led)
{
	EN_LED_Error_t enu_led_retval = LED_OK;
	EN_DIO_ERROR   enu_dio_check  = DIO_OK;
	
	if(ptr_led == null)
	{
		enu_led_retval = LED_NOT_OK;
	}
	else
	{
		enu_dio_check = DIO_init(ptr_led->pinNumber,ptr_led->portNumber,OUTPUT);
		if(enu_dio_check != DIO_OK)
		{
			enu_led_retval = LED_NOT_OK;
		}
		
		else
		{
			// do nothing
		}
	}
	
	
	
	return enu_led_retval;
}
EN_LED_Error_t LED_on  (str_led_t *ptr_led)
{
		EN_LED_Error_t enu_led_retval = LED_OK;
		EN_DIO_ERROR   enu_dio_check  = DIO_OK;
		
		if(ptr_led == null)
		{
			enu_led_retval = LED_NOT_OK;
		}
		else
		{
			enu_dio_check = DIO_write(ptr_led->pinNumber,ptr_led->portNumber,HIGH);
			if(enu_dio_check != DIO_OK)
			{
				enu_led_retval = LED_NOT_OK;
			}
			
			else
			{
				// do nothing
			}
		}
		
		
		
		return enu_led_retval;
}
EN_LED_Error_t LED_off(str_led_t *ptr_led)
{
	
			EN_LED_Error_t enu_led_retval = LED_OK;
			EN_DIO_ERROR   enu_dio_check  = DIO_OK;
			
			if(ptr_led == null)
			{
				enu_led_retval = LED_NOT_OK;
			}
			else
			{
				enu_dio_check = DIO_write(ptr_led->pinNumber,ptr_led->portNumber,LOW);
				if(enu_dio_check != DIO_OK)
				{
					enu_led_retval = LED_NOT_OK;
				}
				
				else
				{
					// do nothing
				}
			}
			
			
			
			return enu_led_retval;
}
EN_LED_Error_t LED_toggle(str_led_t *ptr_led)
{
	
	
	EN_LED_Error_t enu_led_retval = LED_OK;
	EN_DIO_ERROR   enu_dio_check  = DIO_OK;
	
	if(ptr_led == null)
	{
		enu_led_retval = LED_NOT_OK;
	}
	else
	{
		enu_dio_check = DIO_toggle(ptr_led->pinNumber,ptr_led->portNumber);
		if(enu_dio_check != DIO_OK)
		{
			enu_led_retval = LED_NOT_OK;
		}
		
		else
		{
			// do nothing
		}
	}
	
	
	
	return enu_led_retval;
}







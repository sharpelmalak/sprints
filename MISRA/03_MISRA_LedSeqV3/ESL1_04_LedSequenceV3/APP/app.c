/*
 * app.c
 *
 * Created: 4/8/2023 9:04:54 PM
 *  Author: Sharpel
 */ 

#include "app.h"

uint8_t gl_uint8_timeout    = FALSE;
uint8_t gl_btn_flag         = FALSE;
uint8_t gl_blink_counter    = FALSE;
uint8_t gl_state            = FALSE;
uint8_t gl_is_init          = FALSE;


str_led_t gl_str_led1 = 
{
	.pinNumber = DIO_PIN4,
	.portNumber= DIO_PORTB
};

str_led_t gl_str_led2 =
{
	.pinNumber = DIO_PIN5,
	.portNumber= DIO_PORTB
};

str_led_t gl_str_led3 =
{
	.pinNumber = DIO_PIN6,
	.portNumber= DIO_PORTB
};

str_led_t gl_str_led4 =
{
	.pinNumber = DIO_PIN7,
	.portNumber= DIO_PORTB
};

str_Btn_t gl_str_Btn0 =
{
	.pinNumber = DIO_PIN4,
	.portNumber= DIO_PORTC
};
str_timer_configs_t gl_str_timer_configs = 
{
	.enu_timer_mode = TIMER_NORMAL_MODE,
	.enu_timer_interrupt_option = TIMER_ENABLE_INTERRUPT,
	.ptr_call_back = timer_check
};
void app_init()
{

	EN_LED_Error_t      enu_led_retval = LED_OK;
	EN_BTN_Error_t      enu_Btn_retval = BTN_OK;
	EN_EXTINT_ERROR     enu_ext_retval = EXTINT_OK;
	enu_timer_status_t  enu_tim_retval = TIMER_OK;
	
	enu_led_retval = LED_init(&gl_str_led1);
	if(enu_led_retval == LED_OK)
	{
		enu_led_retval = LED_init(&gl_str_led2);
		if(enu_led_retval == LED_OK)
		{
			enu_led_retval = LED_init(&gl_str_led3);
			if(enu_led_retval == LED_OK)
			{
				enu_led_retval = LED_init(&gl_str_led4);
				if(enu_led_retval == LED_OK)
				{
					gl_is_init = TRUE;
				}
				else
				{
					//nothing
				}
			}
			else
			{
				//nothing
			}
		}
		else
		{
			//nothing
		}
	}
	else
    {
         //nothing
	}
	
	if (gl_is_init == TRUE)
	{
		enu_Btn_retval = Button_init(&gl_str_Btn0);
		if(enu_Btn_retval == BTN_NOT_OK)
		{
			gl_is_init = FALSE;
		}
		else
		{
			//nothing
		}
	}
	
	else
	{
		//nothing
	}
	
	
	/************************************************************************/
	/*   BUTTON ONE as External interrupt Two to control BLINK Mode         */
	/************************************************************************/
	
	if (gl_is_init == TRUE)
	{
		enu_ext_retval = EXTINT_init(EXTINT2,RISING_EDGE);
		if(enu_ext_retval == EXTINT_OK)
		{
			enu_ext_retval = EXTINT_CallBack(EXTINT2,Blink);
			if(enu_ext_retval == EXTINT_NOT_OK)
			{
				gl_is_init = FALSE;
			}
			else
			{
				//nothing
			}
		}
		else
		{
			gl_is_init = FALSE;
		}
	}
	else
	{
		//nothing
	}
	
	if(gl_is_init == TRUE)
	{
		enu_tim_retval = timer0_init(&gl_str_timer_configs);
		if(enu_tim_retval != TIMER_OK)
		{
			gl_is_init = FALSE;
		}
		else
		{
			//nothing
		}
	}
	
	else
	{
		//nothing
	}
	
}
void app_start()
{
	uint8_t loc_button = FALSE ;
	if(gl_is_init == TRUE)
	{
	   while(1)
	   {
		   	
		   	(void)Button_read(&gl_str_Btn0,&loc_button);
		   	if(loc_button == TRUE)
		   	{
			   	while(loc_button == TRUE)
			   	{
				   	(void)Button_read(&gl_str_Btn0,&loc_button);
			   	}
			   	gl_btn_flag++;
		   	}
			else
			{
				if(gl_blink_counter == 0)
				{
					callBlink(100,900);
				}
				else if(gl_blink_counter == 1)
				{
					callBlink(200,800);
				}
				else if(gl_blink_counter == 2)
				{
					callBlink(300,700);
				}
				else if(gl_blink_counter == 3)
				{
					callBlink(500,500);
				}
				else if(gl_blink_counter == 4)
				{
					callBlink(800,200);
				}
				else
				{
					gl_blink_counter = 0 ;
				}
				
			} 
			
			
	   }	
	}
	else
	{
		//init error
	}
}



void Blink(void)
{
     gl_blink_counter++;
}

void timer_check(void)
{
	gl_uint8_timeout = TRUE;
}


void callBlink(uint16_t T_ON,uint16_t T_OFF)
{
	if(gl_btn_flag == 1)
	{
		 if(gl_state == FALSE)
		 {
			 LED_on(&gl_str_led1);
			 timer0_set_delay(T_ON);
			 timer0_start();
			 gl_state ++;
		 }
		 else if (gl_state == 1 && gl_uint8_timeout == TRUE)
		 {
			 gl_uint8_timeout = FALSE;
			 LED_off(&gl_str_led1);
			 timer0_set_delay(T_OFF);
			 timer0_start();
			 gl_state ++;
		 }
		 else if(gl_state == 2 && gl_uint8_timeout == TRUE)
		 {
			 gl_uint8_timeout = FALSE;
			 gl_state = 0;
		 }
		 else
		 {
			 //nothing
		 }
	}
	else if(gl_btn_flag == 2)
	{
		if(gl_state == FALSE)
		{
			LED_on(&gl_str_led1);
			LED_on(&gl_str_led2);
			timer0_set_delay(T_ON);
			timer0_start();
			gl_state ++;
		}
		else if (gl_state == 1 && gl_uint8_timeout == TRUE)
		{
			gl_uint8_timeout = FALSE;
			LED_off(&gl_str_led1);
			LED_off(&gl_str_led2);
			timer0_set_delay(T_OFF);
			timer0_start();
			gl_state ++;
		}
		else if(gl_state == 2 && gl_uint8_timeout == TRUE)
		{
			gl_uint8_timeout = FALSE;
			gl_state = 0;
		}
		else
		{
			//nothing
		}
	}
	else if(gl_btn_flag == 3)
	{
		 if(gl_state == FALSE)
		 {
			 LED_on(&gl_str_led1);
			 LED_on(&gl_str_led2);
			 LED_on(&gl_str_led3);
			 timer0_set_delay(T_ON);
			 timer0_start();
			 gl_state ++;
		 }
		 else if (gl_state == 1 && gl_uint8_timeout == TRUE)
		 {
			 gl_uint8_timeout = FALSE;
			 LED_off(&gl_str_led1);
			 LED_off(&gl_str_led2);
			 LED_off(&gl_str_led3);
			 timer0_set_delay(T_OFF);
			 timer0_start();
			 gl_state ++;
		 }
		 else if(gl_state == 2 && gl_uint8_timeout == TRUE)
		 {
			 gl_uint8_timeout = FALSE;
			 gl_state = 0;
		 }
		 else
		 {
			 //nothing
		 }
	}
	else if(gl_btn_flag == 4)
	{
		 if(gl_state == FALSE)
		 {
			 LED_on(&gl_str_led1);
			 LED_on(&gl_str_led2);
			 LED_on(&gl_str_led3);
			 LED_on(&gl_str_led4);
			 timer0_set_delay(T_ON);
			 timer0_start();
			 gl_state ++;
		 }
		 else if (gl_state == 1 && gl_uint8_timeout == TRUE)
		 {
			 gl_uint8_timeout = FALSE;
			 LED_off(&gl_str_led1);
			 LED_off(&gl_str_led2);
			 LED_off(&gl_str_led3);
			 LED_off(&gl_str_led4);
			 timer0_set_delay(T_OFF);
			 timer0_start();
			 gl_state ++;
		 }
		 else if(gl_state == 2 && gl_uint8_timeout == TRUE)
		 {
			 gl_uint8_timeout = FALSE;
			 gl_state = 0;
		 }
		 else
		 {
			 //nothing
		 }
	}
	else if(gl_btn_flag == 5)
	{
		 if(gl_state == FALSE)
		 {
			 LED_off(&gl_str_led1);
			 LED_on (&gl_str_led2);
			 LED_on (&gl_str_led3);
			 LED_on (&gl_str_led4);
			 timer0_set_delay(T_ON);
			 timer0_start();
			 gl_state ++;
		 }
		 else if (gl_state == 1 && gl_uint8_timeout == TRUE)
		 {
			 gl_uint8_timeout = FALSE;
			 LED_off(&gl_str_led2);
			 LED_off(&gl_str_led3);
			 LED_off(&gl_str_led4);
			 timer0_set_delay(T_OFF);
			 timer0_start();
			 gl_state ++;
		 }
		 else if(gl_state == 2 && gl_uint8_timeout == TRUE)
		 {
			 gl_uint8_timeout = FALSE;
			 gl_state = 0;
		 }
		 else
		 {
			 //nothing
		 }
	}
	else if(gl_btn_flag == 6)
	{
		if(gl_state == FALSE)
		{
			
			LED_off(&gl_str_led2);
			LED_on (&gl_str_led3);
			LED_on (&gl_str_led4);
			timer0_set_delay(T_ON);
			timer0_start();
			gl_state ++;
		}
		else if (gl_state == 1 && gl_uint8_timeout == TRUE)
		{
			gl_uint8_timeout = FALSE;
			LED_off(&gl_str_led3);
			LED_off(&gl_str_led4);
			timer0_set_delay(T_OFF);
			timer0_start();
			gl_state ++;
		}
		else if(gl_state == 2 && gl_uint8_timeout == TRUE)
		{
			gl_uint8_timeout = FALSE;
			gl_state = 0;
		}
		else
		{
			//nothing
		}
	}
	else if(gl_btn_flag == 7)
	{
		 if(gl_state == FALSE)
		 {
			 
			 
			 LED_off(&gl_str_led3);
			 LED_on (&gl_str_led4);
			 timer0_set_delay(T_ON);
			 timer0_start();
			 gl_state ++;
		 }
		 else if (gl_state == 1 && gl_uint8_timeout == TRUE)
		 {
			 gl_uint8_timeout = FALSE;
			 LED_off(&gl_str_led4);
			 timer0_set_delay(T_OFF);
			 timer0_start();
			 gl_state ++;
		 }
		 else if(gl_state == 2 && gl_uint8_timeout == TRUE)
		 {
			 gl_uint8_timeout = FALSE;
			 gl_state = 0;
		 }
		 else
		 {
			 //nothing
		 }
	}
	else if(gl_btn_flag == 8)
	{
		 LED_off(&gl_str_led4);
	}
	else if(gl_btn_flag == 9)
	{
		gl_btn_flag = 1;
	}
	else
	{
		gl_btn_flag = FALSE;
	}
}
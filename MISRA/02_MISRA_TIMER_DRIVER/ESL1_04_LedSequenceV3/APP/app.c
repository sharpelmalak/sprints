/*
 * app.c
 *
 * Created: 4/8/2023 9:04:54 PM
 *  Author: sharb
 */ 

#include "app.h"

volatile uint8_t gl_uint8_timeout=0;
volatile uint8_t flag = 0 ;
volatile uint8_t blink=0;
uint8_t gl_state=FALSE;

str_timer_configs_t gl_str_timer_configs = 
{
	.enu_timer_mode = TIMER_NORMAL_MODE,
	.enu_timer_interrupt_option = TIMER_ENABLE_INTERRUPT,
	.ptr_call_back = timer_check
};
void app_init()
{
	
	/************************************************************************/
	/*   LED initialization                                                 */
	/************************************************************************/
	LED_init(DIO_PIN4,DIO_PORTB);
	LED_init(DIO_PIN5,DIO_PORTB);
	LED_init(DIO_PIN6,DIO_PORTB);
	LED_init(DIO_PIN7,DIO_PORTB);
	
	Button_init(DIO_PIN4,DIO_PORTC);
	
	/************************************************************************/
	/*   BUTTON ZERO as External interrupt zero to control Led Sequence      */
	/************************************************************************/
	
	//EXTINT_init(EXTINT0,RISING_EDGE);
	//EXTINT_CallBack(EXTINT0,flagCount);
	
	/************************************************************************/
	/*   BUTTON ONE as External interrupt Two to control BLINK Mode         */
	/************************************************************************/
	EXTINT_init(EXTINT2,RISING_EDGE);
	EXTINT_CallBack(EXTINT2,Blink);
	timer0_init(&gl_str_timer_configs);
	
	
}
void app_start()
{
	uint8_t loc_button = FALSE ;
	while(1)
	{
		
    Button_read(DIO_PIN4,DIO_PORTC,&loc_button);
    if(loc_button == TRUE)
    {
    	while(loc_button == TRUE)
    	{
    		Button_read(DIO_PIN4,DIO_PORTC,&loc_button);
    	}
    	flagCount();
    }
	switch(blink)
	{
		case 0 :
		callBlink(100,900);
		break;
		case 1 :
		callBlink(200,800);
		break; 
		case 2 :
		callBlink(300,700);
		break;
		case 3 :
		callBlink(500,500);
		break;
		case 4 :
		callBlink(800,200);
		break;
		default:break;
	}
	
	}
	
}



void Blink(void)
{
	blink++;
	if(blink == 5)blink=0;
}

void timer_check(void)
{
	gl_uint8_timeout = 1;
}

void flagCount(void)
{
	flag++;
	if(flag==9)flag=1;
}


void callBlink(uint16_t T_ON,uint16_t T_OFF)
{
    switch(flag)
    {
	    case 1:
		   if(gl_state == FALSE)
		   {
		     LED_on(DIO_PIN4,DIO_PORTB);
		     timer0_set_delay(T_ON);
		     timer0_start();
			 gl_state ++;
		   }
	       else if (gl_state == 1 && gl_uint8_timeout == TRUE)
		   {
			   gl_uint8_timeout = FALSE;
			   LED_off(DIO_PIN4,DIO_PORTB);
			   timer0_set_delay(T_OFF);
			   timer0_start();
			   gl_state ++;
		   }
		   else if(gl_state == 2 && gl_uint8_timeout == TRUE)
		   {
			    gl_uint8_timeout = FALSE;
				gl_state = 0;
		   }
	    break;
	    case 2:  
	       if(gl_state == FALSE)
	       {
		       LED_on(DIO_PIN4,DIO_PORTB);
		       LED_on(DIO_PIN5,DIO_PORTB);
		       timer0_set_delay(T_ON);
		       timer0_start();
		       gl_state ++;
	       }
	       else if (gl_state == 1 && gl_uint8_timeout == TRUE)
	       {
		       gl_uint8_timeout = FALSE;
		       LED_off(DIO_PIN4,DIO_PORTB);
		       LED_off(DIO_PIN5,DIO_PORTB);
		       timer0_set_delay(T_OFF);
		       timer0_start();
		       gl_state ++;
	       }
	       else if(gl_state == 2 && gl_uint8_timeout == TRUE)
	       {
		       gl_uint8_timeout = FALSE;
		       gl_state = 0;
	       }
	    break;
	    case 3:
	       if(gl_state == FALSE)
	       {
		       LED_on(DIO_PIN4,DIO_PORTB);
		       LED_on(DIO_PIN5,DIO_PORTB);
		       LED_on(DIO_PIN6,DIO_PORTB);
		       timer0_set_delay(T_ON);
		       timer0_start();
		       gl_state ++;
	       }
	       else if (gl_state == 1 && gl_uint8_timeout == TRUE)
	       {
		       gl_uint8_timeout = FALSE;
		       LED_off(DIO_PIN4,DIO_PORTB);
		       LED_off(DIO_PIN5,DIO_PORTB);
		       LED_off(DIO_PIN6,DIO_PORTB);
		       timer0_set_delay(T_OFF);
		       timer0_start();
		       gl_state ++;
	       }
	       else if(gl_state == 2 && gl_uint8_timeout == TRUE)
	       {
		       gl_uint8_timeout = FALSE;
		       gl_state = 0;
	       }
	    break;
	    case 4:
	       if(gl_state == FALSE)
	       {
		       LED_on(DIO_PIN4,DIO_PORTB);
		       LED_on(DIO_PIN5,DIO_PORTB);
		       LED_on(DIO_PIN6,DIO_PORTB);
		       LED_on(DIO_PIN7,DIO_PORTB);
		       timer0_set_delay(T_ON);
		       timer0_start();
		       gl_state ++;
	       }
	       else if (gl_state == 1 && gl_uint8_timeout == TRUE)
	       {
		       gl_uint8_timeout = FALSE;
		       LED_off(DIO_PIN4,DIO_PORTB);
		       LED_off(DIO_PIN5,DIO_PORTB);
		       LED_off(DIO_PIN6,DIO_PORTB);
		       LED_off(DIO_PIN7,DIO_PORTB);
		       timer0_set_delay(T_OFF);
		       timer0_start();
		       gl_state ++;
	       }
	       else if(gl_state == 2 && gl_uint8_timeout == TRUE)
	       {
		       gl_uint8_timeout = FALSE;
		       gl_state = 0;
	       }
	    break;
	    case 5:
	            if(gl_state == FALSE)
	            {
		            LED_off(DIO_PIN4,DIO_PORTB);
		            LED_on(DIO_PIN5,DIO_PORTB);
		            LED_on(DIO_PIN6,DIO_PORTB);
		            LED_on(DIO_PIN7,DIO_PORTB);
		            timer0_set_delay(T_ON);
		            timer0_start();
		            gl_state ++;
	            }
	            else if (gl_state == 1 && gl_uint8_timeout == TRUE)
	            {
		            gl_uint8_timeout = FALSE;
		            LED_off(DIO_PIN5,DIO_PORTB);
		            LED_off(DIO_PIN6,DIO_PORTB);
		            LED_off(DIO_PIN7,DIO_PORTB);
		            timer0_set_delay(T_OFF);
		            timer0_start();
		            gl_state ++;
	            }
	            else if(gl_state == 2 && gl_uint8_timeout == TRUE)
	            {
		            gl_uint8_timeout = FALSE;
		            gl_state = 0;
	            }
	    break;
	    case 6:
	      if(gl_state == FALSE)
	      {
		      
		      LED_off(DIO_PIN5,DIO_PORTB);
		      LED_on(DIO_PIN6,DIO_PORTB);
		      LED_on(DIO_PIN7,DIO_PORTB);
		      timer0_set_delay(T_ON);
		      timer0_start();
		      gl_state ++;
	      }
	      else if (gl_state == 1 && gl_uint8_timeout == TRUE)
	      {
		      gl_uint8_timeout = FALSE;
		      LED_off(DIO_PIN6,DIO_PORTB);
		      LED_off(DIO_PIN7,DIO_PORTB);
		      timer0_set_delay(T_OFF);
		      timer0_start();
		      gl_state ++;
	      }
	      else if(gl_state == 2 && gl_uint8_timeout == TRUE)
	      {
		      gl_uint8_timeout = FALSE;
		      gl_state = 0;
	      }
	       break;
	    case 7:
	       if(gl_state == FALSE)
	       {
		       
		      
		       LED_off(DIO_PIN6,DIO_PORTB);
		       LED_on(DIO_PIN7,DIO_PORTB);
		       timer0_set_delay(T_ON);
		       timer0_start();
		       gl_state ++;
	       }
	       else if (gl_state == 1 && gl_uint8_timeout == TRUE)
	       {
		       gl_uint8_timeout = FALSE;
		       LED_off(DIO_PIN7,DIO_PORTB);
		       timer0_set_delay(T_OFF);
		       timer0_start();
		       gl_state ++;
	       }
	       else if(gl_state == 2 && gl_uint8_timeout == TRUE)
	       {
		       gl_uint8_timeout = FALSE;
		       gl_state = 0;
	       }
	    break;
	    case 8:
		   LED_off(DIO_PIN7,DIO_PORTB);
	    break;
    }
    
  
}
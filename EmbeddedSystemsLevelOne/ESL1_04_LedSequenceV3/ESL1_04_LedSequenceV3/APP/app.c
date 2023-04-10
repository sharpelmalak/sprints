/*
 * app.c
 *
 * Created: 4/8/2023 9:04:54 PM
 *  Author: sharb
 */ 

#include "app.h"

extern uint32_t NUM_OVF;
extern uint8_t INIT_VAL;


volatile uint8_t flag = 0 ;
volatile uint8_t blink=0;


void app_init()
{
	
	/************************************************************************/
	/*   LED initialization                                                 */
	/************************************************************************/
	LED_init(DIO_PIN0,DIO_PORTA);
	LED_init(DIO_PIN1,DIO_PORTA);
	LED_init(DIO_PIN2,DIO_PORTA);
	LED_init(DIO_PIN3,DIO_PORTA);
	
	/************************************************************************/
	/*   BUTTON ZERO as External interrupt zero to control Led Sequence      */
	/************************************************************************/
	
	EXTINT_init(EXTINT0,RISING_EDGE);
	EXTINT_CallBack(EXTINT0,flagCount);
	
	/************************************************************************/
	/*   BUTTON ONE as External interrupt ONE to control BLINK Mode         */
	/************************************************************************/
	EXTINT_init(EXTINT1,RISING_EDGE);
	EXTINT_CallBack(EXTINT1,Blink);
	timer0_init();
	TIMER_INT_CallBack(timer_check);
	
}
void app_start()
{
	while(1)
	{
		
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
	static uint32_t counter = 0;
	counter++;
	if(counter == NUM_OVF)
	{
		counter=0;
		timer0_stop();
	}
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
	       LED_on(DIO_PIN0,DIO_PORTA);
	       timer0_set_delay(T_ON);
		   timer0_start();
		   while (TCCR0);
		   LED_off(DIO_PIN0,DIO_PORTA);
		   timer0_set_delay(T_OFF);
		   timer0_start();
		   while (TCCR0);
	    break;
	    case 2:  
	       LED_on(DIO_PIN0,DIO_PORTA);
	       LED_on(DIO_PIN1,DIO_PORTA);
	       timer0_set_delay(T_ON);
	       timer0_start();
	       while (TCCR0);
	       LED_off(DIO_PIN0,DIO_PORTA);
	       LED_off(DIO_PIN1,DIO_PORTA);
	       timer0_set_delay(T_OFF);
	       timer0_start();
	       while (TCCR0);
	    break;
	    case 3:
	       LED_on(DIO_PIN0,DIO_PORTA);
	       LED_on(DIO_PIN1,DIO_PORTA);
	       LED_on(DIO_PIN2,DIO_PORTA);
	       timer0_set_delay(T_ON);
	       timer0_start();
	       while (TCCR0);
	       LED_off(DIO_PIN0,DIO_PORTA);
	       LED_off(DIO_PIN1,DIO_PORTA);
	       LED_off(DIO_PIN2,DIO_PORTA);
	       timer0_set_delay(T_OFF);
	       timer0_start();
	       while (TCCR0);
	    break;
	    case 4:
	       LED_on(DIO_PIN0,DIO_PORTA);
	       LED_on(DIO_PIN1,DIO_PORTA);
	       LED_on(DIO_PIN2,DIO_PORTA);
	       LED_on(DIO_PIN3,DIO_PORTA);
	       timer0_set_delay(T_ON);
	       timer0_start();
	       while (TCCR0);
	       LED_off(DIO_PIN0,DIO_PORTA);
	       LED_off(DIO_PIN1,DIO_PORTA);
	       LED_off(DIO_PIN2,DIO_PORTA);
	       LED_off(DIO_PIN3,DIO_PORTA);
	       timer0_set_delay(T_OFF);
	       timer0_start();
	       while (TCCR0);
	    break;
	    case 5:
	        LED_off(DIO_PIN0,DIO_PORTA);
		    LED_on(DIO_PIN1,DIO_PORTA);
		    LED_on(DIO_PIN2,DIO_PORTA);
		    LED_on(DIO_PIN3,DIO_PORTA);
		    timer0_set_delay(T_ON);
		    timer0_start();
		    while (TCCR0);
		    LED_off(DIO_PIN1,DIO_PORTA);
		    LED_off(DIO_PIN2,DIO_PORTA);
		    LED_off(DIO_PIN3,DIO_PORTA);
		    timer0_set_delay(T_OFF);
		    timer0_start();
		    while (TCCR0);
	    break;
	    case 6:
	       LED_off(DIO_PIN1,DIO_PORTA);
	       LED_on(DIO_PIN2,DIO_PORTA);
	       LED_on(DIO_PIN3,DIO_PORTA);
	       timer0_set_delay(T_ON);
	       timer0_start();
	       while (TCCR0);
	       LED_off(DIO_PIN2,DIO_PORTA);
	       LED_off(DIO_PIN3,DIO_PORTA);
	       timer0_set_delay(T_OFF);
	       timer0_start();
	       while (TCCR0);
	       break;
	    case 7:
	       LED_off(DIO_PIN2,DIO_PORTA);
	       LED_on(DIO_PIN3,DIO_PORTA);
	       timer0_set_delay(T_ON);
	       timer0_start();
	       while (TCCR0);
	       LED_off(DIO_PIN3,DIO_PORTA);
	       timer0_set_delay(T_OFF);
	       timer0_start();
	       while (TCCR0);
	    break;
	    case 8:
		   LED_off(DIO_PIN3,DIO_PORTA);
	    break;
    }
    
  
}
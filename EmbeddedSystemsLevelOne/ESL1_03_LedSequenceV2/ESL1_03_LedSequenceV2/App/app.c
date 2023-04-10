/*
 * app.c
 *
 * Created: 4/8/2023 9:04:54 PM
 *  Author: sharb
 */ 

#include "app.h"


void pressed(void);
volatile uint8_t flag = 0 ;
void app_init()
{
	LED_init(DIO_PIN0,DIO_PORTA);
	LED_init(DIO_PIN1,DIO_PORTA);
	LED_init(DIO_PIN2,DIO_PORTA);
	LED_init(DIO_PIN3,DIO_PORTA);
	
	EXTINT_init(EXTINT1,RISING_EDGE);
	EXTINT_CallBack(EXTINT1,pressed);
}
void app_start()
{
	while(1)
	{
		switch(flag)
		{
			case 1:
				LED_on(DIO_PIN0,DIO_PORTA);
				break;
			case 2:
				LED_on(DIO_PIN1,DIO_PORTA);
				break;
			case 3:
				LED_on(DIO_PIN2,DIO_PORTA);
				break;
			case 4:
				LED_on(DIO_PIN3,DIO_PORTA);
				break;
			case 5:
			    LED_off(DIO_PIN0,DIO_PORTA);
				break;
			case 6:
				LED_off(DIO_PIN1,DIO_PORTA);
				break;
			case 7:
				LED_off(DIO_PIN2,DIO_PORTA);
				break;
			case 8:
				LED_off(DIO_PIN3,DIO_PORTA);
				break;			
		}
	}
	
}

void pressed()
{
	flag++;
	if(flag == 9)flag=1;
}
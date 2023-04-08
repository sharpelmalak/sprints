/*
 * Led_Seq_V1.c
 *
 * Created: 4/8/2023 4:18:14 PM
 * Author : sharpel
 */ 
#define  F_CPU 1000000UL
#include <util/delay.h>
#include "../ECUAL/Button/button.h"
#include "../ECUAL/LED/led.h"


int main(void)
{
	// test function
	DIO_init_TEST();
	// initialize four leds
     LED_init(DIO_PIN0,DIO_PORTA);
     LED_init(DIO_PIN1,DIO_PORTA);
     LED_init(DIO_PIN2,DIO_PORTA);
     LED_init(DIO_PIN3,DIO_PORTA);
     
	 //initialize one button
     Button_init(DIO_PIN0,DIO_PORTC);
     
     uint8_t btnValue = LOW; // Button initially low 
     uint8_t flag = 0;
     while (1)
     {
	     Button_read(DIO_PIN0,DIO_PORTC,&btnValue);
	     if(btnValue){
		     _delay_ms(300);
		     switch(flag)
		     {
			     case 0:
			     LED_on(DIO_PIN0,DIO_PORTA);
			     flag++;
			     break;
			     case 1:
			     LED_on(DIO_PIN1,DIO_PORTA);
			     flag++;
			     break;
			     case 2:
			     LED_on(DIO_PIN2,DIO_PORTA);
			     flag++;
			     break;
			     case 3:
			     LED_on(DIO_PIN3,DIO_PORTA);
			     flag++;
			     break;
			     case 4:
			     LED_off(DIO_PIN0,DIO_PORTA);
			     flag++;
			     break;
			     case 5:
			     LED_off(DIO_PIN1,DIO_PORTA);
			     flag++;
			     break;
			     case 6:
			     LED_off(DIO_PIN2,DIO_PORTA);
			     flag++;
			     break;
			     case 7:
			     LED_off(DIO_PIN3,DIO_PORTA);
			     flag=0;
			     break;
			     default:break;
		     }
		     
	     }
	     
     }
}
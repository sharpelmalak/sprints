/*
 * app.c
 *
 * Created: 6/6/2023 3:54:18 AM
 *  Author: sharpel
 */ 


#include "app.h"

uint8_t gl_u8_btnValue = LOW; // Button initially low
uint8_t gl_app_state = FALSE;
void app_init(void)
{
	(void)LED_init(DIO_PIN4,DIO_PORTB);
	(void)LED_init(DIO_PIN5,DIO_PORTB);
	(void)LED_init(DIO_PIN6,DIO_PORTB);
	(void)LED_init(DIO_PIN7,DIO_PORTB);
	
	//initialize one button
	(void)Button_init(DIO_PIN4,DIO_PORTC);
}
void app_start(void)
{
	 (void)Button_read(DIO_PIN4,DIO_PORTC,&gl_u8_btnValue);
	 if(gl_u8_btnValue == HIGH)
	 {
		 while(gl_u8_btnValue == HIGH)
		 {
			 (void)Button_read(DIO_PIN4,DIO_PORTC,&gl_u8_btnValue);
		 }
		 switch(gl_app_state)
		 {
			 case 0:
			 LED_on(DIO_PIN4,DIO_PORTB);
			 gl_app_state++;
			 break;
			 case 1:
			 LED_on(DIO_PIN5,DIO_PORTB);
			 gl_app_state++;
			 break;
			 case 2:
			 LED_on(DIO_PIN6,DIO_PORTB);
			 gl_app_state++;
			 break;
			 case 3:
			 LED_on(DIO_PIN7,DIO_PORTB);
			 gl_app_state++;
			 break;
			 case 4:
			 LED_off(DIO_PIN4,DIO_PORTB);
			 gl_app_state++;
			 break;
			 case 5:
			 LED_off(DIO_PIN5,DIO_PORTB);
			 gl_app_state++;
			 break;
			 case 6:
			 LED_off(DIO_PIN6,DIO_PORTB);
			 gl_app_state++;
			 break;
			 case 7:
			 LED_off(DIO_PIN7,DIO_PORTB);
			 gl_app_state=0;
			 break;
			 default:break;
		 }
		 
	 }
	 
}
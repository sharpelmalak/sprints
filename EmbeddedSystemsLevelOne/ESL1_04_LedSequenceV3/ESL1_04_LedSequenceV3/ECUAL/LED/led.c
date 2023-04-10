/*
 * led.c
 *
 * Created: 4/5/2023 2:09:49 PM
 *  Author: sharpel
 */ 

#include "led.h"

// initialize LED as output 
EN_LED_Error_t LED_init(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber)
{
	if(!DIO_init(pinNumber,portNumber,OUTPUT))return LED_OK;
	else return LED_NOT_OK;
}
EN_LED_Error_t LED_on(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber)
{
	if(!DIO_write(pinNumber,portNumber,HIGH))return LED_OK;
	else return LED_NOT_OK;
}
EN_LED_Error_t LED_off(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber){
	if(!DIO_write(pinNumber,portNumber,LOW))return LED_OK;
	else return LED_NOT_OK;
}
EN_LED_Error_t LED_toggle(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber){
	if(!DIO_toggle(pinNumber,portNumber))return LED_OK;
	else return LED_NOT_OK;
}







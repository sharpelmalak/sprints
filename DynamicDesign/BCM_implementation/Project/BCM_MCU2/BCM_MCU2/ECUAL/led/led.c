/*
 * led.c
 *
 * Created: 4/5/2023 2:09:49 PM
 *  Author: sharpel
 */ 

#include "led.h"

// initialize LED as output 
enu_led_error_t LED_init(str_led_config_t *str_ptr_led_config)
{
	if(!DIO_init(str_ptr_led_config->pinNumber,str_ptr_led_config->portNumber,OUTPUT))return LED_OK;
	else return LED_NOT_OK;
}
enu_led_error_t LED_on(str_led_config_t *str_ptr_led_config)
{
	if(!DIO_write(str_ptr_led_config->pinNumber,str_ptr_led_config->portNumber,HIGH))return LED_OK;
	else return LED_NOT_OK;
}
enu_led_error_t LED_off(str_led_config_t *str_ptr_led_config){
	if(!DIO_write(str_ptr_led_config->pinNumber,str_ptr_led_config->portNumber,LOW))return LED_OK;
	else return LED_NOT_OK;
}
enu_led_error_t LED_toggle(str_led_config_t *str_ptr_led_config){
	if(!DIO_toggle(str_ptr_led_config->pinNumber,str_ptr_led_config->portNumber))return LED_OK;
	else return LED_NOT_OK;
}







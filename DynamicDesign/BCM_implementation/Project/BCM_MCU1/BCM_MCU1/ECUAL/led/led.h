/*
 * led.h
 *
 * Created: 4/5/2023 2:10:05 PM
 *  Author: sharpel
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../MCAL/DIO/dio.h"


// led typedefs
typedef enum 
{
	LED_OK = 0,
	LED_NOT_OK
	
}enu_led_error_t;

typedef struct
{
	EN_DIO_PINS pinNumber;
	EN_DIO_PORTS portNumber;
	
}str_led_config_t;

enu_led_error_t LED_init(str_led_config_t *str_ptr_led_config);
enu_led_error_t LED_on(str_led_config_t *str_ptr_led_config);
enu_led_error_t LED_off(str_led_config_t *str_ptr_led_config);
enu_led_error_t LED_toggle(str_led_config_t *str_ptr_led_config);



#endif /* LED_H_ */
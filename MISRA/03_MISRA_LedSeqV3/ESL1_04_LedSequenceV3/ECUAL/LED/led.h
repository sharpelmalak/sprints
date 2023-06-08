/*
 * led.h
 *
 * Created: 4/5/2023 2:10:05 PM
 *  Author: sharpel
 */ 


#ifndef LED_H_
#define LED_H_

#include "DIO/dio.h"

// led typedefs
typedef enum EN_LED_Error_t
{
	LED_OK = 0,
	LED_NOT_OK
	
}EN_LED_Error_t;


typedef struct
{
	EN_DIO_PINS pinNumber;
	EN_DIO_PORTS portNumber;
	
}str_led_t;

EN_LED_Error_t LED_init  (str_led_t *ptr_led);
EN_LED_Error_t LED_on    (str_led_t *ptr_led);
EN_LED_Error_t LED_off   (str_led_t *ptr_led);
EN_LED_Error_t LED_toggle(str_led_t *ptr_led);



#endif /* LED_H_ */
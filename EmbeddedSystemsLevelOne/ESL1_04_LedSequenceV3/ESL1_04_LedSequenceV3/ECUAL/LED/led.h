/*
 * led.h
 *
 * Created: 4/5/2023 2:10:05 PM
 *  Author: sharpel
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../MCAL/DIO/dio.h"
#include "../../MCAL/EXTINT/Ext_Interrupt.h"
#include "../../MCAL/Timer/timer.h"

// led typedefs
typedef enum EN_LED_Error_t
{
	LED_OK = 0,
	LED_NOT_OK
	
}EN_LED_Error_t;

typedef struct ST_Led
{
	EN_DIO_PINS pinNumber;
	EN_DIO_PORTS portNumber;
	
	}ST_Led;

EN_LED_Error_t LED_init(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber);
EN_LED_Error_t LED_on(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber);
EN_LED_Error_t LED_off(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber);
EN_LED_Error_t LED_toggle(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber);



#endif /* LED_H_ */
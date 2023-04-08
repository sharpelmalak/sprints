/*
 * button.c
 *
 * Created: 4/5/2023 2:10:59 PM
 *  Author: sharpel
 */ 

#include "button.h"




/*
Description : This function initialize PIN and set it's direction as Input
ARGS        : take PIN Number and PORT Number
return      : return BTN_OK if the PIN initializes correctly, BTN_NOT_OK otherwise
*/

EN_BTN_Error_t Button_init(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber)
{
	if(!DIO_init(pinNumber,portNumber,INPUT))return BTN_OK;
	else return BTN_NOT_OK;
}

/*
Description : This function Read PIN value and store it in variable
ARGS        : take PIN Number and PORT Number and the address of the variable
return      : return BTN_OK if the PIN read correctly, BTN_NOT_OK otherwise
*/
EN_BTN_Error_t Button_read(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumbert,uint8_t *value)
{
	if(!DIO_read(pinNumber,portNumbert,value))return BTN_OK;
	else return BTN_NOT_OK;
}
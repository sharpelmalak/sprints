/*
 * button.h
 *
 * Created: 4/5/2023 2:10:34 PM
 *  Author: sharpel
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "DIO/dio.h"


// button typedefs
typedef enum EN_BTN_Error_t
{
	BTN_OK = 0,
	BTN_NOT_OK
	
}EN_BTN_Error_t;

typedef struct
{
	EN_DIO_PINS pinNumber;
	EN_DIO_PORTS portNumber;
	
}str_Btn_t;


/*
Description : This function initialize PIN and set it's direction as Input
ARGS        : take PIN Number and PORT Number 
return      : return BTN_OK if the PIN initializes correctly, BTN_NOT_OK otherwise
*/

EN_BTN_Error_t Button_init(str_Btn_t *ptr_btn);

/*
Description : This function Read PIN value and store it in variable
ARGS        : take PIN Number and PORT Number and the address of the variable 
return      : return BTN_OK if the PIN read correctly, BTN_NOT_OK otherwise
*/
EN_BTN_Error_t Button_read(str_Btn_t *ptr_btn,uint8_t *value);


#endif /* BUTTON_H_ */
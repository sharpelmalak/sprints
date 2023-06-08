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

EN_BTN_Error_t Button_init(str_Btn_t *ptr_btn)
{
		EN_BTN_Error_t enu_btn_retval = BTN_OK;
		EN_DIO_ERROR   enu_dio_check  = DIO_OK;
		
		if(ptr_btn == null)
		{
			enu_btn_retval = BTN_NOT_OK;
		}
		else
		{
			enu_dio_check = DIO_init(ptr_btn->pinNumber,ptr_btn->portNumber,INPUT);
			if(enu_dio_check != DIO_OK)
			{
				enu_btn_retval = BTN_NOT_OK;
			}
			
			else
			{
				// do nothing
			}
		}
		
		
		
		return enu_btn_retval;
}

/*
Description : This function Read PIN value and store it in variable
ARGS        : take PIN Number and PORT Number and the address of the variable
return      : return BTN_OK if the PIN read correctly, BTN_NOT_OK otherwise
*/
EN_BTN_Error_t Button_read(str_Btn_t *ptr_btn,uint8_t *value)
{
	EN_BTN_Error_t enu_btn_retval = BTN_OK;
	EN_DIO_ERROR   enu_dio_check  = DIO_OK;
	
	if( (ptr_btn == null) || (value == null) )
	{
		enu_btn_retval = BTN_NOT_OK;
	}
	else
	{
		enu_dio_check = DIO_read(ptr_btn->pinNumber,ptr_btn->portNumber,value);
		if(enu_dio_check != DIO_OK)
		{
			enu_btn_retval = BTN_NOT_OK;
		}
		
		else
		{
			// do nothing
		}
	}
	
	
	
	return enu_btn_retval;
}
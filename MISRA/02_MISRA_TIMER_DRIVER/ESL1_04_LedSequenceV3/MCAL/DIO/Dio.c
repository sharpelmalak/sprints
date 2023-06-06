/*
 * Dio.c
 *
 * Created: 4/7/2023 2:45:37 PM
 *  Author: sharb
 */ 

#include "Dio.h"


// DIO FUNCTIONS IMPLEMENTATION

/*
Description : This function initialize PIN and set it's direction
ARGS        : take PIN Number and PORT Number and Direction (INPUT,OUTPUT)
return      : return DIO_OK if the PIN initializes correctly, DIO_NOT_OK otherwise
*/
EN_DIO_ERROR DIO_init(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber,EN_DIO_DIRECTION direction){
	
	if(pinNumber>7 || pinNumber < 0) return DIO_NOT_OK; // handle pin number error
	switch(portNumber){
		case DIO_PORTA:
		  if(direction == INPUT)CLEAR_BIT(DDRA,pinNumber);
		  else if (direction == OUTPUT) SET_BIT(DDRA,pinNumber);
		  else return DIO_NOT_OK ; // handle direction error
		  break;
		  case DIO_PORTB:
		  if(direction == INPUT)CLEAR_BIT(DDRB,pinNumber);
		  else if (direction == OUTPUT) SET_BIT(DDRB,pinNumber);
		  else return DIO_NOT_OK ; // handle direction error
		  break;
		  case DIO_PORTC:
		  if(direction == INPUT)CLEAR_BIT(DDRC,pinNumber);
		  else if (direction == OUTPUT) SET_BIT(DDRC,pinNumber);
		  else return DIO_NOT_OK ; // handle direction error
		  break;
		  case DIO_PORTD:
		  if(direction == INPUT)CLEAR_BIT(DDRD,pinNumber);
		  else if (direction == OUTPUT) SET_BIT(DDRD,pinNumber);
		  else return DIO_NOT_OK ; // handle direction error
		  break;
		  default: 
		  return DIO_NOT_OK; //handle port number error
	}
	
	return DIO_OK; 
}


/*
Description : This function write on PIN and set it's level
ARGS        : take PIN Number and PORT Number and level (LOW,HIGH)
return      : return DIO_OK if the PIN level sets correctly, DIO_NOT_OK otherwise
*/
EN_DIO_ERROR DIO_write(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber,EN_DIO_LEVEL level){
	
	if(pinNumber>7 || pinNumber < 0) return DIO_NOT_OK; // handle pin number error
	switch(portNumber){
		case DIO_PORTA:
		if(level == LOW)CLEAR_BIT(PORTA,pinNumber);
		else if (level == HIGH) SET_BIT(PORTA,pinNumber);
		else return DIO_NOT_OK ; // handle direction error
		break;
		case DIO_PORTB:
		if(level == LOW)CLEAR_BIT(PORTB,pinNumber);
		else if (level == HIGH) SET_BIT(PORTB,pinNumber);
		else return DIO_NOT_OK ; // handle direction error
		break;
		case DIO_PORTC:
		if(level == LOW)CLEAR_BIT(PORTC,pinNumber);
		else if (level == HIGH) SET_BIT(PORTC,pinNumber);
		else return DIO_NOT_OK ; // handle direction error
		break;
		case DIO_PORTD:
		if(level == LOW)CLEAR_BIT(PORTD,pinNumber);
		else if (level == HIGH) SET_BIT(PORTD,pinNumber);
		else return DIO_NOT_OK ; // handle direction error
		break;
		default:
		return DIO_NOT_OK; //handle port number error
	}
	
	return DIO_OK;
}

/*
Description : This function toggles PIN level
ARGS        : take PIN Number and PORT Number
return      : return DIO_OK if the PIN toggles correctly, DIO_NOT_OK otherwise
*/
EN_DIO_ERROR DIO_toggle(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber){
	if(pinNumber>7 || pinNumber < 0) return DIO_NOT_OK; // handle pin number error
	switch(portNumber){
		case DIO_PORTA:
		TOGGLE_BIT(PORTA,pinNumber);
		break;
		case DIO_PORTB:
		TOGGLE_BIT(PORTB,pinNumber);
		break;
		case DIO_PORTC:
		TOGGLE_BIT(PORTC,pinNumber);
		break;
		case DIO_PORTD:
		TOGGLE_BIT(PORTD,pinNumber);
		break;
		default:
		return DIO_NOT_OK; //handle port number error
	}
	
	return DIO_OK;
}

/*
Description : This function reads PIN level and store it in the variable
ARGS        : take PIN Number and PORT Number and pointer to the variable
return      : return DIO_OK if the PIN value stored correctly , DIO_NOT_OK otherwise
*/
EN_DIO_ERROR DIO_read(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber, uint8_t * value){
	
	if(pinNumber>7 || pinNumber < 0) return DIO_NOT_OK; // handle pin number error
	switch(portNumber){
		case DIO_PORTA:
		*value = GET_BIT(PINA,pinNumber);
		break;
		case DIO_PORTB:
		*value = GET_BIT(PINB,pinNumber);
		break;
		case DIO_PORTC:
		*value = GET_BIT(PINC,pinNumber);
		break;
		case DIO_PORTD:
		*value = GET_BIT(PIND,pinNumber);
		break;
		default:
		return DIO_NOT_OK; //handle port number error
	}
	
	return DIO_OK;
}


void DIO_init_TEST(void)
{
	uint8_t returnValue;
	// THIS WILL RETURN DIO_OKAY  HAPPYCASE
	returnValue = DIO_init(DIO_PIN7,DIO_PORTD,OUTPUT);
	if(!returnValue)DIO_write(DIO_PIN7,DIO_PORTD,HIGH);
	// THIS WILL RETURN DIO_NOT_OKAY WORST CASE
	returnValue = DIO_init(DIO_PIN6,DIO_PORTD,6);
	if(!returnValue)DIO_write(DIO_PIN6,DIO_PORTD,HIGH);
}
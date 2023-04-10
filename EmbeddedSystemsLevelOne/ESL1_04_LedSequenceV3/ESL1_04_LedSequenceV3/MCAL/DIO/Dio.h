/*
 * Dio.h
 *
 * Created: 4/7/2023 2:45:22 PM
 *  Author: sharb
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "../../Utilities/BitMath.h"
#include "../../Utilities/Registers.h"

// DIO TYPEDEFS

typedef enum EN_DIO_ERROR{
	DIO_OK=0,
	DIO_NOT_OK
	}EN_DIO_ERROR;

typedef enum EN_DIO_PINS{
	DIO_PIN0=0,
	DIO_PIN1,
	DIO_PIN2,
	DIO_PIN3,
	DIO_PIN4,
	DIO_PIN5,
	DIO_PIN6,
	DIO_PIN7,

}EN_DIO_PINS;

typedef enum EN_DIO_PORTS{
	DIO_PORTA=0,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD
}EN_DIO_PORTS;

typedef enum EN_DIO_DIRECTION{
	INPUT=0,
	OUTPUT
	}EN_DIO_DIRECTION;

typedef enum EN_DIO_LEVEL{
	LOW=0,
	HIGH
}EN_DIO_LEVEL;	

// DIO MACROS
  
  
  
// DIO FUNCTIONS PROTOTYPES

/*
Description : This function initialize PIN and set it's direction 
ARGS        : take PIN Number and PORT Number and Direction (INPUT,OUTPUT)
return      : return DIO_OK if the PIN initializes correctly, DIO_NOT_OK otherwise
*/
EN_DIO_ERROR DIO_init(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber,EN_DIO_DIRECTION direction);

/*
Description : This function write on PIN and set it's level
ARGS        : take PIN Number and PORT Number and level (LOW,HIGH)
return      : return DIO_OK if the PIN level sets correctly, DIO_NOT_OK otherwise
*/
EN_DIO_ERROR DIO_write(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber,EN_DIO_LEVEL level);

/*
Description : This function toggles PIN level 
ARGS        : take PIN Number and PORT Number
return      : return DIO_OK if the PIN toggles correctly, DIO_NOT_OK otherwise
*/
EN_DIO_ERROR DIO_toggle(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber);

/*
Description : This function reads PIN level and store it in the variable
ARGS        : take PIN Number and PORT Number and pointer to the variable
return      : return DIO_OK if the PIN value stored correctly , DIO_NOT_OK otherwise
*/
EN_DIO_ERROR DIO_read(EN_DIO_PINS pinNumber,EN_DIO_PORTS portNumber, uint8_t * value);


void DIO_init_TEST(void);
#endif /* DIO_H_ */
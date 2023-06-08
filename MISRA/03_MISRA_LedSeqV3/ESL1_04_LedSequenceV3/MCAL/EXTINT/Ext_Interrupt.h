/*
 * Ext_Interrupt.h
 *
 * Created: 4/7/2023 11:19:13 PM
 *  Author: sharpel
 */ 


#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_

#include "BitMath.h"
#include "Registers.h"
#include "vect_table.h"

// EXT_INT TYPEDEFS
typedef enum EN_EXTINT_ERROR {
	EXTINT_OK=0,
	EXTINT_NOT_OK
}EN_EXTINT_ERROR;

typedef enum EN_Sence_Control {
	LOW_LEVEL=0,
	FALLING_EDGE,
	RISING_EDGE,
	ANY_LOGICAL_CHANGE
}EN_Sence_Control;

typedef enum EN_EXINT_NUMBER{
	EXTINT0=0,
	EXTINT1,
	EXTINT2,
}EN_EXINT_NUMBER;

typedef enum EN_GLOBAL_INT{
	DISABLE=0,
	ENABLE
}EN_GLOBAL_INT;



EN_EXTINT_ERROR EXTINT_init(EN_EXINT_NUMBER INTx ,EN_Sence_Control INTxSense);
EN_EXTINT_ERROR EXTINT_CallBack(EN_EXINT_NUMBER INTx,void(*ptrfunc)(void));

#endif /* EXT_INTERRUPT_H_ */
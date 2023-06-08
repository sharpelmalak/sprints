/*
 * Ext_Interrupt.c
 *
 * Created: 4/7/2023 11:19:36 PM
 *  Author: sharpel
 */ 

#include "Ext_Interrupt.h"


void (*ptrINT0)(void) = null;
void (*ptrINT1)(void) = null;
void (*ptrINT2)(void) = null;
static void SET_GLOBAL_INTERRUPT(EN_GLOBAL_INT state);


static void SET_GLOBAL_INTERRUPT(EN_GLOBAL_INT state)
{
	
	if(state == ENABLE)
	{
		SET_BIT(SREG,7);
	}
    else if (state == DISABLE)
	{
		CLEAR_BIT(SREG,7);
	}
	
	else 
	{
		//nothing
	}
	
}

EN_EXTINT_ERROR EXTINT_init(EN_EXINT_NUMBER INTx ,EN_Sence_Control INTxSense)
{
	
	EN_EXTINT_ERROR enu_extInt_retvl = EXTINT_OK;
	switch(INTx)
	{
		case EXTINT0:
		  if(INTxSense == LOW_LEVEL)
		  {
			  CLEAR_BIT(MCUCR,0);
			  CLEAR_BIT(MCUCR,1);
		  }
		  else if(INTxSense == FALLING_EDGE)
		  {
			  CLEAR_BIT(MCUCR,0);
			  SET_BIT(MCUCR,1);
		  }
		  else if(INTxSense == RISING_EDGE)
		  {
			  SET_BIT(MCUCR,0);
			  SET_BIT(MCUCR,1);
		  }
		  else if(INTxSense == ANY_LOGICAL_CHANGE)
		  {
			  SET_BIT(MCUCR,0);
			  CLEAR_BIT(MCUCR,1);
		  }
		  else   // handle sense option error
		  {
			 enu_extInt_retvl = EXTINT_NOT_OK;
		  }	
		  
		  if(enu_extInt_retvl == EXTINT_OK)
		  {
			SET_BIT(GICR,6); //Enable External INT0  (PIE)
		  }
		  else
		  {
		    // Nothing
		  }   

		  break;
		case EXTINT1:
		  if(INTxSense == LOW_LEVEL)
		  {
			  CLEAR_BIT(MCUCR,2);
			  CLEAR_BIT(MCUCR,3);
		  }
		  else if(INTxSense == FALLING_EDGE)
		  {
			  CLEAR_BIT(MCUCR,2);
			  SET_BIT(MCUCR,3);
		  }
		  else if(INTxSense == RISING_EDGE)
		  {
			  SET_BIT(MCUCR,2);
			  SET_BIT(MCUCR,3);
		  }
		  else if(INTxSense == ANY_LOGICAL_CHANGE)
		  {
			  SET_BIT(MCUCR,2);
			  CLEAR_BIT(MCUCR,3);
		  }
		   else   // handle sense option error
		   {
			   enu_extInt_retvl = EXTINT_NOT_OK;
		   }
		   
		   if(enu_extInt_retvl == EXTINT_OK)
		   {
			   SET_BIT(GICR,7); //Enable External INT1  (PIE)
		   }
		   else
		   {
			   // Nothing
		   }
		  break;
		case EXTINT2:
		 
		  if(INTxSense == FALLING_EDGE)
		  {
			  CLEAR_BIT(MCUCSR,6);
		  }
		  else if(INTxSense == RISING_EDGE)
		  {
			  SET_BIT(MCUCSR,6);
		  }
		   else   // handle sense option error
		   {
			   enu_extInt_retvl = EXTINT_NOT_OK;
		   }
		   
		   if(enu_extInt_retvl == EXTINT_OK)
		   {
			   SET_BIT(GICR,5); //Enable External INT2  (PIE)
		   }
		   else
		   {
			   // Nothing
		   }
		  break;
		default: // handle wrong Choose for EXT Interrupt Number
	      enu_extInt_retvl = EXTINT_NOT_OK;
		  break;
	}
	
	if(enu_extInt_retvl == EXTINT_OK)
	{
		SET_GLOBAL_INTERRUPT(ENABLE);
	}
	else
	{
		//nothing
	}
	return enu_extInt_retvl;
}

EN_EXTINT_ERROR EXTINT_CallBack(EN_EXINT_NUMBER INTx,void(*ptrfunc)(void))
{
	EN_EXTINT_ERROR enu_extInt_retval = EXTINT_OK;
	if(ptrfunc == null)
	{
		enu_extInt_retval = EXTINT_NOT_OK;
	}
	else
	{
		switch(INTx)
		{
			case EXTINT0:
			{
				ptrINT0 = ptrfunc;
				break;
			}
			case EXTINT1:
			{
				ptrINT1 = ptrfunc;
				break;
			}
			case EXTINT2:
			{
				ptrINT2 = ptrfunc;
				break;
			}
			default:
			{
				enu_extInt_retval = EXTINT_NOT_OK;
				break;
			}
		}
	}
	
	return enu_extInt_retval;
}


ISR (EXT_INT_0)
{
	if(ptrINT0 != null)
	{
	  ptrINT0();	
	}
	else
	{
		//nothing
	} 
}

ISR (EXT_INT_1)
{
	if(ptrINT1 != null)
	{
		ptrINT1();
	}
	else
	{
		//nothing
	}
}

ISR (EXT_INT_2)
{
	if(ptrINT2 != null)
	{
		ptrINT2();
	}
	else
	{
		//nothing
	}
}
/*
* usart_program.c
*
* Created: 5/23/2023 6:29:09 PM
*  Author: Sharpel
*/


#include <ctype.h>
#include "../../COMMON/vect_table.h"
#include "../../COMMON/bit_math.h"
#include "usart_private.h"
#include "usart_interface.h"
void update_queue(void);
static en_usart_error_code_t insert_queue(uint8_t uint8_arg_byte);
static en_usart_error_code_t truncate_queue();

#if USART_INTERRUPT_OPTION == USART_ENABLE_INTERRUPT
void (*ptr_USART_send)(void) = NULL;
void (*ptr_USART_recieve)(void) = NULL;
en_usart_error_code_t USART_setCallBack(en_usart_operating_state_t en_usart_operating_state ,void(*ptr_func)(void))
{
	en_usart_error_code_t en_usart_error_code_return = STATUS_OK;
	if(ptr_func != NULL)
	{
		switch(en_usart_operating_state)
		{
			case USART_SEND_STATE:
			{
				ptr_USART_send = ptr_func ;
				break;
			}
			
			case USART_RECIEVE_STATE:
			{
				ptr_USART_recieve = ptr_func ;
				break;
			}
			
			default:
			{
				en_usart_error_code_return = CALL_BACK_ERROR;
			}
		}
	}
	else
	{
		en_usart_error_code_return = CALL_BACK_ERROR;
	}
	
	return en_usart_error_code_return;
}

typedef struct
{
	uint8_t uint8_arr_tasks[TASKS_MAX_SIZE];
	sint8_t sint_front_queue;
	sint8_t sint_rear_queue;
}str_usart_tasks_queue_t;

str_usart_tasks_queue_t  str_gl_usart_tasks_queue =
{
	.sint_front_queue = -1 ,
	.sint_rear_queue  = -1 ,
};

vuint8_t  gl_recieve_arr[TASKS_MAX_SIZE]="";
vuint8_t  gl_recieve_index = 0;
vuint8_t  gl_recieve_size = NULL;
//vuint8_t gl_isSent = 0;
//vuint8_t gl_isReceive = 0;
#endif
static en_usart_error_code_t insert_queue(uint8_t uint8_arg_byte)
{
    en_usart_error_code_t en_usart_error_code_return = STATUS_OK;
	if( str_gl_usart_tasks_queue.sint_rear_queue >= TASKS_MAX_SIZE)
	{
		en_usart_error_code_return = QUEUE_OVERFLOW;
	}
	else
	{
		if(str_gl_usart_tasks_queue.sint_front_queue < 0)
		{
			str_gl_usart_tasks_queue.sint_front_queue = 0;
		}
		
		str_gl_usart_tasks_queue.sint_rear_queue++;
		str_gl_usart_tasks_queue.uint8_arr_tasks[str_gl_usart_tasks_queue.sint_rear_queue] = uint8_arg_byte;
	}	
	
	return en_usart_error_code_return;
}
static en_usart_error_code_t truncate_queue()
{
	en_usart_error_code_t en_usart_error_code_return = STATUS_OK;
	if((str_gl_usart_tasks_queue.sint_front_queue > str_gl_usart_tasks_queue.sint_rear_queue) || (str_gl_usart_tasks_queue.sint_front_queue == -1))
	{
		
		str_gl_usart_tasks_queue.sint_front_queue = -1;
		str_gl_usart_tasks_queue.sint_rear_queue  = -1;
		en_usart_error_code_return = QUEUE_EMPTY;
	}
	else
	{
		UDR = str_gl_usart_tasks_queue.uint8_arr_tasks[str_gl_usart_tasks_queue.sint_front_queue];
		str_gl_usart_tasks_queue.sint_front_queue ++;
	}
	return en_usart_error_code_return;
}

en_usart_error_code_t USART_init(uint8_t uint8_arg_channel_id)
{
	en_usart_error_code_t en_usart_error_code_return = STATUS_OK;
	uint8_t uint8_local_counter = 0 ;
	const str_usart_configs_t *str_usart_configs = NULL ;
	for(uint8_local_counter = 0 ; uint8_local_counter < USART_CHANNELS;uint8_local_counter++)
	{
		if(uint8_local_counter == str_gl_usart_arr_configs[uint8_local_counter].uint8_channel_id)
		{
			str_usart_configs = &str_gl_usart_arr_configs[uint8_local_counter];
			break;
		}
	}
	
	if(str_usart_configs == NULL)
	{
		en_usart_error_code_return = CHANNEL_NOT_FOUND;
	}
	else
	{
		//// select UCSRC register
		SET_BIT(UCSRC,URSEL);
		
		switch(str_usart_configs->en_usart_set_mode)
		{
			case USART_ASYNC_MODE:
			{
				CLEAR_BIT(UCSRC,UMSEL);
				break;
			}
			
			case USART_SYNC_MODE:
			{
				SET_BIT(UCSRC,UMSEL);
				break;
			}
			
			default:
			{
				en_usart_error_code_return = CONFIG_ERROR;
				break;
			}
		}
		
		if(en_usart_error_code_return == STATUS_OK)
		{
			switch(str_usart_configs->en_usart_operating_state)
			{
				case USART_SEND_STATE:
				{
					CLEAR_BIT(UCSRB,RXEN);
					SET_BIT(UCSRB,TXEN);
					break;
				}
				
				case USART_RECIEVE_STATE:
				{
					SET_BIT(UCSRB,RXEN);
					CLEAR_BIT(UCSRB,TXEN);
					break;
				}
				
				case USART_FULL_DUBLEX_STATE:
				{
					SET_BIT(UCSRB,RXEN);
					SET_BIT(UCSRB,TXEN);
					break;
				}
				default:
				{
					en_usart_error_code_return = CONFIG_ERROR;
					break;
				}
			}
		}
			if(en_usart_error_code_return == STATUS_OK)
			{
				switch(str_usart_configs->en_usart_parity_select)
				{
					case USART_EVEN_PARITY:
					{
						CLEAR_BIT(UCSRC,UPM0);
						SET_BIT(UCSRC,UPM1);
						break;
					}
					
					case USART_ODD_PARITY:
					{
						SET_BIT(UCSRC,UPM0);
						SET_BIT(UCSRC,UPM1);
						break;
					}
					
					case USART_DIS_PARITY:
					{
						CLEAR_BIT(UCSRC,UPM0);
						CLEAR_BIT(UCSRC,UPM1);
						break;
					}
					default:
					{
						en_usart_error_code_return = CONFIG_ERROR;
						break;
					}
				}
			}
			
			if(en_usart_error_code_return == STATUS_OK)
			{
				switch(str_usart_configs->en_usart_stop_bit_select)
				{
					case USART_ONE_STOP_BIT:
					{
						CLEAR_BIT(UCSRC,USBS);
						break;
					}
					
					case USART_TWO_STOP_BITS:
					{
						SET_BIT(UCSRC,USBS);
						break;
					}
					
					default:
					{
						en_usart_error_code_return = CONFIG_ERROR;
						break;
					}
				}
			}
			
			if(en_usart_error_code_return == STATUS_OK)
			{
				switch(str_usart_configs->en_usart_data_size_select)
				{
					case USART_DATA_SIZE_5:
					{
						CLEAR_BIT(UCSRC,UCSZ0);
						CLEAR_BIT(UCSRC,UCSZ1);
						CLEAR_BIT(UCSRB,UCSZ2);
						break;
					}
					
					case USART_DATA_SIZE_6:
					{
						SET_BIT(UCSRC,UCSZ0);
						CLEAR_BIT(UCSRC,UCSZ1);
						CLEAR_BIT(UCSRB,UCSZ2);
						break;
					}
					
					case USART_DATA_SIZE_7:
					{
						CLEAR_BIT(UCSRC,UCSZ0);
						SET_BIT(UCSRC,UCSZ1);
						CLEAR_BIT(UCSRB,UCSZ2);
						break;
					}
					
					case USART_DATA_SIZE_8:
					{
						SET_BIT(UCSRC,UCSZ0);
						SET_BIT(UCSRC,UCSZ1);
						CLEAR_BIT(UCSRB,UCSZ2);
						break;
					}
					
					case USART_DATA_SIZE_9:
					{
						SET_BIT(UCSRC,UCSZ0);
						SET_BIT(UCSRC,UCSZ1);
						SET_BIT(UCSRB,UCSZ2);
						break;
					}
					default:
					{
						en_usart_error_code_return = CONFIG_ERROR;
						break;
					}
				}
			}
			/* select interrupt option (Enable,disable) */
			#if USART_INTERRUPT_OPTION == USART_ENABLE_INTERRUPT
			
			SET_BIT(UCSRB,RXCIE);
			SET_BIT(UCSRB,TXCIE);
			sei(); // enable global interrupt
			
			#elif USART_INTERRUPT_OPTION == USART_DISABLE_INTERRUPT
			
			CLEAR_BIT(UCSRB,RXCIE);
			CLEAR_BIT(UCSRB,TXCIE);
			CLEAR_BIT(UCSRB,UDRIE);
			
			#else
			en_usart_error_code_return = CONFIG_ERROR;
			#endif
			
			
			/* select USART Speed (Normal,Double) */
			#if USART_SPEED_SELECT == USART_NORMAL_SPEED
			
			CLEAR_BIT(UCSRA,U2X);
			// set baud rate for normal speed
			UBRRL = BAUD_PRESCALLER;
			UBRRH = (BAUD_PRESCALLER>>8);
			
			#elif USART_SPEED_SELECT == USART_DOUBLE_SPEED
			
			SET_BIT(UCSRA,U2X);
			// set baud rate for Double speed
			UBRRL = BAUD_PRESCALLER_DOUBLE_SPEED;
			UBRRH = (BAUD_PRESCALLER_DOUBLE_SPEED>>8);
			
			#else
			en_usart_error_code_return = CONFIG_ERROR;
			#endif
			
		}
		
		return en_usart_error_code_return;
}
en_usart_error_code_t USART_send_byte(uint8_t uint8_arg_byte)
{
	en_usart_error_code_t en_usart_error_code_return = STATUS_OK;
	
	#if USART_INTERRUPT_OPTION == USART_ENABLE_INTERRUPT
	
	en_usart_error_code_return = insert_queue(uint8_arg_byte);
	truncate_queue();
	
	
	#else
	// WAIT UNTIL ISEMPTY FLAG IS SET
	while(!GET_BIT(UCSRA,UDRE));
	
	// assign data to UDR register to be sent
	
	UDR = uint8_arg_byte;
	
	#endif
	
	return en_usart_error_code_return ;
}
en_usart_error_code_t USART_send_n_bytes(uint8_t *uint8_arg_arr_bytes,uint8_t uint8_arg_arr_size)
{
	en_usart_error_code_t en_usart_error_code_return = STATUS_OK;
	uint8_t uint8_loc_counter = 0;
	#if USART_INTERRUPT_OPTION == USART_ENABLE_INTERRUPT
	
	if(uint8_arg_arr_bytes == NULL)
	{
		en_usart_error_code_return = CALL_BACK_ERROR; // NULL POINTER
	}
	else
	{
		// set size in the queue
		insert_queue(uint8_arg_arr_size);
		while(uint8_loc_counter < uint8_arg_arr_size)
		{
			en_usart_error_code_return = insert_queue(uint8_arg_arr_bytes[uint8_loc_counter]);
			if(en_usart_error_code_return != STATUS_OK)
			{
				break;
			}
			uint8_loc_counter++;
		}
		
		truncate_queue();
	}
	
	
	
	#else
	
	
	while(uint8_arg_arr_bytes[uint8_loc_counter]!= NULL)
	{
	   USART_send_byte(uint8_arg_arr_bytes[uint8_loc_counter]);	
	   uint8_loc_counter++
	}
	#endif
	
	return en_usart_error_code_return ;
}	
en_usart_error_code_t USART_recieve_byte(uint8_t *uint8_arg_byte)
{
	
    en_usart_error_code_t en_usart_error_code_return = STATUS_OK;
    
    #if USART_INTERRUPT_OPTION == USART_ENABLE_INTERRUPT
    
    //do nothing
    
    #else
    // WAIT UNTIL ISrecieved FLAG IS SET
    while(!GET_BIT(UCSRA,RXC));
    
    // assign data to UDR register to be sent
    
    *uint8_arg_byte = UDR;
    
    #endif
    
    return en_usart_error_code_return ;	
}
en_usart_error_code_t USART_recieve_n_bytes(uint8_t *uint8_arg_arr_bytes,uint8_t uint8_arg_arr_size)
{
	//BLOCKING ONLY
	uint8_t uint8_loc_counter=0;
	while(uint8_loc_counter < uint8_arg_arr_size)
	{
		USART_recieve_byte(&uint8_arg_arr_bytes[uint8_loc_counter]);
		uint8_loc_counter++;
	}
	
	return STATUS_OK;
}

	



ISR(USART_RXC_INT)
{
	

	 if(gl_recieve_size == NULL)
	 {
		 // convert size to integer number
		 gl_recieve_size = UDR;
		 if(gl_recieve_size < '0' || gl_recieve_size > '9')
		 {
			 //nothing
		 }
		 else
		 {
			 gl_recieve_size-='0';
		 }
	 }
	 else if(gl_recieve_index < gl_recieve_size)
	 {
		 gl_recieve_arr[gl_recieve_index] = UDR ;
		 gl_recieve_index++;
	 }
	 
	 if(gl_recieve_index == gl_recieve_size && gl_recieve_size != NULL)
	 {
		 gl_recieve_index = 0;
		 gl_recieve_size = NULL;
		 ptr_USART_recieve();
		 
	 }

	
}
	
ISR(USART_TXC_INT)
{
	if (truncate_queue()==QUEUE_EMPTY)
	{
		ptr_USART_send();
	}

}
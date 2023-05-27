/*
* usart_program.c
*
* Created: 5/23/2023 6:29:09 PM
*  Author: Sharpel
*/


#include "../../COMMON/vect_table.h"
#include "../../COMMON/bit_math.h"
#include "usart_private.h"
#include "usart_interface.h"

/*insert queue simply insert desired data to be sent in queue*/
static en_usart_error_code_t insert_queue(uint8_t uint8_arg_byte);

/*truncate queue simply dequeue desired data to be sent*/
static en_usart_error_code_t truncate_queue();

#if USART_INTERRUPT_OPTION == USART_ENABLE_INTERRUPT


void (*ptr_USART_send)   (void) = NULL;
void (*ptr_USART_recieve)(void) = NULL;


str_usart_tasks_queue_t  str_gl_usart_tasks_queue =
{
	.sint_front_queue = EMPTY_POSITOIN ,
	.sint_rear_queue  = EMPTY_POSITOIN ,
};

vuint8_t  gl_recieve_arr[TASKS_MAX_SIZE]="";
vuint8_t  gl_recieve_index = NULL;
vuint8_t  gl_recieve_size  = NULL;

// function to handle enqueue operation
static en_usart_error_code_t insert_queue(uint8_t uint8_arg_byte)
{
	//status code
	en_usart_error_code_t en_usart_error_code_return = STATUS_OK;
	
	//check if queue full
	if( str_gl_usart_tasks_queue.sint_rear_queue >= TASKS_MAX_SIZE)
	{
		en_usart_error_code_return = QUEUE_OVERFLOW;
	}
	else
	{
		//check if queue empty
		if(str_gl_usart_tasks_queue.sint_front_queue == EMPTY_POSITOIN)
		{
			str_gl_usart_tasks_queue.sint_front_queue = FALSE;
		}
		
		// increment rear then store byte in queue
		str_gl_usart_tasks_queue.sint_rear_queue++;
		str_gl_usart_tasks_queue.uint8_arr_tasks[str_gl_usart_tasks_queue.sint_rear_queue] = uint8_arg_byte;
	}
	
	return en_usart_error_code_return;
}

// function to handle dequeue operation
static en_usart_error_code_t truncate_queue()
{
	
	// status code okay
	en_usart_error_code_t en_usart_error_code_return = STATUS_OK;
	
	// check if all bytes has been sent OR queue is empty
	if((str_gl_usart_tasks_queue.sint_front_queue > str_gl_usart_tasks_queue.sint_rear_queue) || (str_gl_usart_tasks_queue.sint_front_queue == EMPTY_POSITOIN))
	{
		// set front and rear to defaults
		str_gl_usart_tasks_queue.sint_front_queue = EMPTY_POSITOIN;
		str_gl_usart_tasks_queue.sint_rear_queue  = EMPTY_POSITOIN;
		
		//status code queue is empty
		en_usart_error_code_return = QUEUE_EMPTY;
	}
	else
	{
		//send current byte and increment front
		UDR = str_gl_usart_tasks_queue.uint8_arr_tasks[str_gl_usart_tasks_queue.sint_front_queue];
		str_gl_usart_tasks_queue.sint_front_queue ++;
	}
	return en_usart_error_code_return;
}

#endif


en_usart_error_code_t USART_init(uint8_t uint8_arg_channel_id)
{
	//status code okay
	en_usart_error_code_t en_usart_error_code_return = STATUS_OK;
	uint8_t uint8_local_counter = 0 ;
	
	//create instance of usart configs
	const str_usart_configs_t *str_usart_configs = NULL ;
	
	//search for desired config from channel id sent
	for(uint8_local_counter = 0 ; uint8_local_counter < USART_CHANNELS;uint8_local_counter++)
	{
		if(uint8_local_counter == str_gl_usart_arr_configs[uint8_local_counter].uint8_channel_id)
		{
			//point to desired channel
			str_usart_configs = &str_gl_usart_arr_configs[uint8_local_counter];
			break;
		}
	}
	
	// handle channel error
	if(str_usart_configs == NULL)
	{
		en_usart_error_code_return = CHANNEL_NOT_FOUND;
	}
	else
	{
		//// select UCSRC register
		SET_BIT(UCSRC,URSEL);
		
		// config all options
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
				//status config error
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
	//status code okay
	en_usart_error_code_t en_usart_error_code_return = STATUS_OK;
	
	#if USART_INTERRUPT_OPTION == USART_ENABLE_INTERRUPT
	
	//store size of byte --> 1 in queue
	insert_queue(TRUE);
	
	//store the byte in queue
	insert_queue(uint8_arg_byte);
	
	//dequeue
	truncate_queue();
	
	
	#else //Blocking
	
	// WAIT UNTIL ISEMPTY FLAG IS SET
	while(!GET_BIT(UCSRA,UDRE));
	
	// assign data to UDR register to be sent
	
	UDR = uint8_arg_byte;
	
	#endif
	
	return en_usart_error_code_return ;
}


en_usart_error_code_t USART_send_n_bytes(uint8_t *uint8_arg_arr_bytes,uint8_t uint8_arg_arr_size)
{
	//status code okay
	en_usart_error_code_t en_usart_error_code_return = STATUS_OK;
	uint8_t uint8_loc_counter = FALSE;
	#if USART_INTERRUPT_OPTION == USART_ENABLE_INTERRUPT
	
	//check on pointer argument
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
			//set all bytes from array in order
			en_usart_error_code_return = insert_queue(uint8_arg_arr_bytes[uint8_loc_counter]);
			if(en_usart_error_code_return != STATUS_OK)
			{
				// case of overflow
				break;
			}
			uint8_loc_counter++;
		}
		
		//dequeue
		truncate_queue();
	}
	
	
	
	#else // Blocking
	
	
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
	
	// WAIT UNTIL ISrecieved FLAG IS SET
	while(!GET_BIT(UCSRA,RXC));
	
	// assign data to UDR register to be sent
	
	*uint8_arg_byte = UDR;
	
	
	
	return en_usart_error_code_return ;
}
en_usart_error_code_t USART_recieve_n_bytes(uint8_t *uint8_arg_arr_bytes,uint8_t uint8_arg_arr_size)
{
	//BLOCKING ONLY
	uint8_t uint8_loc_counter=FALSE;
	while(uint8_loc_counter < uint8_arg_arr_size)
	{
		USART_recieve_byte(&uint8_arg_arr_bytes[uint8_loc_counter]);
		uint8_loc_counter++;
	}
	
	return STATUS_OK;
}


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



ISR(USART_RXC_INT)
{
	
	if(gl_recieve_size == NULL)
	{
		// recieve size
		gl_recieve_size = UDR;
	}
	else if(gl_recieve_index < gl_recieve_size)
	{
		gl_recieve_arr[gl_recieve_index] = UDR ;
		gl_recieve_index++;
	}
	
	//receiving done
	if(gl_recieve_index == gl_recieve_size && gl_recieve_size != NULL)
	{
		gl_recieve_index = NULL;
		gl_recieve_size  = NULL;
		
		//fire call back
		ptr_USART_recieve();
		
	}

	
}

ISR(USART_TXC_INT)
{
	// check if queue is empty
	if (truncate_queue()==QUEUE_EMPTY)
	{
		// fire send call back
		ptr_USART_send();
	}

}
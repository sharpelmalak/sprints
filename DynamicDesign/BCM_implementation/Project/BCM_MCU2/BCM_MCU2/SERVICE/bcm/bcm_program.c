/*
 * bcm_program.c
 *
 * Created: 5/24/2023 4:57:37 PM
 *  Author: sharb
 */ 

#include "bcm_interface.h"

void bcm_send_done(void);
void bcm_recieve_done(void);

vuint8_t gl_bcm_send_done    = FALSE ;
vuint8_t gl_bcm_recieve_done = FALSE ;
extern vuint8_t  gl_recieve_arr[TASKS_MAX_SIZE];

enu_bcm_status_t bcm_init (str_bcm_instance_t * ptr_str_bcm_instance)
{
	enu_bcm_status_t enu_bcm_status_return = BCM_OKAY;
	uint8_t uint8_loc_counter = FALSE ;
	if(ptr_str_bcm_instance == NULL)
	{
		enu_bcm_status_return = NULL_POINTER;
	}
	else
	{
         for(uint8_loc_counter = FALSE ; uint8_loc_counter < BCM_INSTANCES ; uint8_loc_counter ++)
         {
	         if(ptr_str_bcm_instance->en_bcm_channel == str_bcm_instance[uint8_loc_counter].en_bcm_channel)
	         {
		         str_bcm_instance[uint8_loc_counter].str_bcm_functions_pointer.ptr_func_init(ptr_str_bcm_instance->en_bcm_channel);
		         str_bcm_instance[uint8_loc_counter].str_bcm_functions_pointer.ptr_func_setCall(USART_SEND_STATE,bcm_send_done);
		         str_bcm_instance[uint8_loc_counter].str_bcm_functions_pointer.ptr_func_setCall(USART_RECIEVE_STATE,bcm_recieve_done);
		         break;
	         }
         }
         
         if(uint8_loc_counter == BCM_INSTANCES)
         {
	         enu_bcm_status_return = CHANNEL_ERROR;
         }
	}
	
	return enu_bcm_status_return;
}

enu_bcm_status_t bcm_deinit (str_bcm_instance_t * ptr_str_bcm_instance)
{
	enu_bcm_status_t enu_bcm_status_return = BCM_OKAY;
	if((ptr_str_bcm_instance != NULL) && (ptr_str_bcm_instance->en_bcm_channel != NULL))
	{
		ptr_str_bcm_instance->en_bcm_channel = NULL;
	}
	
	else
	{
		enu_bcm_status_return = NULL_POINTER;
	}
	
	return enu_bcm_status_return;
}

enu_bcm_status_t bcm_send (str_bcm_instance_t * ptr_str_bcm_instance , uint8_t uint8_arg_byte)
{
	enu_bcm_status_t enu_bcm_status_return = BCM_OKAY;
	uint8_t uint8_loc_counter = FALSE ;
	
	if(ptr_str_bcm_instance == NULL)
	{
		enu_bcm_status_return = NULL_POINTER;
	}
	else
	{
		for(uint8_loc_counter = 0 ; uint8_loc_counter < BCM_INSTANCES ; uint8_loc_counter ++)
		{
			if(ptr_str_bcm_instance->en_bcm_channel == str_bcm_instance[uint8_loc_counter].en_bcm_channel)
			{
				str_bcm_instance[uint8_loc_counter].str_bcm_functions_pointer.ptr_func_send(uint8_arg_byte);
				break;
			}
		}
		
		if(uint8_loc_counter == BCM_INSTANCES)
		{
			enu_bcm_status_return = CHANNEL_ERROR;
		}
	}
	return enu_bcm_status_return;
}
enu_bcm_status_t bcm_send_n (str_bcm_instance_t * ptr_str_bcm_instance ,uint8_t *uint8_arg_bytes,uint8_t uint8_arg_size)
{
	enu_bcm_status_t enu_bcm_status_return = BCM_OKAY;
	uint8_t uint8_loc_counter = FALSE ;
	
	if(ptr_str_bcm_instance == NULL)
	{
		enu_bcm_status_return = NULL_POINTER;
	}
	
	else
	{
		for(uint8_loc_counter = 0 ; uint8_loc_counter < BCM_INSTANCES ; uint8_loc_counter ++)
		{
			if(ptr_str_bcm_instance->en_bcm_channel == str_bcm_instance[uint8_loc_counter].en_bcm_channel)
			{
				str_bcm_instance[uint8_loc_counter].str_bcm_functions_pointer.ptr_func_send_n(uint8_arg_bytes,uint8_arg_size);
				break;
			}
		}
	}
	
	
	if(uint8_loc_counter == BCM_INSTANCES)
	{
		enu_bcm_status_return = CHANNEL_ERROR;
	}
	return enu_bcm_status_return;

}

enu_bcm_status_t bcm_dispatcher (str_bcm_instance_t * ptr_str_bcm_instance_t)
{
	enu_bcm_status_t enu_bcm_status_return = BCM_OKAY;
	
	if(ptr_str_bcm_instance_t == NULL)
	{
		 enu_bcm_status_return = NULL_POINTER;
	}
	else if(gl_bcm_send_done == TRUE)
	{
		enu_bcm_status_return = SEND_OPERATION_DONE;
	}
	
	else if(gl_bcm_recieve_done == TRUE)
	{
		enu_bcm_status_return = REC_OPERATION_DONE;
	}
	
	return enu_bcm_status_return;
}

void bcm_send_done(void)
{
	gl_bcm_send_done=TRUE;
}


void bcm_recieve_done(void)
{
	gl_bcm_recieve_done=TRUE;
}
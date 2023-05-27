/*
 * bcm_instance_config.c
 *
 * Created: 5/24/2023 4:58:23 PM
 *  Author: sharb
 */ 

#include "bcm_instance_config.h"

const str_bcm_instance_t str_bcm_instance[BCM_INSTANCES] =
{
	{
		.en_bcm_comm_type = BCM_USART,
		.en_bcm_channel   = CHANNEL_0,
		.str_bcm_functions_pointer.ptr_func_init    = USART_init,
		.str_bcm_functions_pointer.ptr_func_send    = USART_send_byte,
		.str_bcm_functions_pointer.ptr_func_send_n  = USART_send_n_bytes,
		.str_bcm_functions_pointer.ptr_func_setCall = USART_setCallBack
		
	},
	{
		.en_bcm_comm_type = BCM_SPI,
		.en_bcm_channel   = CHANNEL_1,
		//.str_bcm_functions_pointer.ptr_func_init   = SPI_init;
		//.str_bcm_functions_pointer.ptr_func_send   = SPI_send_byte;
		//.str_bcm_functions_pointer.ptr_func_send_n = SPI_send_n_bytes;
	}
};
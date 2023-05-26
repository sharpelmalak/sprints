/*
 * usart_config.c
 *
 * Created: 5/23/2023 6:29:33 PM
 *  Author: sharpel
 */ 

#include "../../COMMON/std_types.h"
#include "usart_config.h"


const str_usart_configs_t str_gl_usart_arr_configs[USART_CHANNELS] =
{
	{
		.uint8_channel_id             = 0,
		.en_usart_set_mode            = USART_ASYNC_MODE,
		.en_usart_operating_state     = USART_FULL_DUBLEX_STATE,
		.en_usart_parity_select       = USART_DIS_PARITY,
		.en_usart_stop_bit_select     = USART_ONE_STOP_BIT,
		.en_usart_data_size_select    = USART_DATA_SIZE_8,
	},
	{
		.uint8_channel_id             = 1,
		.en_usart_set_mode            = USART_ASYNC_MODE,
		.en_usart_operating_state     = USART_SEND_STATE,
		.en_usart_parity_select       = USART_EVEN_PARITY,
		.en_usart_stop_bit_select     = USART_TWO_STOP_BITS,
		.en_usart_data_size_select    = USART_DATA_SIZE_8,
	}
};


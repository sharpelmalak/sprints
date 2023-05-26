/*
 * usart_interface.h
 *
 * Created: 5/23/2023 6:30:13 PM
 *  Author: Sharpel
 */ 


#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

#include "../../COMMON/std_types.h"
#include "usart_config.h"

#define  PORTA (*(vuint8_t*)(0X3B))
extern const str_usart_configs_t  str_gl_usart_arr_configs[USART_CHANNELS];

typedef enum
{
	STATUS_OK = 0,
	CHANNEL_NOT_FOUND,
	CONFIG_ERROR,
	QUEUE_OVERFLOW,
	QUEUE_EMPTY,
	CALL_BACK_ERROR
}en_usart_error_code_t;

en_usart_error_code_t USART_init(uint8_t uint8_arg_channel_id);
				   
en_usart_error_code_t USART_send_byte(uint8_t uint8_arg_byte);
en_usart_error_code_t USART_send_n_bytes(uint8_t *uint8_arg_arr_bytes,uint8_t uint8_arg_arr_size);
				   
en_usart_error_code_t USART_recieve_byte(uint8_t *uint8_arg_byte);
en_usart_error_code_t USART_recieve_n_bytes(uint8_t *uint8_arg_arr_bytes,uint8_t uint8_arg_arr_size);

en_usart_error_code_t USART_setCallBack(en_usart_operating_state_t en_usart_operating_state , void(*ptr_func)(void));
#endif /* USART_INTERFACE_H_ */
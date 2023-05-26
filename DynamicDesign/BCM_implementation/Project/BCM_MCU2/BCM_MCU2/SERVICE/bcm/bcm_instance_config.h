/*
 * bcm_instance_config.h
 *
 * Created: 5/24/2023 4:58:48 PM
 *  Author: sharb
 */ 


#ifndef BCM_INSTANCE_CONFIG_H_
#define BCM_INSTANCE_CONFIG_H_

#include "../../MCAL/usart/usart_interface.h"

#define BCM_INSTANCES  2
typedef enum
{
	BCM_USART = 0 ,
	BCM_SPI       ,
	BCM_I2C       ,
}en_bcm_comm_type_t;

typedef enum
{
	CHANNEL_0 = 0 ,
	CHANNEL_1     ,
	CHANNEL_2     ,
	CHANNEL_4     ,
}en_bcm_channels_t;

typedef struct
{
	en_usart_error_code_t (*ptr_func_init)(en_bcm_channels_t);
	en_usart_error_code_t (*ptr_func_send)(uint8_t);
	en_usart_error_code_t (*ptr_func_send_n)(uint8_t *,uint8_t);
	en_usart_error_code_t (*ptr_func_setCall)(en_usart_operating_state_t,void *);
}str_bcm_functions_pointers_t;

typedef struct  
{
	en_bcm_comm_type_t en_bcm_comm_type;
	en_bcm_channels_t  en_bcm_channel;
	
	str_bcm_functions_pointers_t str_bcm_functions_pointer;
}str_bcm_instance_t;

#endif /* BCM_INSTANCE_CONFIG_H_ */
/*
 * bcm_interface.h
 *
 * Created: 5/24/2023 4:57:14 PM
 *  Author: sharb
 */ 


#ifndef BCM_INTERFACE_H_
#define BCM_INTERFACE_H_


#include "bcm_instance_config.h"

extern const str_bcm_instance_t str_bcm_instance[BCM_INSTANCES];

typedef enum
{
	BCM_OKAY = 0,
	CHANNEL_ERROR,
	NULL_POINTER,
	SEND_OPERATION_DONE,
	REC_OPERATION_DONE,
	OPERATION_NOT_DONE
	
}enu_bcm_status_t;


enu_bcm_status_t bcm_init (str_bcm_instance_t * ptr_str_bcm_instance);
enu_bcm_status_t bcm_deinit (str_bcm_instance_t * ptr_str_bcm_instance);
enu_bcm_status_t bcm_send (str_bcm_instance_t * ptr_str_bcm_instance , uint8_t uint8_arg_byte);
enu_bcm_status_t bcm_send_n (str_bcm_instance_t * ptr_str_bcm_instance ,uint8_t *uint8_arg_bytes,uint8_t uint8_arg_size);
enu_bcm_status_t bcm_dispatcher (str_bcm_instance_t * ptr_str_bcm_instance_t);




#endif /* BCM_INTERFACE_H_ */
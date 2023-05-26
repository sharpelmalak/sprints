/*
 * app.h
 *
 * Created: 5/25/2023 4:02:39 PM
 *  Author: sharb
 */ 


#ifndef APP_H_
#define APP_H_


#include "../SERVICE/bcm/bcm_interface.h"
#include "../ECUAL/led/led.h"
#include <string.h>


typedef enum
{
	IDLE = 0 ,
	BLOCKED,
}enu_app_states_t;


extern vuint8_t  gl_recieve_arr[TASKS_MAX_SIZE];


void app_init(void);

void app_start(void);

#endif /* APP_H_ */
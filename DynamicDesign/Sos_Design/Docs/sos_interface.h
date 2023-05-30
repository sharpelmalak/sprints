/*
 * sos_interface.h
 *
 * Created: 5/29/2023 7:44:00 PM
 *  Author: sharpel
 */ 


#ifndef SOS_INTERFACE_H_
#define SOS_INTERFACE_H_

#define MAX_TASKS  10

// assuming that lower the priority number having higher priority 
typedef enum
{
  PRIORITY_ONE,
  PRIORITY_TWO,
  PRIORITY_THREE,
  PRIORITY_FOUR,
  PRIORITY_FIVE,
  PRIORITY_SIX,
  PRIORITY_SEVEN,
  PRIORITY_EIGHT,
  PRIORITY_NINE,
  PRIORITY_TEN,
  PRIORITY_TOTAL,	
}enu_task_priority_id_t; 
typedef struct  
{

	uint16_t taskPeriodicity;
	void (*ptr_task_arg)(void);
	void (*ptr_task_ref)(void*);
	
}str_tasks_config_t;


typedef enum
{
	SOS_STATUS_SUCCESS,
	SOS_STATUS_INVALID_STATE,
	SOS_NULL_ARGS,
	SOS_TASK_PERIODICITY_UNKNOWN,
	SOS_TASK_DUBLICATED_PIRIORITY,
	SOS_TASK_NOT_FOUND,
	SOS_TASK_PRIRORITY_ERROR,
	SOS_NO_TASKS_TO_RUN
}enu_system_status_t;

typedef enum
{
	IDLE,
	STOP_RUN,
	FIRST_START,

}enu_run_state_t;

enu_system_status_t sos_init(void);
enu_system_status_t sos_deinit(void);
enu_system_status_t sos_create_task(enu_task_priority_id_t enu_task_priority_id , str_tasks_config_t *str_tasks_config);
enu_system_status_t sos_modify_task(enu_task_priority_id_t enu_task_priority_id ,str_tasks_config_t *str_tasks_config);
enu_system_status_t sos_delete_task(enu_task_priority_id_t enu_task_priority_id);
enu_system_status_t sos_run(void);
enu_system_status_t sos_disable(void);
#endif /* SOS_INTERFACE_H_ */
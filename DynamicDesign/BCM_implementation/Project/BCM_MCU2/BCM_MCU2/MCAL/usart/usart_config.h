/*
 * usart_config.h
 *
 * Created: 5/23/2023 6:30:45 PM
 *  Author: sharb
 */ 


#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

#define F_CPU								8000000UL
#define BAUDRATE							9600


#define BAUD_PRESCALLER                    ((F_CPU/(16UL*BAUDRATE))-1)
#define BAUD_PRESCALLER_DOUBLE_SPEED       ((F_CPU/(8UL*BAUDRATE))-1)


#define USART_NORMAL_SPEED				   0
#define USART_DOUBLE_SPEED				   1

#define USART_ENABLE_INTERRUPT			   0
#define USART_DISABLE_INTERRUPT			   1



#define USART_CHANNELS                     2
#define TASKS_MAX_SIZE                     200

/* USART SPEED SELECT :
1-USART_NORMAL_SPEED
2-USART_DOUBLE_SPEED
*/

#define USART_SPEED_SELECT                 USART_NORMAL_SPEED


/* USART INTERRUPT OPTION :
1-USART_ENABLE_INTERRUPT
2-USART_DISABLE_INTERRUPT
*/

#define USART_INTERRUPT_OPTION             USART_ENABLE_INTERRUPT


/* USART MODE :
1-USART_ASYNC_MODE
2-USART_SYNC_MODE
*/
typedef enum 
{
	USART_ASYNC_MODE = 0 ,
	USART_SYNC_MODE,
	USART_WRONG_MODE
}en_usart_set_mode_t;


/* USART OPERATING STATE :
1-USART_SEND_STATE
2-USART_RECIEVE_STATE
3-USART_FULL_DUBLEX_STATE
*/
typedef enum
{
	USART_SEND_STATE = 0 ,
	USART_RECIEVE_STATE,
	USART_FULL_DUBLEX_STATE,
	USART_WRONG_STATE
}en_usart_operating_state_t;


/* USART PARITY OPTIONS :
1-USART_DIS_PARITY
2-USART_ODD_PARITY
3-USART_EVEN_PARITY
*/
typedef enum 
{
	USART_DIS_PARITY = 0 ,
	USART_ODD_PARITY,
	USART_EVEN_PARITY,
	USART_WRONG_PARITY
}en_usart_parity_select_t;

/* USART STOP BIT OPTIONS :
1-USART_ONE_STOP_BIT
2-USART_TWO_STOP_BITS
*/
typedef enum 
{
	USART_ONE_STOP_BIT = 0 ,
	USART_TWO_STOP_BITS,
	USART_WRONG_STOP_BIT
}en_usart_stop_bit_select_t;

/* USART Data SIZE OPTIONS :
1-USART_DATA_SIZE_5
2-USART_DATA_SIZE_6
3-USART_DATA_SIZE_7
4-USART_DATA_SIZE_8
5-USART_DATA_SIZE_9
*/
typedef enum 
{
	USART_DATA_SIZE_5=0,
	USART_DATA_SIZE_6,
	USART_DATA_SIZE_7,
	USART_DATA_SIZE_8,
	USART_DATA_SIZE_9,
	USART_DATA_SIZE_WRONG,
}en_usart_data_size_select_t;


typedef struct
{
	uint8_t                      uint8_channel_id;
	en_usart_set_mode_t          en_usart_set_mode;
	en_usart_operating_state_t   en_usart_operating_state;
	en_usart_parity_select_t     en_usart_parity_select;
	en_usart_stop_bit_select_t   en_usart_stop_bit_select;
	en_usart_data_size_select_t  en_usart_data_size_select;

}str_usart_configs_t;




#endif /* USART_CONFIG_H_ */
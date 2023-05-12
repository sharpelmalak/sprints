

#include "linking_config.h"

const ST_USART_CONF st_g_USARTconfig;

st_g_USARTconfig =
{
	/**
	 * FCPU Selection:
	 *	1 - FCPU1M
        2 - FCPU2M
        3 - FCPU4M
        4 - FCPU8M
	 */
	.FCPU = FCPU1M,

    /**
	 * Baud Rate Options:
	 *	1 - BAUDRATE_2400
        2 - BAUDRATE_4600
        3 - BAUDRATE_9600
        4 - BAUDRATE_14400
	 */
	.BAUDRATE = BAUDRATE_9600,
	
	/* USART MODE : 
        1-USART_ASYNC_MODE
        2-USART_SYNC_MODE
    */
	.SETMODE = USART_ASYNC_MODE,
	
	/* USART PARITY OPTIONS :
       1-USART_DIS_PARITY
       2-USART_ODD_PARITY
       3-USART_EVEN_PARITY
    */
	.PARITYMODE = USART_DIS_PARITY,

    /* USART STOP BIT OPTIONS :
       1-USART_ONE_STOP_BIT
       2-USART_TWO_STOP_BITS
    */
	.STOPBIT = USART_ONE_STOP_BIT,

	/* USART Data SIZE OPTIONS :
       1-USART_DATA_SIZE_5
       2-USART_DATA_SIZE_6
       3-USART_DATA_SIZE_7
       4-USART_DATA_SIZE_8
       5-USART_DATA_SIZE_9
    */

    
	.DATASIZE = USART_DATA_SIZE_8,
	
    /* USART Speed MODE :
       1-USART_NORMAL_SPEED
       2-USART_DOUBLE_SPEED
    */
	
	.SETSPEED = USART_NORMAL_SPEED,
	
};
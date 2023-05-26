/*
 * app.c
 *
 * Created: 5/25/2023 4:02:29 PM
 *  Author: Sharpel
 */ 


#include "app.h"
// configure two leds for send complete and receieve complete
str_led_config_t gl_str_send_complete_led =
{
	.pinNumber = DIO_PIN0,
	.portNumber = DIO_PORTA
};

str_led_config_t gl_str_recieve_complete_led =
{
	.pinNumber = DIO_PIN1,
	.portNumber = DIO_PORTA
};

str_led_config_t gl_error_led =
{
	.pinNumber = DIO_PIN2,
	.portNumber = DIO_PORTA
};


enu_app_states_t gl_enu_app_state = IDLE ;
str_bcm_instance_t gl_str_bcm_instance_app = {.en_bcm_channel=CHANNEL_0};
uint8_t gl_rec_string_from_dest[]="BCM OPERATING";
uint8_t gl_send_string_to_dest []="CONFIRM BCM OPERATING";


// variable return for bcm
enu_bcm_status_t gl_enu_bcm_status_return = BCM_OKAY;
void app_init(void)
{
	
	LED_init(&gl_error_led);
	// init leds and check on their return
	
	if( (LED_init(&gl_str_send_complete_led) != LED_OK) || (LED_init(&gl_str_recieve_complete_led) != LED_OK))
	{
		gl_enu_app_state = BLOCKED;
	}
	
	
	gl_enu_bcm_status_return = bcm_init(&gl_str_bcm_instance_app);
	if((gl_enu_bcm_status_return != BCM_OKAY) && (gl_enu_app_state != BLOCKED))
	{
		gl_enu_app_state = BLOCKED;
	}
	
}

void app_start(void)
{
	switch(gl_enu_app_state)
	{
		case IDLE :
		{
			gl_enu_bcm_status_return = bcm_dispatcher(&gl_str_bcm_instance_app);
			if(gl_enu_bcm_status_return == SEND_OPERATION_DONE)
			{
				LED_toggle(&gl_str_send_complete_led);
			}
			else if(gl_enu_bcm_status_return == REC_OPERATION_DONE)
			{
				if(!strcmp(gl_rec_string_from_dest,gl_recieve_arr))
				{
					LED_toggle(&gl_str_recieve_complete_led);
					gl_enu_bcm_status_return = bcm_send_n(&gl_str_bcm_instance_app,gl_send_string_to_dest,strlen(gl_send_string_to_dest));
				}
				
			}
			
			else if(gl_enu_bcm_status_return == NULL_POINTER)
			{
				gl_enu_app_state = BLOCKED;
			}
			break;
		}
		
		case BLOCKED :
		{
			LED_toggle(&gl_error_led);
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}

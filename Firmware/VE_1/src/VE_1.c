#include "Board.h"
#include "Threads.h"
#include "watches.h"
#include "motor.h"
#include <stdio.h>
#include <stdlib.h>
char fn1(void)
{
//	debug_send_byte('G');
debug_s.data_tx[0] = 'T';
debug_s.data_tx[1] = 'U';
debug_s.data_tx[2] = 'L';
	//debug_send_data_handler(3);
	//adc_read();
	LED_RGB_TGL(COLOUR_RED);

	return 0;
}
char fn2(void)
{
	static char toggle =0;
	enum WATCH_ALARM_FLAG flag;
	LED_RGB_TGL(COLOUR_BLUE);
	watches_run();
	if(toggle== 0 )
	{
		watches_set_alarm_counter(0,22);
				toggle ++;
	}
	else 
	{
		
		if(watches_get_alarm_flag(0,&flag)==1)
		{
			if(flag == WATCH_ALARM_FINISHED)
			{
				uint32_t val = watch_alarm_s[0].counter; //just for testing
				
				
				sprintf(debug_s.data_tx ,"%0.5d" , val);
				debug_s.data_tx [5] ='\r';
				debug_s.data_tx [6] = '\n';
				debug_send_data_handler(7);
				toggle = 0;
			}
		}
	}
		
	return 0;
}
char fn3(void)
{
	LED_RGB_TGL(COLOUR_GREEN);
	
	return 0;
}

ve_1_init(void)
{
	board_init();
	watches_init();
	threads_init();
	threads_constructor(&fn1,1000,0,0);
	threads_constructor(&fn2,100,0,1);
	threads_constructor(&fn3,100000,0,2);
	motor_init();
	motor_set_duty(MOTOR_SIDE_RIGHT,90,MOTOR_DIRECTION_CC);
	//configure_pwm();
	//configure_ad();
}

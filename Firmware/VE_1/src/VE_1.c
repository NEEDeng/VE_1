#include "Board.h"
#include "Threads.h"
#include "watches.h"

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
	LED_RGB_TGL(COLOUR_BLUE);
	watches_run();
	if(toggle== 0 )
	{
		watches_set_cronos(0);
				toggle ++;
	}
	else 
	{
		toggle ++;
		if(toggle>2000)
		{
			uint32_t val;
			unsigned char valor_str[7];
			watches_set_cronos_flag(0,WATCH_CRONOS_FINISHED);
			watches_get_cronos_counter(0,&val);
			
			sprintf(debug_s.data_tx ,"%0.5d" , val);
			debug_s.data_tx [5] ='\r';
			debug_s.data_tx [6] = '\n';
			debug_send_data_handler(7);
			toggle = 0;
		}
	}
		
	return 0;
}
char fn3(void)
{
	LED_RGB_TGL(COLOUR_GREEN);
	
	return 0;
}
char motor_th(void)
{
	
}
char motor_speed(char motor1_duty, char motor1_dir)
{
	
	};
enum MOTOR_S_FLAG {MOTOR_S_RUNNING, MOTOR_S_STOPPED, MOTOR_S_WAITING, MOTOR_S_NOT_IMPLEMENTED};
struct _motor_s
{
	TC_COUNT8_CC_Type cc_reg;
	int position_abs_turn;
	int position_abs_degree;
	int position_relative_turn;
	int position_relative_degree;
	int position_last_turn;
	int position_last_degree;
	unsigned int adc_current_val;
	unsigned int adc_last_val;
	char duty;
	char flag;
	unsigned int turn_table[360];
	unsigned int turn_table_precision;	
};
void ve_1_init(void)
{
	board_init();
	watches_init();
	threads_init();
	threads_constructor(&fn1,1000,0,0);
	threads_constructor(&fn2,100,0,1);
	threads_constructor(&fn3,100000,0,2);
	
	//configure_pwm();
	//configure_ad();
}

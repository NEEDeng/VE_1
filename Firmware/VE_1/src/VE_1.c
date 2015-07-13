#include "Board.h"
#include "Threads.h"
#include "watches.h"
#include "motor.h"
#include <stdio.h>
#include <stdlib.h>
char fn1(void)
{
	watches_run();
	
	return 0;
}
int cc=0;
char fn2(void)
{
	motor_fn();
	//LED_RGB_TGL(COLOUR_BLUE);

	return 0;
}
char fn3(void)
{
	
//	LED_RGB_TGL(COLOUR_GREEN);
	
	return 0;
}

void ve_1_init(void)
{
	board_init();
	watches_init();
	threads_init();
	motor_init();
	threads_constructor(&fn1,1,0,0);
	threads_constructor(&fn2,100,0,1);
	threads_constructor(&fn3,100000,0,2);
	
	LED_RGB_CLR_ALL();
	
	//configure_pwm();
	//configure_ad();
}

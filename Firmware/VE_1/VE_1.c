#include "Board.h"
#include "Threads.h"
#include <stdio.h>
#include <stdlib.h>
char fn1(void)
{
//	debug_send_byte('G');

	LED_RGB_TGL(COLOUR_RED);

	return 0;
}
char fn2(void)
{
	LED_RGB_TGL(COLOUR_BLUE);
		
	return 0;
}
char fn3(void)
{
	LED_RGB_TGL(COLOUR_GREEN);
	
	return 0;
}
void ve_1_init(void)
{
	board_init();
	
	
	threads_init();
	threads_constructor(&fn1,1000,0,0);
	threads_constructor(&fn2,10000,0,1);
	threads_constructor(&fn3,10000,0,2);
	
	//configure_pwm();
	//configure_ad();
}

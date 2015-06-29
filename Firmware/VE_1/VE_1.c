#include "Board.h"
#include "Threads.h"

char fn1(void)
{
	LED_RGB_TGL(COLOUR_RED);
}
char fn2(void)
{
	LED_RGB_TGL(COLOUR_BLUE);
}
char fn3(void)
{
	LED_RGB_TGL(COLOUR_GREEN);
}
void ve_1_init(void)
{
	board_init();
	
	
	threads_init();
	threads_constructor(&fn1,1,0,0);
	threads_constructor(&fn2,1,0,1);
	threads_constructor(&fn3,1,0,2);
	
	//configure_pwm();
	//configure_ad();
}

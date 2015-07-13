/*
 * sensors.c
 *
 * Created: 7/12/2015 5:42:13 PM
 *  Author: Tulio
 */ 
#include "Board.h"
#include "sensors.h"
void adc_run()
{
	adc_data[0] =adc_read_handler();
}
/*
 * watches.h
 *
 * Created: 7/1/2015 9:45:52 AM
 *  Author: Tulio
 */ 


#ifndef WATCHES_H_
#define WATCHES_H_

#include "Board.h"

/**
	@var counter_current Contador contendo o valor atual do 
*/
enum CRONOS_FLAG {CRONOS_IDLE, CRONOS_COUNTING, CRONOS_PAUSED, CRONOS_FINISHED, CRONOS_RESETED};
enum CRONOS_FLAG {ALARM_IDLE, ALARM_COUNTING, ALARM_PAUSED, ALARM_FINISHED, ALARM_RESETED};
	
struct _watch_crono_s
{
	char FLAG;
	unsigned long counter;
	};


struct _watch_alarm_s
{
	char FLAG;
	unsigned long counter;
	
};


#endif /* WATCHES_H_ */
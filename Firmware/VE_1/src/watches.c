/*
 * watches.c
 *
 * Created: 7/1/2015 9:45:35 AM
 *  Author: Tulio
 */ 
#include "watches.h"
void watches_init()
{
	for(int i=0;i<WATCH_CRONOS_N;i++)
	{
		watch_crono_s[i].FLAG = WATCH_CRONOS_IDLE;
	}
	for(int i=0;i<WATCH_ALARM_N;i++)
	{
		watch_alarm_s[i].FLAG = WATCH_ALARM_IDLE;
	}
}
char watches_set_cronos(int n) 
{
	if(n<WATCH_CRONOS_N)
	{
		if(watch_crono_s[n].FLAG == WATCH_CRONOS_COUNTING)
		{
			return -1;
		}
		
		watch_crono_s[n].counter =0;
		watch_crono_s[n].FLAG = WATCH_CRONOS_COUNTING;
		return 1;
	}
	else
	{
		return -1;
	}
}
char watches_get_cronos_ms(int n, uint16_t *val)
{
	uint32_t temp_val=0;
	if(watches_get_cronos_counter(n, temp_val))
	{
		*val = temp_val/WATCH_FINAL_FREQ_KHZ;
		return 0 ;
	}
	else
	return -1;
}
char watches_get_cronos_counter(int n, uint32_t *val)
{
	if(n<WATCH_CRONOS_N)
	{
		if(watch_crono_s[n].FLAG == WATCH_CRONOS_COUNTING)
		{
			*val =0;
			return -1;
		}
	
		*val = watch_crono_s[n].counter;
		return 1;
	}
	else
	{
		*val =0;
		return -1;
	}
}
char watches_set_cronos_flag(int n, int flag)
{
	if(n<WATCH_CRONOS_N)
	{
		watch_crono_s[n].FLAG = flag;
		return 1;
	}
	else
	{
		return -1;
	}
}
char watches_set_alarm_counter(int n, uint32_t referencia)
{
	if(n<WATCH_ALARM_N)
{
	if(watch_alarm_s[n].FLAG == WATCH_ALARM_COUNTING)
	{
		return -1;
	}
	watch_alarm_s[n].referencia = referencia;
	watch_alarm_s[n].FLAG = WATCH_ALARM_RESETED;
	return 1;
}
else
	{
		return -1;
	}
}
char watches_get_alarm_flag(int n, int *flag)
{
	if(n<WATCH_CRONOS_N)
	{
		*flag = watch_alarm_s[n].FLAG ;
		return 1;
	}
	else
	{
		return -1;
	}
}
char watches_set_alarm_flag(int n, int flag)
{
	if(n<WATCH_CRONOS_N)
	{
		watch_alarm_s[n].FLAG =flag ;
		return 1;
	}
	else
	{
		return -1;
	}
}

char watches_run()
{
	for(int i=0;i<WATCH_CRONOS_N;i++)
	{
		
		if(watch_crono_s[i].FLAG == WATCH_CRONOS_COUNTING)
		{
			watch_crono_s[i].counter++;
		}
		
	}
	for(int i=0;i<WATCH_ALARM_N;i++)
	{
		
		if(watch_alarm_s[i].FLAG == WATCH_ALARM_COUNTING)
		{
			if(watch_alarm_s[i].counter == watch_alarm_s[i].referencia)
			{
				watch_alarm_s[i].FLAG == WATCH_ALARM_FINISHED;
			}
			else
			{
				watch_alarm_s[i].counter++;
			}
		}
		
	}
}
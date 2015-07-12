/*
 * watches.c
 *
 * Created: 7/1/2015 9:45:35 AM
 *  Author: Tulio
 */ 
#include "watches.h"
void watches_init(void)
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
#define THREAD_STEP_US	10
#define THREAD_STEP_MS	1000/THREAD_STEP_US
char watches_set_alarm_ms(int n, uint32_t ms)
{
	uint32_t referencia =  ms*THREAD_STEP_MS;
	return watches_set_alarm(n,referencia);
}
char watches_set_alarm_10us(int n, uint32_t us_10)
{
	uint32_t referencia =  us_10;
	return watches_set_alarm(n,referencia);
}
char watches_set_alarm_hz(int n, float hz)
{
	uint32_t referencia =  (uint32_t)(100000/hz);
	return watches_set_alarm(n,referencia);
}
char watches_set_alarm(int n, uint32_t referencia)
{
	if(n<WATCH_ALARM_N)
{
	if(watch_alarm_s[n].FLAG == WATCH_ALARM_COUNTING)
	{
		return -1;
	}
	watch_alarm_s[n].referencia = referencia;
	watch_alarm_s[n].FLAG = WATCH_ALARM_COUNTING;
	watch_alarm_s[n].counter = 0;
	return 1;
}
else
	{
		return -1;
	}
}
char watches_get_alarm_flag(int n, enum WATCH_ALARM_FLAG *flag)
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
char wathces_is_alarm_finished(int n)
{
	/*enum WATCH_ALARM_FLAG flag;
	if(watches_get_alarm_flag(n,&flag)<0)
	{
		return -1;
	}
	if(flag == WATCH_ALARM_FINISHED)
	{
		return 1;
	}
	else
	{
		return 0;
	}*/
	if(watch_alarm_s[0].FLAG == WATCH_ALARM_FINISHED)
	{
		watches_set_alarm_flag(0, WATCH_ALARM_IDLE);
		return 1;
	}
	else
	{
		return 0;
	}
}
char watches_set_alarm_flag(int n,  enum WATCH_ALARM_FLAG flag)
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

char watches_run(void)
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
				watch_alarm_s[i].FLAG = WATCH_ALARM_FINISHED;
				
			}
			else
			{
				watch_alarm_s[i].counter++;
			}
		}
		
	}
}
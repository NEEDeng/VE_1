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
typedef enum WATCH_CRONOS_FLAG {WATCH_CRONOS_IDLE, WATCH_CRONOS_COUNTING, WATCH_CRONOS_PAUSED, WATCH_CRONOS_FINISHED, WATCH_CRONOS_RESETED};
typedef enum WATCH_ALARM_FLAG {WATCH_ALARM_IDLE, WATCH_ALARM_COUNTING, WATCH_ALARM_PAUSED, WATCH_ALARM_FINISHED, WATCH_ALARM_RESETED};
#define WATCH_CRONOS_N	3	
#define WATCH_ALARM_N	3
#define WATCH_CLOCK_SRC_FREQ	100000
#define WATCH_THREAD_PRESCALER	10
#define WATCH_FINAL_FREQ_HZ		WATCH_CLOCK_SRC_FREQ/WATCH_THREAD_PRESCALER
#define WATCH_FINAL_FREQ_KHZ	WATCH_CLOCK_SRC_FREQ/(WATCH_THREAD_PRESCALER *1000)
/**
*	Struct contendo informacoes necessarias para gestao do cronometro.
*/
struct _watch_crono_s
{
	char FLAG; /**< Representa estado do cronometro */
	uint32_t counter; /**< Valor incremental e instantaneo do cronometro.*/
	}watch_crono_s[WATCH_CRONOS_N];

/**
*	Struct contendo informacoes necessarias para gestao do alarme 
*/
struct _watch_alarm_s
{
	char FLAG;/**< Representa estado do alarme */
	uint32_t counter;/**< Valor incremental e instantaneo do alarme.*/
	//unsigned long nova_referencia;	/**< Valor incremental e instantaneo do alarme.*/
	uint32_t referencia;	/**< Valor de comparacao do alarme.*/
}watch_alarm_s[WATCH_ALARM_N];

void watches_init();
char watches_set_cronos(int n);
char watches_get_cronos_counter(int n, uint32_t *val);
char watches_get_cronos_ms(int n, uint16_t *val);
char watches_set_cronos_flag(int n, int flag);
char watches_set_alarm_counter(int n, uint32_t referencia);
char watches_get_alarm_flag(int n, int *flag);
char watches_set_alarm_flag(int n, int flag);
char watches_run();

#endif /* WATCHES_H_ */
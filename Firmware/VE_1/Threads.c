/**
*	\file		Threads.c
*	\author		TPO
*	\date		16/06/2015
*	\brief		Arquivo responsavel pela criacao de threads.
*	\details	Este arquivo contem a logica de funcionaento das threads
*	\copyright 	GNU V2.0
*/
#include "Threads.h"
extern struct thread_s list_thread_s[THREADS_MAX_N]; 

#define THREAD0_INDEX		0
#define THREAD0_PRIORITY	0
#define THREAD0_MS			1000
#define THREAD1_INDEX		1
#define THREAD1_PRIORITY	0
#define THREAD1_MS			1000
#define THREAD2_INDEX		2
#define THREAD2_PRIORITY	0
#define THREAD2_MS			1000
#define THREAD3_INDEX		3
#define THREAD3_PRIORITY	0
#define THREAD3_MS			1000

void threads_init()
{
	for(int i=0;i<THREADS_MAX_N;i++)
	{
		list_thread_s[i].STATUS =	THREAD_STATUS_N_IMPLEMENTED;
	}
}


void threads_constructor(char (*p2f)(void),unsigned int ms, char prioridade, int index)
{
	list_thread_s[index].STATUS =	THREAD_STATUS_IDLE;
	list_thread_s[index].p2f = p2f;
	list_thread_s[index].count = 0;
	list_thread_s[index].count_max = ms;
	list_thread_s[index].index = index;
	list_thread_s[index].prioridade = prioridade;		
}

void threads_increment(void)
{
	for(int i=0;i<THREADS_MAX_N;i++)
	{
		if(list_thread_s[i].STATUS == THREAD_STATUS_RUNNING)
		{
			
				list_thread_s[i].count++;
			
		}
		else if(list_thread_s[i].STATUS == THREAD_STATUS_IDLE)
		{
			list_thread_s[i].STATUS = THREAD_STATUS_RUNNING;
			list_thread_s[i].count = 0;
		}
	}
}
void threads_run(void)
{
	for(int i=0;i<THREADS_MAX_N;i++)
	{
		if(list_thread_s[i].STATUS == THREAD_STATUS_RUNNING)
		{
			if(list_thread_s[i].count >= list_thread_s[i].count_max)
			{
			list_thread_s[i].count = 0;
			(*list_thread_s[i].p2f)();
			}
		
		}
		
	}
}
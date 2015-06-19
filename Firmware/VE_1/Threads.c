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

void thread_init()
{
	for(int i=0;i<THREADS_MAX_N;i++)
	{
		list_thread_s[i].STATUS =	THREAD_STATUS_N_IMPLEMENTED;
	}
}


void thread_constructor(char (*p2f)(void),int ms, char prioridade, int index)
{
	list_thread_s[index].STATUS =	THREAD_STATUS_IDLE;
	list_thread_s[index].p2f = p2f;
	list_thread_s[index].count = 0;
	list_thread_s[index].count_max = ms;
	list_thread_s[index].index = index;
	list_thread_s[index].prioridade = prioridade;	
}

void thread_run(void)
{
	for(int i=0;i<THREADS_MAX_N;i++)
	{
		if(list_thread_s[i].STATUS == THREAD_STATUS_RUNNING)
		{
			if(list_thread_s[i].count < list_thread_s[i].count_max)
			{
				list_thread_s[i].count++;
			}
			else
			{
				list_thread_s[i].count = 0;
				(*list_thread_s[i].p2f)();
			}
		}
		else if(list_thread_s[i].STATUS == THREAD_STATUS_IDLE)
		{
			list_thread_s[i].STATUS = THREAD_STATUS_RUNNING;
			list_thread_s[i].count = 0;
		}
	}
}
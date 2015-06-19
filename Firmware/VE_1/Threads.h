/**
*	\file		Threads.h
*	\author		TPO
*	\date		16/06/2015
*	\brief		Arquivo responsavel pela criacao de threads.
*	\details	Este arquivo contem a logica de funcionaento das threads
*	\copyright 	GNU V2.0
*/

#ifndef THREADS_H_
#define THREADS_H_
#define THREADS_MAX_N		4
/** Tempo minimo de um milisegundo para a thread. */
#define THREAD_TEMPO_MIN	1	
//char (*p2f[THREADS_MAX_N]) (void); /**< Array of pointers to function with void param and return char. */
//char (**pp2f)(void); /**< Array of pointers to function with void param and return char. */
enum THREAD_STATUS_e  {THREAD_STATUS_IDLE, THREAD_STATUS_RUNNING, THREAD_STATUS_STOPPED, THREAD_STATUS_END, THREAD_STATUS_ABORTED, THREAD_STATUS_N_IMPLEMENTED };
struct thread_s
{
	int		count;		/**< Valor atual da contagem da thread. */
	int		count_max;	/**< Valor maximo do contador da thread. */
	enum THREAD_STATUS_e	STATUS;		/**< Estado da thread. */
	char	prioridade;	/**< Prioridade da thread */
	int		index;		/**< Index da thread. */
	char	(*p2f)(void); /**< Ponteiro para funcao correpondente*/		
}stThread;

void thread_init(void);
void thread_run(void);
void thread_constructor(char (*p2f)(void),int ms, char prioridade, int index);


#endif /* THREADS_H_ */
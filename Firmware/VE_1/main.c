/*
 * main.c
 *
 * Created: 6/26/2015 7:45:48 PM
 *  Author: Tulio
 */ 
/**
*	\file		VE_1.c
*	\author		TPO
*	\date		16/06/2015
*	\brief		Arquivo principal.
*	\details	Este arquivo contem a logica de funcionaento do programa principal.
*	\copyright 	GNU V2.0
*/

#include "samd20g17.h"
#include "Threads.h"
#include "Board.h"
struct thread_s list_thread_s[THREADS_MAX_N]; /**<Array contendo todas as threads do sistema.*/

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */

int main(void)
{
    /* Initialize the SAM system */
	ve_1_init();
		LED_RGB_SET(COLOUR_BLUE);
    while (1) 
    {
		LED_RGB_SET(COLOUR_RED);
		LED_RGB_CLR(COLOUR_RED);
        //TODO:: Please write your application code 
    }
}

void TC0_Handler(void)
{
	threads_run();
/*	if(Count>20)
	{
		
		
		if(side==0)
		{
			PORT->Group[0].OUTCLR.reg = PIN1_MOTOR | PIN3_MOTOR;
			PORT->Group[0].OUTSET.reg = PIN4_MOTOR | PIN2_MOTOR;
			PORT->Group[0].OUTSET.reg = PORT_PA12;
			PORT->Group[0].OUTCLR.reg = PORT_PA13;
			side =1;
		}
		else
		{
			PORT->Group[0].OUTSET.reg = PIN1_MOTOR | PIN3_MOTOR;
			PORT->Group[0].OUTCLR.reg = PIN4_MOTOR | PIN2_MOTOR;
			PORT->Group[0].OUTSET.reg = PORT_PA13;
			PORT->Group[0].OUTCLR.reg = PORT_PA12;
			side =0;
		}
		Count=0;
	}
	else
	Count++;
*/
	THREAD_INTERRUPT_CLEAR();
	
}

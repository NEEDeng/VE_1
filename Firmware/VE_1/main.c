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
#include "VE_1.h"
#define true 1
#define false !true
struct thread_s list_thread_s[THREADS_MAX_N]; /**<Array contendo todas as threads do sistema.*/

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
volatile char TC0_FLAG = false;
volatile char SERCOM5_FLAG = false;
int main(void)
{
    /* Initialize the SAM system */
	ve_1_init();
		LED_RGB_SET(COLOUR_BLUE);
		volatile int ii=0;
		
    while (1) 
    {
		
		if(TC0_FLAG== true)
		{
			threads_increment();
			threads_run();
			TC0_FLAG = false;
		}
		if(SERCOM5_FLAG == true)
		{
			debug_send_byte_hand();
			SERCOM5_FLAG = false;
		}
	
    }
}

void TC0_Handler(void)
{
	TC0_FLAG = true;
	TC0->COUNT16.INTFLAG.reg = TC_INTFLAG_OVF;
}

void SERCOM5_Handler()
{
	SERCOM5_FLAG = true;
	SERCOM5->USART.INTFLAG.reg = SERCOM_USART_INTFLAG_TXC | SERCOM_USART_INTFLAG_DRE;
}

void ADC_Handler()
{
	
}
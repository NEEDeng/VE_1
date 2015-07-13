/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

#include "Threads.h"
#include "Board.h"
#include "VE_1.h"
#include "sensors.h"
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
volatile char ADC_FLAG = false;
int main(void)
{
    /* Initialize the SAM system */
	system_init();
	ve_1_init();
	//	LED_RGB_SET(COLOUR_BLUE);
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
		if(ADC_FLAG)
		{
			adc_run();
			ADC_FLAG = false;
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
	ADC_FLAG = true;
	adc_run();
	ADC->INTENSET.reg = ADC_INTENSET_RESRDY;
	
}
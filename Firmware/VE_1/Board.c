/**
*	\file		Board.c
*	\author		TPO
*	\date		16/06/2015
*	\brief		Arquivo contendo informacoes sobre a VE_1.
*	\details	Este arquivo contem todas a rotinas de  baixo nivel para acesar a placa EV_1.
*	\copyright 	GNU V2.0
*/
#include <stddef.h>
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "samd20g17.h"
//#include "config.h"
#include <_syslist.h>

int Count=20;
char side=0;

/**
* @brief	Inicializa o timer 0.
* @details	Essa funcao inicializa o timer 0 com XXhz e habilita a interrpucao.
* @return	none
*/
void thread_init(void)
{
	PM->APBCMASK.reg			|=	PM_APBCMASK_TC0; //enable clock to timer 0
	
	GCLK->CLKCTRL.reg		=	GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_TC0_TC1 | GCLK_CLKCTRL_GEN_GCLK2;
	while(GCLK->STATUS.bit.SYNCBUSY){}
	
	
	THREAD_COUNT_CONF.CC[0].reg		=	THREAD_TOP_VAL;
	while(THREAD_COUNT_CONF.STATUS.bit.SYNCBUSY){}
	THREAD_COUNT_CONF.EVCTRL.reg		|=	TC_EVCTRL_OVFEO;
	
	
	
	THREAD_COUNT_CONF.INTENSET.reg	|=	TC_INTENSET_OVF; //enable overflow interrupt
	TC0->COUNT16.INTFLAG.reg = 0xFF;
	NVIC_EnableIRQ(TC0_IRQn);
	
	THREAD_COUNT_CONF.CTRLA.reg	=	TC_CTRLA_ENABLE | TC_CTRLA_WAVEGEN_MFRQ   | TC_CTRLA_RUNSTDBY ;//| TC_CTRLA_PRESCALER_DIV2; //enable timmer
	while(THREAD_COUNT_CONF.STATUS.bit.SYNCBUSY){}
		NVIC_EnableIRQ(TC0_IRQn);
}

void led_init(void)
{
	LED_RGB_PORT_CONF.DIRSET.reg		= LED_RGB_RED_PORT | LED_RGB_BLUE_PORT | LED_RGB_GREEN_PORT;
	LED_RGB_CLR_ALL();
}

void motor_init(void)
{
	
	GCLK->CLKCTRL.reg			=	GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_TC2_TC3 | GCLK_CLKCTRL_GEN_GCLK2;
	while(GCLK->STATUS.bit.SYNCBUSY){}
	PM->APBCMASK.reg			|=	PM_APBCMASK_TC2 | PM_APBCMASK_TC3;
	while(TC2->COUNT8.STATUS.bit.SYNCBUSY);
	PWM_MOTOR1_PORT_CONF.DIRSET.reg = PWM_MOTOR1_A_PORT | PWM_MOTOR1_B_PORT ;
	PWM_MOTOR1_PORT_CONF.OUTCLR.reg = PWM_MOTOR1_A_PORT | PWM_MOTOR1_B_PORT ;
	
		PWM_MOTOR1_PORT_CONF.PMUX[8].reg |= PWM_MOTOR1_A_PMUX;
	PWM_MOTOR1_PORT_CONF.PMUX[8].reg |= PWM_MOTOR1_B_PMUX;
	
	PWM_MOTOR1_PORT_CONF.PINCFG[PWM_MOTOR1_A_PORT_N].reg |= PORT_PINCFG_PMUXEN | PORT_PINCFG_PULLEN;
	PWM_MOTOR1_PORT_CONF.PINCFG[PWM_MOTOR1_B_PORT_N].reg |= PORT_PINCFG_PMUXEN | PORT_PINCFG_PULLEN;
	
	PWM_MOTOR1_TC_CONF.CTRLA.reg |= TC_CTRLA_WAVEGEN_NPWM | TC_CTRLA_MODE_COUNT8 ;
	PWM_MOTOR1_TC_CONF.PER.reg	=	0xFF;
	PWM_MOTOR1_TC_A_DUTY.reg	=	0x00;
	PWM_MOTOR1_TC_B_DUTY.reg	=	0x00;
		
	PWM_MOTOR1_TC_CONF.CTRLA.reg |= TC_CTRLA_ENABLE;
	while(TC2->COUNT8.STATUS.bit.SYNCBUSY);	
	////MOTOR 2
	PWM_MOTOR2_PORT_CONF.DIRSET.reg = PWM_MOTOR2_A_PORT | PWM_MOTOR2_B_PORT ;
	PWM_MOTOR2_PORT_CONF.OUTCLR.reg = PWM_MOTOR2_A_PORT | PWM_MOTOR2_B_PORT ;
	
	//PWM_MOTOR2_PORT_CONF.OUTSET.reg = PWM_MOTOR2_A_PORT ;
		
		
	PWM_MOTOR2_PORT_CONF.PMUX[9].reg |= PWM_MOTOR2_A_PMUX;
	PWM_MOTOR2_PORT_CONF.PMUX[9].reg |= PWM_MOTOR2_B_PMUX;
		
	PWM_MOTOR2_PORT_CONF.PINCFG[PWM_MOTOR2_A_PORT_N].reg |= PORT_PINCFG_PMUXEN | PORT_PINCFG_PULLEN;
	PWM_MOTOR2_PORT_CONF.PINCFG[PWM_MOTOR2_B_PORT_N].reg |= PORT_PINCFG_PMUXEN | PORT_PINCFG_PULLEN;
		
	PWM_MOTOR2_TC_CONF.CTRLA.reg |= TC_CTRLA_WAVEGEN_NPWM | TC_CTRLA_MODE_COUNT8 ;
	PWM_MOTOR2_TC_CONF.PER.reg = 0xFF;

	PWM_MOTOR2_TC_A_DUTY.reg = 0x00;
	PWM_MOTOR2_TC_B_DUTY.reg = 0x9A;
		
	PWM_MOTOR2_TC_CONF.CTRLA.reg |= TC_CTRLA_ENABLE;
}



char debug_send_byte( char data)
{
	if((SERCOM5->USART.INTFLAG.bit.DRE))
	{
		SERCOM5->USART.INTFLAG.bit.DRE = true;
		SERCOM5->USART.DATA.reg =  data;
		
		
	return 0;	
	}
	return -1;
}
	char debug_send_byte_hand()
	{
		if(debug_s.flag ==  DEBUG_S_SENDING)
		{
			if(debug_s.size_sended >= debug_s.size_to_send)
			{
				debug_s.flag =  DEBUG_S_IDLE;
			}
			else
			{
				SERCOM5->USART.DATA.reg = debug_s.data_tx[debug_s.size_sended];
				debug_s.size_sended++;
			}
		}
	
	return 0;
	}

char debug_send_data_handler(int size)

{
	if(debug_s.flag == DEBUG_S_IDLE)
	{
		debug_s.size_to_send = size;
		debug_s.size_sended = 0;
		debug_s.flag = DEBUG_S_SENDING;
		debug_send_byte_hand();
	}
	return 0;
}


char debug_send_data(char *data,  int size)
{
	for(int i = 0;i<size;i++)
	{
		debug_send_byte(*data);
	}
	return 0;
}
#define DEBUG_CLK_FREQUENCY	8000000
#define DEBUG_PRESCALER		1
#define DEBUG_FREQUENCY		38400
#define DEBUG_TOP_VAL		(65536*(1-16*((float)DEBUG_FREQUENCY/(float)DEBUG_CLK_FREQUENCY)))

void  debug_init()
{
	
	while(SERCOM5->USART.STATUS.bit.SYNCBUSY);
	GCLK->CLKCTRL.reg	=	GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_SERCOM5_CORE  | GCLK_CLKCTRL_GEN_GCLK2; //set
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM5; //Habilita alimentacao
	while(SERCOM5->USART.STATUS.reg & SERCOM_USART_STATUS_SYNCBUSY);
	
	PORT->Group[1].DIRSET.reg = PORT_PB22; // configura pino como saida
	PORT->Group[1].PMUX[11].reg |= PORT_PMUX_PMUXE_D; // seta multiplexador do pino PB22 como sendo D
	PORT->Group[1].PINCFG[22].reg = PORT_PINCFG_PMUXEN | PORT_PINCFG_PULLEN;
	
	SERCOM5->USART.CTRLA.reg |= SERCOM_USART_CTRLA_TXPO_PAD2 |  SERCOM_USART_CTRLA_DORD |  SERCOM_USART_CTRLA_MODE_USART_INT_CLK;//bug in mode(1) = assynchronous
	while(SERCOM5->USART.STATUS.reg & SERCOM_USART_STATUS_SYNCBUSY);
	SERCOM5->USART.CTRLB.reg |= SERCOM_USART_CTRLB_TXEN ;
while(SERCOM5->USART.STATUS.reg & SERCOM_USART_STATUS_SYNCBUSY);
SERCOM5->USART.INTENSET.reg = SERCOM_USART_INTENSET_TXC ;// | SERCOM_USART_INTENSET_DRE;
	
	SERCOM5->USART.BAUD.reg = DEBUG_TOP_VAL;
while(SERCOM5->USART.STATUS.reg & SERCOM_USART_STATUS_SYNCBUSY);
	SERCOM5->USART.CTRLA.reg = SERCOM5->USART.CTRLA.reg  |  SERCOM_USART_CTRLA_ENABLE ;
	while(SERCOM5->USART.STATUS.reg & SERCOM_USART_STATUS_SYNCBUSY);
	debug_s.flag = DEBUG_S_IDLE;
	SERCOM5->USART.INTFLAG.reg = SERCOM_USART_INTFLAG_DRE | SERCOM_USART_INTFLAG_TXC | SERCOM_USART_INTFLAG_RXC;
	while(SERCOM5->USART.STATUS.reg & SERCOM_USART_STATUS_SYNCBUSY);
	NVIC_EnableIRQ(SERCOM5_IRQn);
	


}

void adc_init(void)
{PORT->Group[0].DIRSET.reg = PORT_PA12;
	//volatile int i=0,k=0;
//	configure_usart();

	unsigned char valor_str[7];
	
	unsigned int valor_int=0;
	
	


	GCLK->CLKCTRL.reg |= GCLK_CLKCTRL_ID_ADC | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0;
	while(GCLK->STATUS.bit.SYNCBUSY);
	PM->APBCMASK.reg |= PM_APBCMASK_ADC ;
	
	ADC->CTRLA.reg |= ADC_CTRLA_RESETVALUE;
	while(ADC->STATUS.bit.SYNCBUSY){}
	
	ADC_MOTOR2_PORT_CONF.DIRCLR.reg = ADC_MOTOR2_PORT;
	ADC_MOTOR2_PORT_CONF.PMUX[5].reg |= ADC_MOTOR2_PMUX;
	ADC_MOTOR2_PORT_CONF.PINCFG[ADC_MOTOR2_PORT_N].reg |= PORT_PINCFG_PMUXEN;// | PORT_PINCFG_PULLEN;

	

	//ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_64 | (4<<ADC_AVGCTRL_ADJRES_Pos);
	ADC->REFCTRL.reg |= ADC_REFCTRL_REFSEL_INTVCC1;
	//ADC->SAMPCTRL.reg = ADC_SAMPCTRL_SAMPLEN(0xFF);
	ADC->INPUTCTRL.reg |= ADC_INPUTCTRL_MUXPOS_PIN18 | ADC_INPUTCTRL_MUXNEG_GND | ADC_INPUTCTRL_GAIN_DIV2;
	while(ADC->STATUS.bit.SYNCBUSY){}
	ADC->CTRLB.reg |=  ADC_CTRLB_PRESCALER_DIV256;//| ADC_CTRLB_RESSEL_16BIT;ADC_CTRLB_FREERUN
	while(ADC->STATUS.bit.SYNCBUSY){}
	ADC->CTRLA.reg |= ADC_CTRLA_ENABLE;
	while(ADC->STATUS.bit.SYNCBUSY){}
	ADC->SWTRIG.bit.START = true;

}


void adc_read(void)
{
	static unsigned char valor_str[7];
	static unsigned int valor_int=0;
	
	ADC->SWTRIG.bit.START = true;
	while(!ADC->INTFLAG.bit.RESRDY){}
	
	valor_int = 20;
	
	//sprintf(valor_str ,"%0.5d" , valor_int);
	//itoa(valor_int,valor_str,10);
	valor_str[5] ='\r';
	valor_str[6] = '\n';
	for(int i=0;i<7;i++)
	{
		debug_s.data_tx[i] = valor_str[i];
	}
	ADC->INTFLAG.reg = ADC_INTFLAG_RESRDY;
	debug_send_data_handler(7);
}

void clock_init()
{
		WDT->CTRL.reg	&=	(1<<WDT_CTRL_ENABLE); //disable watchdog
		volatile unsigned int i=0;
		GCLK->GENCTRL.reg = GCLK_GENCTRL_ID_GCLK0 | GCLK_GENCTRL_SRC_OSC8M | GCLK_GENCTRL_RUNSTDBY | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_OE | GCLK_GENCTRL_IDC  ;
		while(GCLK->STATUS.bit.SYNCBUSY){}
		
		//Habilita cristal externo
		SYSCTRL->XOSC.reg = SYSCTRL_XOSC_AMPGC | SYSCTRL_XOSC_GAIN(3) | SYSCTRL_XOSC_XTALEN | SYSCTRL_XOSC_RUNSTDBY | SYSCTRL_XOSC_ENABLE  | SYSCTRL_XOSC_STARTUP(3);
		while(!SYSCTRL->PCLKSR.bit.XOSCRDY){}
		//Configura GLCK0 com cristal externo de 16Mhz
		GCLK->GENDIV.reg = GCLK_GENDIV_DIV(0) | GCLK_GENDIV_ID_GCLK0;
		GCLK->GENCTRL.reg = GCLK_GENCTRL_ID_GCLK0 | GCLK_GENCTRL_SRC_XOSC | GCLK_GENCTRL_RUNSTDBY | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_OE | GCLK_GENCTRL_IDC  ;
		while(GCLK->STATUS.bit.SYNCBUSY){}
		
		
		//Configura GLCK2 com cristal interno de 8Mhz
		//enable 8mhz operation
		SYSCTRL->OSC8M.reg &=  ~(SYSCTRL_OSC8M_ENABLE | SYSCTRL_OSC8M_PRESC_Msk);
		SYSCTRL->OSC8M.reg = SYSCTRL->OSC8M.reg | SYSCTRL_OSC8M_PRESC(0) | SYSCTRL_OSC8M_ENABLE | SYSCTRL_OSC8M_RUNSTDBY | SYSCTRL_OSC8M_ONDEMAND | SYSCTRL_OSC8M_FRANGE(2);
		GCLK->GENCTRL.reg = GCLK_GENCTRL_ID_GCLK2 | GCLK_GENCTRL_SRC_OSC8M | GCLK_GENCTRL_RUNSTDBY | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_OE | GCLK_GENCTRL_IDC  ;
		while(GCLK->STATUS.bit.SYNCBUSY){}
		
		
		GCLK->GENCTRL.reg = GCLK_GENCTRL_ID_GCLK1 | GCLK_GENCTRL_SRC_XOSC | GCLK_GENCTRL_RUNSTDBY | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_OE | GCLK_GENCTRL_IDC  ;
		while(GCLK->STATUS.bit.SYNCBUSY){}
		//Configura GLCK0 com DFFL48
		SYSCTRL->DFLLCTRL.reg &=  ~SYSCTRL_DFLLCTRL_ONDEMAND; //diable ondemand
		//	while(!SYSCTRL->PCLKSR.bit.DFLLRDY){}
		SYSCTRL->INTFLAG.reg =  SYSCTRL_INTFLAG_BOD33RDY | SYSCTRL_INTFLAG_BOD33DET |SYSCTRL_INTFLAG_DFLLRDY;
		
		//Configura o clock base do DFLL48 como sendo GLCK1
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK1 | GCLK_CLKCTRL_ID_DFLL48M ; //para o ID dado utiliza o CLCK de GCLK1
		while(GCLK->STATUS.bit.SYNCBUSY){}
		//ERRATA
		SYSCTRL->DFLLCTRL.reg = SYSCTRL_DFLLCTRL_ENABLE;
		while(!SYSCTRL->PCLKSR.bit.DFLLRDY){}
		SYSCTRL->DFLLMUL.reg = SYSCTRL_DFLLMUL_MUL(3) | SYSCTRL_DFLLMUL_CSTEP(10) | SYSCTRL_DFLLMUL_FSTEP(1);
		SYSCTRL->DFLLVAL.reg = SYSCTRL_DFLLVAL_COARSE(10) | SYSCTRL_DFLLVAL_FINE(1);
		// END OF ERRATA
		
		//habilita o glck3 com o clock do DFLL48
		GCLK->GENCTRL.reg = GCLK_GENCTRL_ID_GCLK3 | GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_RUNSTDBY | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_OE | GCLK_GENCTRL_IDC ; //seta o GCLk com o source desejado
		while(GCLK->STATUS.bit.SYNCBUSY){}
		//Reconfigura o DFLL48 para modo close-loop
		SYSCTRL->DFLLCTRL.reg = SYSCTRL_DFLLCTRL_MODE | SYSCTRL_DFLLCTRL_STABLE |  SYSCTRL_DFLLCTRL_RUNSTDBY | SYSCTRL_DFLLCTRL_ONDEMAND | SYSCTRL_DFLLCTRL_ENABLE;
		while(!SYSCTRL->PCLKSR.bit.DFLLRDY){}

	for(i=0;i<1000;i++)
	{
		
	}
	
			NVMCTRL->CTRLB.bit.RWS = 3;

		//adc_init();
		//Configura o glck0 com o clock do DFLL48
		GCLK->GENCTRL.reg = GCLK_GENCTRL_ID_GCLK0 | GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_RUNSTDBY | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_IDC ;
		while(GCLK->STATUS.bit.SYNCBUSY){}
		//desabilita GCLK3
		GCLK->GENCTRL.reg = GCLK_GENCTRL_ID_GCLK3;
		//while(GCLK->STATUS.bit.SYNCBUSY){}
}
void board_init()
{
	SystemInit();
		
	clock_init();
	
	debug_init();
	motor_init();
	led_init();
	
	thread_init();
	
	adc_init();
	
}

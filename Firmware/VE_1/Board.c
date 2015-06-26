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
#include "samd20g17.h"
#include "stdbool.h"
int Count=20;
char side=0;
/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
/**
* @brief	Inicializa o timer 0.
* @details	Essa funcao inicializa o timer 0 com XXhz e habilita a interrpucao.
* @return	none
*/
#define THREAD_CLK_FREQUENCY	8000000 
#define THREAD_PRESCALER		1
#define THREAD_FREQUENCY		1000
#define THREAD_TOP_VAL			(THREAD_CLK_FREQUENCY/(THREAD_PRESCALER*THREAD_FREQUENCY)+1)
void timer0Init(void)
{
	GCLK->CLKCTRL.reg			|=	GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_TC0_TC1;
	PM->APBCMASK.reg			|=	PM_APBCMASK_TC0; //enable clock to timer 0
	TC0->COUNT16.EVCTRL.reg		|=	TC_EVCTRL_OVFEO;
	TC0->COUNT16.CC[0].reg		=	THREAD_TOP_VAL;
	
	TC0->COUNT16.INTENSET.reg	=	TC_INTENSET_OVF; //enable overflow interrupt
	TC0->COUNT16.CTRLA.reg		|=	TC_CTRLA_ENABLE | TC_CTRLA_WAVEGEN_MFRQ ;//| TC_CTRLA_PRESCALER_DIV2; //enable timmer
}


void ledInit(void)
{
	LED_RGB_PORT_CONF.DIRSET.reg		= LED_RGB_RED_PORT | LED_RGB_BLUE_PORT | LED_RGB_GREEN_PORT;
	LED_RGB_CLR_ALL();
}
void motorInit(void)
{
	PM->APBCMASK.reg			=	PM_APBCMASK_TC2 | PM_APBCMASK_TC3;
	GCLK->CLKCTRL.reg			=	GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_TC2_TC3 ;

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
char usart5SendByte(unsigned char data)
{
	SERCOM5->USART.DATA.reg =  data;
	while(!(SERCOM5->USART.INTFLAG.bit.TXC))
	{	}
	SERCOM5->USART.INTFLAG.bit.TXC = true;
	return 0;
}
char usart5SendData(unsigned char *data, unsigned int size)
{
	for(int i = 0;i<size;i++)
	{
		usartSendByte(*data);
	}
}

void usart5Init()
{
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM5; //Habilita alimentacao
	while(SERCOM5->USART.STATUS.bit.SYNCBUSY);
	GCLK->CLKCTRL.reg	=	GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_SERCOM5_CORE ; //set
	while(GCLK->STATUS.bit.SYNCBUSY);
	PORT->Group[1].DIRSET.reg = PORT_PB22; // configura pino como saida
	PORT->Group[1].PMUX[11].reg |= PORT_PMUX_PMUXE_D; // seta multiplexador do pino PB22 como sendo D
	PORT->Group[1].PINCFG[22].reg = PORT_PINCFG_PMUXEN | PORT_PINCFG_PULLEN;

	SERCOM5->USART.CTRLA.reg |= SERCOM_USART_CTRLA_TXPO_PAD2 | SERCOM_USART_CTRLA_MODE(1)| SERCOM_USART_CTRLA_DORD;//| SERCOM_USART_CTRLA_MODE;
	SERCOM5->USART.CTRLB.reg |= SERCOM_USART_CTRLB_TXEN;

	SERCOM5->USART.BAUD.reg = 60502;

	SERCOM5->USART.CTRLA.reg |=   SERCOM_USART_CTRLA_ENABLE ;
	while(SERCOM5->USART.STATUS.bit.SYNCBUSY);
}


void adcInit(void)
{
	PORT->Group[0].DIRSET.reg = PORT_PA12;
	//volatile int i=0,k=0;
	
	unsigned char valor_str[7];
	
	unsigned int valor_int=0;
	
	PM->APBCMASK.reg |= PM_APBCMASK_ADC ;
	PM->APBCMASK.reg |= PM_APBCMASK_ADC ;

	GCLK->CLKCTRL.reg |= GCLK_CLKCTRL_ID_ADC | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0;
	while(GCLK->STATUS.bit.SYNCBUSY);
	
	ADC->CTRLA.reg |= ADC_CTRLA_RESETVALUE;
	while(ADC->STATUS.bit.SYNCBUSY){}
	
	ADC_MOTOR2_PORT_CONF.DIRCLR.reg = ADC_MOTOR2_PORT;
	ADC_MOTOR2_PORT_CONF.PMUX[5].reg |= ADC_MOTOR2_PMUX;
	ADC_MOTOR2_PORT_CONF.PINCFG[ADC_MOTOR2_PORT_N].reg |= PORT_PINCFG_PMUXEN;// | PORT_PINCFG_PULLEN;

	

	ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_64 | (4<<ADC_AVGCTRL_ADJRES_Pos);
	ADC->REFCTRL.reg |= ADC_REFCTRL_REFSEL_INTVCC1;
	//ADC->SAMPCTRL.reg = ADC_SAMPCTRL_SAMPLEN(0xFF);
	ADC->INPUTCTRL.reg |= ADC_INPUTCTRL_MUXPOS_PIN18 | ADC_INPUTCTRL_MUXNEG_GND | ADC_INPUTCTRL_GAIN_DIV2;
	while(ADC->STATUS.bit.SYNCBUSY){}
	ADC->CTRLB.reg |= ADC_CTRLB_FREERUN | ADC_CTRLB_PRESCALER_DIV256 | ADC_CTRLB_RESSEL_16BIT;
	while(ADC->STATUS.bit.SYNCBUSY){}
	ADC->CTRLA.reg |= ADC_CTRLA_ENABLE;
	while(ADC->STATUS.bit.SYNCBUSY){}
	ADC->SWTRIG.bit.START = true;
	int count=0,txCount;
	volatile unsigned int ii=0;
	while(true)
	{
		if(ADC->INTFLAG.bit.RESRDY)
		{
			while(ADC->STATUS.bit.SYNCBUSY){}
			
			valor_int = ADC->RESULT.reg;
					
			sprintf(valor_str ,"%0.5d" , valor_int);
			//itoa(valor_int,valor_str,10);
			valor_str[5] ='\r';
			valor_str[6] = '\n';
			for(txCount=0;txCount<7;txCount++)
			{
			
			}
			for(ii=0;ii<10000;ii++)
			{
				
				
			}
			ADC->INTFLAG.reg = ADC_INTFLAG_RESRDY;
			//	ADC->SWTRIG.bit.START = true;
			while(ADC->STATUS.bit.SYNCBUSY){}
			if(count>10000)
			{
				PORT->Group[0].OUTCLR.reg = PORT_PA12 ;
				count =0;
			}
			else
			{
				count++;
				PORT->Group[0].OUTSET.reg = PORT_PA12 ;
			}
			
		}
	}
}
void readADC(unsigned int number)
{
	
}
void boardInit()
{
	SystemInit();
	//enable 8mhz operation
	SYSCTRL->OSC8M.reg = (SYSCTRL->OSC8M.reg & ~SYSCTRL_OSC8M_PRESC_Msk)  | SYSCTRL_OSC8M_PRESC(0);
	  
	WDT->CTRL.reg	&=	(1<<WDT_CTRL_ENABLE); //disable watchdog
	 
	SYSCTRL->XOSC.reg &= ~SYSCTRL_XOSC_ENABLE;
	SYSCTRL->XOSC.reg = SYSCTRL_XOSC_AMPGC | SYSCTRL_XOSC_GAIN(3) | SYSCTRL_XOSC_XTALEN | SYSCTRL_XOSC_RUNSTDBY | SYSCTRL_XOSC_ENABLE;
	while(!SYSCTRL->PCLKSR.bit.XOSCRDY){}
	 
	GCLK->GENCTRL.reg = GCLK_GENCTRL_ID_GCLK1 | GCLK_GENCTRL_SRC_XOSC | GCLK_GENCTRL_RUNSTDBY | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_OE | GCLK_GENCTRL_IDC ;
	while(GCLK->STATUS.bit.SYNCBUSY){}

	timer0Init();
	NVIC_EnableIRQ(TC0_IRQn);
}

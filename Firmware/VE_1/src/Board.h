/**
*	\file		Board.h
*	\author		TPO
*	\date		16/06/2015
*	\brief		Biblioteca do arquivo contendo informacoes sobre a VE_1.
*	\details	Esta biblioteca do arquivo contem todas a rotinas de  baixo nivel para acesar a placa EV_1.
*	\copyright 	GNU V2.0
*/


#ifndef BOARD_H_
#define BOARD_H_

#include "samd20g17.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define PWM_MOTOR1_A_PORT		PORT_PA16
#define PWM_MOTOR1_B_PORT		PORT_PA17
#define PWM_MOTOR1_A_PORT_N		16
#define PWM_MOTOR1_B_PORT_N		17
#define PWM_MOTOR1_A_PMUX		PORT_PMUX_PMUXE_F
#define PWM_MOTOR1_B_PMUX		PORT_PMUX_PMUXO_F
#define PWM_MOTOR1_PORT_CONF	PORT->Group[0]
#define PWM_MOTOR1_TC_CONF		TC2->COUNT8
#define PWM_MOTOR1_TC_A_VAL		PWM_MOTOR1_TC_CONF.CC[0].reg
#define PWM_MOTOR1_TC_B_VAL		PWM_MOTOR1_TC_CONF.CC[1].reg

#define PWM_MOTOR2_A_PORT		PORT_PA18
#define PWM_MOTOR2_B_PORT		PORT_PA19
#define PWM_MOTOR2_A_PORT_N		18
#define PWM_MOTOR2_B_PORT_N		19
#define PWM_MOTOR2_A_PMUX		PORT_PMUX_PMUXE_F
#define PWM_MOTOR2_B_PMUX		PORT_PMUX_PMUXO_F
#define PWM_MOTOR2_PORT_CONF	PORT->Group[0]
#define PWM_MOTOR2_TC_CONF		TC3->COUNT8
#define PWM_MOTOR2_TC_A_VAL		PWM_MOTOR2_TC_CONF.CC[0].reg
#define PWM_MOTOR2_TC_B_VAL		PWM_MOTOR2_TC_CONF.CC[1].reg


#define ADC_MOTOR2_PORT				PORT_PA10
#define ADC_MOTOR2_PORT_CONF		PORT->Group[0]
#define ADC_MOTOR2_PORT_N			10
#define ADC_MOTOR2_PORT_DIV_2		ADC_MOTOR2_PORT_N/2
#define ADC_MOTOR2_PMUX				PORT_PMUX_PMUXE_B
#define ADC_MOTOR2_ADC_CONF			ADC
#define ADC_IS_SYNCRONIZED			ADC->STATUS.bit.SYNCBUSY
#define ADC_IS_RESULT_READY			ADC->INTFLAG.bit.RESRDY
#define ADC_MOTOR2_MUXPOS			ADC_INPUTCTRL_MUXPOS_PIN18

#define LED_RGB_RED_PORT		PORT_PA11
#define LED_RGB_BLUE_PORT		PORT_PA13
#define LED_RGB_GREEN_PORT		PORT_PA12
#define COLOUR_RED				LED_RGB_RED_PORT
#define COLOUR_BLUE				LED_RGB_BLUE_PORT
#define COLOUR_GREEN			LED_RGB_GREEN_PORT
#define LED_RGB_PORT_CONF		PORT->Group[0]
#define LED_RGB_SET(COLOUR)		LED_RGB_PORT_CONF.OUTCLR.reg = COLOUR
#define LED_RGB_TGL(COLOUR)		LED_RGB_PORT_CONF.OUTTGL.reg = COLOUR
#define LED_RGB_CLR(COLOUR)		LED_RGB_PORT_CONF.OUTSET.reg = COLOUR
#define LED_RGB_CLR_ALL()			LED_RGB_PORT_CONF.OUTSET.reg = LED_RGB_RED_PORT | LED_RGB_BLUE_PORT | LED_RGB_GREEN_PORT

#define THREAD_CLK_FREQUENCY	8000000
#define THREAD_PRESCALER		1
#define THREAD_FREQUENCY		100000
#define THREAD_FREQUENCY_OFF	0
#define THREAD_TOP_VAL			((THREAD_CLK_FREQUENCY)/(THREAD_PRESCALER*THREAD_FREQUENCY)-1+THREAD_FREQUENCY_OFF)
#define THREAD_COUNT_CONF		TC0->COUNT16
#define THREAD_INTERRUPT_CLEAR()	THREAD_COUNT_CONF.INTFLAG.reg |= TC_INTFLAG_OVF //clear interrupt


#define TIMER_CLK_FREQUENCY	8000000
#define TIMER_PRESCALER		1
#define TIMER_FREQUENCY		1000
#define TIMER_FREQUENCY_OFF	0
#define TIMER_TOP_VAL			((TIMER_CLK_FREQUENCY)/(TIMER_PRESCALER*TIMER_FREQUENCY)-1+TIMER_FREQUENCY_OFF)
#define TIMER_COUNT_CONF		TC1->COUNT16
#define TIMER_INTERRUPT_CLEAR()	TIMER_COUNT_CONF.INTFLAG.reg |= TC_INTFLAG_OVF //clear interrupt

void thread_init(void);
void thread_timer(void);
void led_init(void);
char debug_send_byte( char data);
char debug_send_data( char *data,  int size);
void  debug_init(void);
void adc_init(void);
uint16_t adc_read( void);
void board_init(void);
void adc_test(void);
char debug_send_byte_hand();
char debug_send_data_handler(int size);
void dummy_delay_ms(uint16_t ms);
enum DEBUG_S_FLAG {DEBUG_S_SENDING, DEBUG_S_IDLE, DEBUG_S_RECEIVING};
struct _debug_s
{
	int size_to_send;
	int size_sended;
	char data_tx[12];
	char flag;
	}debug_s;

#endif /* BOARD_H_ */
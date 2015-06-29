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
#include "sam.h"
#include "samd20g17.h"

#define PWM_MOTOR1_A_PORT		PORT_PA16
#define PWM_MOTOR1_B_PORT		PORT_PA17
#define PWM_MOTOR1_A_PORT_N		16
#define PWM_MOTOR1_B_PORT_N		17
#define PWM_MOTOR1_A_PMUX		PORT_PMUX_PMUXE_F
#define PWM_MOTOR1_B_PMUX		PORT_PMUX_PMUXO_F
#define PWM_MOTOR1_PORT_CONF	PORT->Group[0]
#define PWM_MOTOR1_TC_CONF		TC2->COUNT8
#define PWM_MOTOR1_TC_A_DUTY	PWM_MOTOR1_TC_CONF.CC[0]
#define PWM_MOTOR1_TC_B_DUTY	PWM_MOTOR1_TC_CONF.CC[1]

#define PWM_MOTOR2_A_PORT		PORT_PA18
#define PWM_MOTOR2_B_PORT		PORT_PA19
#define PWM_MOTOR2_A_PORT_N		18
#define PWM_MOTOR2_B_PORT_N		19
#define PWM_MOTOR2_A_PMUX		PORT_PMUX_PMUXE_F
#define PWM_MOTOR2_B_PMUX		PORT_PMUX_PMUXO_F
#define PWM_MOTOR2_PORT_CONF	PORT->Group[0]
#define PWM_MOTOR2_TC_CONF		TC3->COUNT8
#define PWM_MOTOR2_TC_A_DUTY	PWM_MOTOR2_TC_CONF.CC[0]
#define PWM_MOTOR2_TC_B_DUTY	PWM_MOTOR2_TC_CONF.CC[1]


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
#define LED_RGB_CLR_ALL()			LED_RGB_PORT_CONF.OUTSET.reg = COLOUR_RED | LED_RGB_BLUE_PORT | LED_RGB_GREEN_PORT

#define THREAD_CLK_FREQUENCY	8000000
#define THREAD_PRESCALER		1
#define THREAD_FREQUENCY		1000000
#define THREAD_FREQUENCY_OFF	0
#define THREAD_TOP_VAL			((THREAD_CLK_FREQUENCY)/(THREAD_PRESCALER*THREAD_FREQUENCY)-1+THREAD_FREQUENCY_OFF)
#define THREAD_COUNT_CONF		TC0->COUNT16
#define THREAD_INTERRUPT_CLEAR()	THREAD_COUNT_CONF.INTFLAG.reg |= TC_INTFLAG_OVF //clear interrupt

void thread_init(void);
void led_init(void);
void motor_init(void);
char debug_send_byte(unsigned char data);
char debug_send_data(unsigned char *data, unsigned int size);
void  debug_init(void);
void adc_init(void);
void adc_read(unsigned int number);
void board_init(void);
#endif /* BOARD_H_ */
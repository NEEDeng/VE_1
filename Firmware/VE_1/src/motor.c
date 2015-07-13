/*
 * motor.c
 *
 * Created: 7/6/2015 12:11:47 PM
 *  Author: Tulio
 */ 
#include "Board.h"
#include "motor.h"
#include "compiler.h"
#include "watches.h"
#include "sensors.h"
//#define true	1
//#define false	!true

char (*statefunc)() = motor_init;
char motor_fn(void)
{
	return (*statefunc)();
	
}
char motor_init(void)
{
	motor_s[0] = (struct _motor_s){.abs_position_actual=0,
	.abs_position_final=0,
	.adc_val_max =0,
	.adc_val_min = UINT16_MAX,
	.adc_val_actual = 0,
	.adc_val_last = 0,
	.direction =0 ,
	.duty = 0,
	.flag = 0,
	.motor_pwm_a_ptr = &PWM_MOTOR1_TC_A_VAL,
	.motor_pwm_b_ptr = &PWM_MOTOR1_TC_B_VAL
	};
	motor_s[0].motor_pwm_a_ptr = &PWM_MOTOR1_TC_B_VAL;
	motor_s[1] = (struct _motor_s){.abs_position_actual=0,
	.abs_position_final=0,
	.adc_val_actual = 0,
	.adc_val_max =0,
	.adc_val_min = UINT16_MAX,
	.adc_val_last = 0,
	.direction =0,
	.duty = 0,
	.flag = 0,
	.motor_pwm_a_ptr = &PWM_MOTOR2_TC_A_VAL,
	.motor_pwm_b_ptr = &PWM_MOTOR2_TC_B_VAL
	};
	statefunc = motor_find_min_max;
}
#define MIN_MAX_PRECISION	3
char motor_set_duty(enum MOTOR_SIDE_FLAG motor_side, uint8_t duty, enum MOTOR_DIRECTION_FLAG dir)
{
	float real_duty =0;
	if(motor_side>1)
		return -1;
	if(duty>100)
		duty =100;
	if(duty<0)
		duty =0;
	
	real_duty = ((float)duty*2.55);
	motor_s[motor_side].duty = duty;
	
	if(dir == MOTOR_DIRECTION_C)
	{
		
		*motor_s[motor_side].motor_pwm_b_ptr = 0;		
		*motor_s[motor_side].motor_pwm_a_ptr = (uint8_t)real_duty;		
	}
	else
	{
		*motor_s[motor_side].motor_pwm_b_ptr = (uint8_t)real_duty;	
		*motor_s[motor_side].motor_pwm_a_ptr = 0;
	}
	return 0;
	
}
char motor_find_min_max(void)
{
	static void *goto_jump = &&init;
	static uint8_t valor_str[7];
	uint16_t  adc_val;
	static uint16_t max_val=0,max_val_last=1;
	uint32_t cronos_ms;
	uint16_t min_val= UINT16_MAX, min_val_last=UINT16_MAX;
	static count =0;
	
	motor_set_duty(MOTOR_SIDE_RIGHT,65,MOTOR_DIRECTION_C);
	
	goto  *goto_jump;
	
	init:
	LED_RGB_SET(COLOUR_RED);

	watches_set_alarm_hz(0,0.3);
timer_1:
	adc_val = adc_data[0]; //leia a cada retorno dessa funcao
	count++;
	if(count>9)
	{
	//	debug_send_data_handler_number(adc_val);
			if(adc_val>max_val) //fique com o valor maximo
				{
					
						max_val = adc_val;
				
				}
		}
			
	if(!wathces_is_alarm_finished(0)) //enqnato nao terminou
	{
		goto_jump = &&timer_1;
		return 0;
	}
	else
	{
		goto_jump = &&until_next_max;	
	}
	LED_RGB_CLR_ALL();
	LED_RGB_SET(COLOUR_BLUE);
	return 0;
	/*Esperaremos pelo proximo pico */
until_next_max:
adc_val =  adc_data[0];
	if((max_val < (adc_val+MIN_MAX_PRECISION)) && (max_val > (adc_val-MIN_MAX_PRECISION)))
	{
		goto_jump = &&time_peak_measure;	
		debug_send_data_handler_number(adc_val);
		
	}
	else
	{
	return 0;
	
	}

/*Agora vamos medir o tempo entre maximos */
LED_RGB_CLR_ALL();
LED_RGB_SET(COLOUR_GREEN);

watches_set_cronos(0);
count=0;
time_peak_measure:
	{
		
					count++;
		adc_val= adc_data[0];
			//debug_send_data_handler_number(adc_val);
		if((max_val < (adc_val+MIN_MAX_PRECISION)) && (max_val > (adc_val-MIN_MAX_PRECISION)))
		{
			if(count>50)
			{
				watches_cronos_finish(0);
				watches_get_cronos_ms(0, &cronos_ms);
				debug_send_data_handler_number(cronos_ms);
			}
			
			else
			{

				return 0;
				}
		}
		else
		{
			return 0;
			
		}

	}
	
	motor_set_duty(MOTOR_SIDE_RIGHT,0,MOTOR_DIRECTION_CC);
	
	statefunc =motor_run;
		return 0;
}
char motor_run(void)
{
	return 0;
}

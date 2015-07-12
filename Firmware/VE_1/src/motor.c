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
	uint16_t min_val= UINT16_MAX, min_val_last=UINT16_MAX;
	motor_set_duty(MOTOR_SIDE_RIGHT,55,MOTOR_DIRECTION_CC);
	LED_RGB_SET(COLOUR_RED);
	goto  *goto_jump;
	init:
	watches_set_alarm_hz(0,0.5);
timer_1:
	if(!wathces_is_alarm_finished(0))
	{
		goto_jump = &&timer_1;
		return 0;
	}
	
	
//	while(true)
LED_RGB_CLR(COLOUR_RED);
timer_2:
	{
		watches_set_alarm(0,2);
		adc_val = adc_read();
		max_val = max(adc_val,max_val);
		if(max_val == max_val_last)
		{
			goto timer_2_end;
		}
		max_val_last = max(max_val_last,max_val);
		
timer_2_wait:
		if(!wathces_is_alarm_finished(0))
		{
			goto_jump = &&timer_2_wait;
			return 0;
		}	
		else
		{
			goto timer_2;
		}
	}
timer_2_end:	
	
	LED_RGB_SET(COLOUR_GREEN);
	sprintf(valor_str ,"%0.5d" , max_val);
	//itoa(valor_int,valor_str,10);

	for(int i=0;i<7;i++)
	{
		debug_s.data_tx[i] = valor_str[i];
	}
		valor_str[5] ='\r';
		valor_str[6] = '\n';
	
	//while(true)
	{
		motor_set_duty(MOTOR_SIDE_RIGHT,0,MOTOR_DIRECTION_CC);
		debug_send_data_handler(7);
	//		dummy_delay_ms(500);
			//LED_RGB_SET(COLOUR_BLUE);
	}
	statefunc = motor_run;
		return 0;
}
char motor_run(void)
{
	return 0;
}

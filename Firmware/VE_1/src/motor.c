/*
 * motor.c
 *
 * Created: 7/6/2015 12:11:47 PM
 *  Author: Tulio
 */ 
#include "Board.h"
#include "motor.h"
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
char motor_find_min_max()
{
	
}
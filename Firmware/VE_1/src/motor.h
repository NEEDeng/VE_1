/*
 * motor.h
 *
 * Created: 7/6/2015 12:11:59 PM
 *  Author: Tulio
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#define MOTOR_LOOK_UP_TABLE_SIZE		180
enum MOTOR_FLAG {MOTOR_RUNNING =0, MOTOR_STOPPED, MOTOR_PAUSED};
enum MOTOR_MODE_FLAG {MOTOR_MODE_TIME =0, MOTOR_MODE_ANGLE, MOTOR_MODE_ROTATION};
enum MOTOR_DIRECTION_FLAG {MOTOR_DIRECTION_C=0, MOTOR_DIRECTION_CC};
enum MOTOR_SIDE_FLAG {MOTOR_SIDE_LEFT=0, MOTOR_SIDE_RIGHT};
	
struct _motor_s
{
	uint16_t abs_position_actual; // 3.6 -> 3 turns and (216degrees = 360*0.6)
	uint16_t abs_position_final;
	uint16_t adc_val_max;
	uint16_t adc_val_min;
	uint16_t adc_val_last;
	uint16_t adc_val_actual;
	uint8_t	 duty;
	uint16_t look_up_table[MOTOR_LOOK_UP_TABLE_SIZE];
	uint8_t	 direction;
	uint8_t	 flag;
	uint8_t	 status;
	uint8_t	 speed; //degrees/s
	uint8_t	*motor_pwm_a_ptr;
	uint8_t	*motor_pwm_b_ptr;
}motor_s[2];

char motor_set_duty(enum MOTOR_SIDE_FLAG motor, uint8_t duty, enum MOTOR_DIRECTION_FLAG dir);
char motor_init(void);
#endif /* MOTOR_H_ */
/*
 * sensors.h
 *
 * Created: 7/12/2015 5:42:21 PM
 *  Author: Tulio
 */ 


#ifndef SENSORS_H_
#define SENSORS_H_

#define ADC_MAX_INPUT	1
volatile uint16_t adc_data[ADC_MAX_INPUT];

void adc_run();

#endif /* SENSORS_H_ */
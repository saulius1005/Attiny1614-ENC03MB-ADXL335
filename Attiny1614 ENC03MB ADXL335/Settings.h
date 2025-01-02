/*
 * Settings.h
 *
 * Created: 2024-02-20 11:01:10
 *  Author: Saulius
 */ 


#ifndef SETTINGS_H_
#define SETTINGS_H_

#define F_CPU 20000000
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (8 *(float)BAUD_RATE)) + 0.5) //USART baud calculation

#define ADXL_Xch 3 //X channel for adc
#define ADXL_Ych 2 //Y channel for adc
#define ADXL_Zch 1 //Z channel for adc
#define ADXL_CALIBRATION_MODE 0
#define ADXL_WORK_MODE 1
#define SENSITIVITY 0.3 //300mv/g
#define ZERO_Z_SENS 31 // 0.3* adc ref/ adc res

#define ENC_Xch 10 //X channel for adc
#define ENC_Ych 11 //Y channel for adc
#define ENC_X_REFch 4 //Xref channel for adc
#define ENC_Y_REFch 5 //Yref channel for adc
#define ENC_CALIBRATION_MODE 0
#define ENC_WORK_MODE 1
#define ADC_RES ADC_RESSEL_8BIT_gc
#define ADC_REF VREF_ADC0REFSEL_2V5_gc
#define OPAMP_GAIN 10 //on sensor board with 10k and 90k resistors (gain = (90k/10k)+1 = 10)
#define SCALE_FACTOR 0.00067 //0.67mV
#define SAMPLES 3 //for noise filtering 

#define ENC03MB 0 //Sensor number for Converter function
#define ADXL335 1 //Sensor number for Converter function
#define X 1 //Channels numbers for Converter function
#define Y 0
#define Z 2

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

 struct Work{
	 int16_t ENC03_X_CAL; //calibration value for X
	 int16_t ENC03_Y_CAL; //for Y
	 uint16_t ADXL_X_CAL; //X value for ADXL (middle point for acceleration data (0-g) )
	 uint16_t ADXL_Y_CAL; //Y
	 uint16_t ADXL_Z_CAL; //Z

 }Read;

void GPIO_init();
void ADC0_init();

void USART0_init();
void USART0_sendChar(char c);
int USART0_printChar(char c, FILE *stream);

void VREF_ADC();
uint16_t ADC0_read(uint8_t channel);

int16_t ENC_CALIB(uint8_t ch); //Axis and reference voltage error finding function. Bring back (averages of 100 measurements)  differences between axis and ref adc values
int16_t ENC_Work(uint8_t ch, uint16_t ref, uint8_t work); //Return compensated axis and reference difference ADC values

uint16_t ADXL_Cal(uint8_t ch, uint16_t ref); //Return 0g value of chosen axis
int16_t ADXL_Work(uint8_t ch , uint16_t ref, uint8_t mode); //Return selected channel adc value minus 0g value of selected axis

float Converter(uint8_t ch, uint8_t sensor, uint16_t ref); //Return calculated data for both sensors 
void Calibrator(); //Calibrate both sensors

#endif /* SETTINGS_H_ */
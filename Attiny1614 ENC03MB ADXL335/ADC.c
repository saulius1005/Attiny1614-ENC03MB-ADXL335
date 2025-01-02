/*
 * ADC.cpp
 *
 * Created: 2024-02-20 11:04:08
 *  Author: Saulius
 */ 
#include "Settings.h"

void ADC0_init(){
 ADC0.CTRLB = ADC_SAMPNUM_ACC64_gc; //64 measurements
 ADC0.CTRLC = ADC_PRESC_DIV16_gc | //20mhz/16 adc speed
			  ADC_REFSEL_INTREF_gc; // Internal reference
 ADC0.CTRLA = ADC_ENABLE_bm | ADC_RES; //adc enable with 10bit resolution
}

uint16_t ADC0_read(uint8_t channel){
 uint16_t data = 0;
 ADC0.MUXPOS  = channel; //channel selection 
 ADC0.COMMAND = ADC_STCONV_bm; //start conversion
 while(!(ADC0.INTFLAGS & ADC_RESRDY_bm)); //wait until we get result
 data = ADC0.RES;
 ADC0.INTFLAGS = ADC_RESRDY_bm; //clear result ready flag
 return (data>>6); //return average ADC value of 64 measurements
}
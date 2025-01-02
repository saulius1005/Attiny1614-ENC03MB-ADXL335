/*
 * VREF.cpp
 *
 * Created: 2024-02-20 11:04:23
 *  Author: Saulius
 */ 
#include "Settings.h"

void VREF_ADC(){
	VREF.CTRLA = ADC_REF; //Reference voltage for ADC: ENC03MB output 0.1 - 2.8V , ADXL335 output 0.1-2.8V
}
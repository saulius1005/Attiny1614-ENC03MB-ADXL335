/*
 * Common.c
 *
 * Created: 2024-02-21 14:10:43
 *  Author: Saulius
 */ 
#include "Settings.h"

float Converter(uint8_t ch, uint8_t sensor, uint16_t ref){
 float adcref = 4.34; //default 4.34V
 uint16_t adcres = 256; //default 8 bit
 int16_t chosenOne = 0;
  
 if(ADC_RES == ADC_RESSEL_10BIT_gc)
  adcres = 1024;
 if(ADC_REF == VREF_ADC0REFSEL_0V55_gc)
  adcref = 0.55;
 if(ADC_REF == VREF_ADC0REFSEL_1V1_gc)
  adcref = 1.1;
 if(ADC_REF == VREF_ADC0REFSEL_1V5_gc)
  adcref = 1.5;
 if(ADC_REF == VREF_ADC0REFSEL_2V5_gc)
  adcref = 2.5;

 if(sensor == ADXL335){//ADXL335
  chosenOne = ADXL_Work(ch, ref, ADXL_WORK_MODE);
  return (chosenOne * adcref / adcres) / SENSITIVITY; //return acceleration g
 }
 chosenOne = ENC_Work(ch, ref,ENC_WORK_MODE); //ENC-03MB sensor
 return (chosenOne * adcref / adcres)/ (SCALE_FACTOR * OPAMP_GAIN);//return for ENC-03MB angle velocity according to datasheet ((ENC_Read value * adc ref/ adc resolution) / (0.00067V (0.67mV) *10 (opamp gain)))
}

void Calibrator(){
 Read.ENC03_X_CAL = ENC_Work(X, Read.ENC03_X_CAL,ENC_CALIBRATION_MODE); // finding misalignment. At this time all sensors should keep steady
 Read.ENC03_Y_CAL = ENC_Work(Y, Read.ENC03_Y_CAL,ENC_CALIBRATION_MODE); 
 Read.ADXL_X_CAL = ADXL_Work(X, Read.ADXL_X_CAL, ADXL_CALIBRATION_MODE);
 Read.ADXL_Y_CAL = ADXL_Work(Y, Read.ADXL_Y_CAL, ADXL_CALIBRATION_MODE);
 Read.ADXL_Z_CAL = ADXL_Work(Z, Read.ADXL_Z_CAL, ADXL_CALIBRATION_MODE);
}
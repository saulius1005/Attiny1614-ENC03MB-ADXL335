/*
 * ADXL335.cpp
 *
 * Created: 2024-02-20 11:05:24
 *  Author: Saulius
 */ 
#include "Settings.h"

int16_t ADXL_Work(uint8_t ch , uint16_t ref, uint8_t mode){ // 
 uint16_t sampler = 0;
 uint32_t average = 0;

 for(uint8_t i = 0; i< SAMPLES; i++){ //digital filter 
  if(ch == X)//X
   sampler = ADC0_read(ADXL_Xch);
  if(ch == Z)//Z
   sampler = ADC0_read(ADXL_Zch);
  if(ch == Y) //Y
   sampler = ADC0_read(ADXL_Ych); 
  average += sampler; //adding all values it is not same as min+max/2 !!!
 }
 if(mode == ADXL_WORK_MODE)
  return (average / SAMPLES) - ref; 
 if(mode == ADXL_CALIBRATION_MODE){
  if(ch == Z) //Z axis normally
   return (average/SAMPLES) - ZERO_Z_SENS; //if chip placed normally Z out should be 1g
  return average/SAMPLES; //founding average adc value and return it back
 }
 return 0;
}

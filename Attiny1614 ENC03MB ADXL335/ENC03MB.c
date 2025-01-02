/*
 * ENC03MB.cpp
 *
 * Created: 2024-02-20 11:04:57
 *  Author: Saulius
 */ 
#include "Settings.h"

int16_t ENC_Work(uint8_t ch, uint16_t ref, uint8_t work){
 uint16_t readera = 0,
		  readerb = 0;
 uint32_t average = 0,
		  averager = 0;
 for(uint8_t i = 0; i<SAMPLES; i++){ //filter
  if(ch == X){ //X ch
   readera = ADC0_read(ENC_Xch);
   readerb = ADC0_read(ENC_X_REFch);
  }
  else{//Y ch
   readera = ADC0_read(ENC_Ych);
   readerb = ADC0_read(ENC_Y_REFch);
  }
  average += readera;
  averager += readerb;
 }
 if(work == ENC_WORK_MODE){
  readera = average / SAMPLES;
  readerb = averager / SAMPLES;
  if(!((readera +4 > readerb) && (readera -4 < readerb))) //checking if data fits into boundary with some error compensation at Working mode
  return (readera - ref) - readerb;
 }
 if(work == ENC_CALIBRATION_MODE)
  return (average - averager)/SAMPLES; // return average value if function working for calibration purposes
 return 0;
}

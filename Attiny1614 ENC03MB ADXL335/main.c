/*
 * Attiny1614 ENC-03MB ADXL335.cpp
 *
 * Created: 2024-02-20 11:00:37
 * Author : Saulius
 */ 
#include "Settings.h"

int main(void){

 GPIO_init();
 VREF_ADC();
 ADC0_init();
 USART0_init();
 Calibrator();// at this time don't move any of sensors !!!
 uint16_t a = 0;//for debugging samples collecting add here breakpoint (start)
 while (1){
 a++;
  printf("ENC-03MB X: %8.2f°/sec | Y: %8.2f°/sec | ", Converter(X,ENC03MB,Read.ENC03_X_CAL), Converter(Y,ENC03MB,Read.ENC03_Y_CAL)); //Sending data trought UART (using CP2102 module) to PC
  printf("ADXL335 X: %6.3fg | Y: %6.3fg  | Z: %6.3fg\r\n", Converter(X, ADXL335, Read.ADXL_X_CAL), Converter(Y, ADXL335, Read.ADXL_Y_CAL), Converter(Z, ADXL335, Read.ADXL_Z_CAL));
  _delay_ms(10);
if(a == 1000) 
 a = 0; //add debugging breakpoint here (finish)
 }
}


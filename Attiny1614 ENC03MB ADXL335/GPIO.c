/*
 * GPIO.cpp
 *
 * Created: 2024-02-20 11:05:40
 *  Author: Saulius
 */ 
#include "Settings.h"

void GPIO_init(){
 CPU_CCP = CCP_IOREG_gc;
 CLKCTRL.MCLKCTRLB = 0 << CLKCTRL_PEN_bp;
 while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm);

 PORTA.DIRCLR = PIN5_bm //ENC Y ref (AIN5)
			  |	PIN4_bm //ENC X ref(AIN4)
			  |	PIN3_bm //ADXL X input (AIN3)
			  | PIN2_bm //ADKL Y input (AIN2)
			  | PIN1_bm; //ADXL Z input (AIN1)

 PORTA.PIN3CTRL &= ~PORT_ISC_gm; //turn off digital buffer
 PORTA.PIN3CTRL |= PORT_ISC_INPUT_DISABLE_gc; //turn off interrupts
 PORTA.PIN3CTRL &= ~PORT_PULLUPEN_bm; //Turn off pullup resistor

 PORTA.PIN2CTRL &= ~PORT_ISC_gm; //turn off digital buffer
 PORTA.PIN2CTRL |= PORT_ISC_INPUT_DISABLE_gc; //turn off interrupts
 PORTA.PIN2CTRL &= ~PORT_PULLUPEN_bm; //Turn off pullup resistor

 PORTA.PIN1CTRL &= ~PORT_ISC_gm; //turn off digital buffer
 PORTA.PIN1CTRL |= PORT_ISC_INPUT_DISABLE_gc; //turn off interrupts
 PORTA.PIN1CTRL &= ~PORT_PULLUPEN_bm; //Turn off pullup resistor
	
 PORTB.DIRCLR = PIN1_bm //ENC X input (AIN10)
			  | PIN0_bm; //ENC Y input (AIN11)

 PORTB.PIN1CTRL &= ~PORT_ISC_gm; //turn off digital buffer
 PORTB.PIN1CTRL |= PORT_ISC_INPUT_DISABLE_gc; //turn off interrupts
 PORTB.PIN1CTRL &= ~PORT_PULLUPEN_bm; //Turn off pullup resistor

 PORTB.PIN0CTRL &= ~PORT_ISC_gm; //turn off digital buffer
 PORTB.PIN0CTRL |= PORT_ISC_INPUT_DISABLE_gc; //turn off interrupts
 PORTB.PIN0CTRL &= ~PORT_PULLUPEN_bm; //Turn off pullup resistor

 PORTB.DIRCLR = PIN3_bm; //In: UART RX
 PORTB.PIN3CTRL = PORT_PULLUPEN_bm;	//pullup RX
 PORTB.DIRSET = PIN2_bm;	//Out: UART TX
 PORTB.PIN2CTRL = PORT_PULLUPEN_bm; //pullup TX

}
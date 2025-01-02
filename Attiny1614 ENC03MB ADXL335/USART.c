/*
 * USART.cpp
 *
 * Created: 2024-02-20 21:44:10
 *  Author: Saulius
 */ 
#include "Settings.h"

static FILE USART_stream = FDEV_SETUP_STREAM(USART0_printChar, NULL, _FDEV_SETUP_WRITE);

void USART0_init(){
 USART0.BAUD = (uint16_t)USART0_BAUD_RATE(600000);// Set baud rate 600k
 USART0.CTRLB = USART_RXEN_bm | USART_TXEN_bm | USART_RXMODE_CLK2X_gc; //TX, TX on, 2x speed
 USART0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_1BIT_gc;
 stdout = &USART_stream;
}

void USART0_sendChar(char c){
 while (!(USART0.STATUS & USART_DREIF_bm));
 USART0.TXDATAL = c;
}

int USART0_printChar(char c, FILE *stream){
 USART0_sendChar(c);
 return 0;
}
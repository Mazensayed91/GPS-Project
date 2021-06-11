#include "TM4C123GH6PM2.h"
#include "UART.h"
#include "stdint.h"
#include "GPIO.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void UART0_init(void){
    SYSCTL->RCGCUART |= UARTA_R0;
    ///PORTA should be initialized
		initA();

    UART0->CTL &= ~(UARTA_R0);
    ///BRD for 16Mhz clock and 9600 baudrate is 104.16667
    UART0->IBRD = 104;
    UART0->FBRD = 11;
    UART0->LCRH = (UARTA_R0_FEN | UARTA_R0_WLEN_8);
    UART0->CTL |= (UARTA_R0 | UARTA_RO_RXE | UARTA_RO_TXE);

}

uint8_t UART0_available(void){
    return ((UART0->FR & UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}

uint8_t UART0_read(void){
    while(UART0_available() != 1);
    return (uint8_t)(UART0->DR & 0xFF);
}


void UART0_write(uint8_t data){
    while((UART0->FR & UART_FR_TXFF) != 0);
    UART0->DR = data;
}

void UART0_write_string(uint8_t *data){
  int i;
	for (i = 0; data[i] != '\0'; ++i) {
        while((UART0->FR & UART_FR_TXFF) != 0);
        UART0->DR = data[i];
    }
}

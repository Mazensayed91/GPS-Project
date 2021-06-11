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

void UART2_init(void){
    SYSCTL->RCGCUART |= 0x04;
    ///PORTD should be initialized (if not worked remove the initialization and initialize it here explicitly)
		initD();

    UART2->CTL &= ~(0x01);
    ///BRD for 16Mhz clock and 9600 baudrate is 104.16667
    UART2->IBRD = 104;
    UART2->FBRD = 11;
    UART2->LCRH = (UARTA_R0_FEN | UARTA_R0_WLEN_8);
    UART2->CTL |= (UARTA_R0 | UARTA_RO_RXE | UARTA_RO_TXE);

}

uint8_t UART2_available(void){
    return ((UART2->FR & UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}

uint8_t UART2_read(void){
    while(UART2_available() != 1);
    return (uint8_t)(UART2->DR & 0xFF);
}


void UART2_write(uint8_t data){
    while((UART2->FR & UART_FR_TXFF) != 0);
    UART2->DR = data;
}

void UART2_write_string(uint8_t *data){
  int i;
	for (i = 0; data[i] != '\0'; ++i) {
        while((UART2->FR & UART_FR_TXFF) != 0);
        UART2->DR = data[i];
    }
}

#ifndef UART_H
#define UART_H

#define UARTA_R0            0x01
#define UARTA_R0_WLEN_8     0x60
#define UARTA_R0_FEN        0x10
#define UARTA_RO_TXE        0x100
#define UARTA_RO_RXE        0x200
#define UART_FR_RXFE        0x10
#define UART_FR_TXFF        0x20

void UART0_init(void);
uint8_t UART0_available(void);
uint8_t UART0_read(void);
void UART0_write(uint8_t data);
void UART0_write_string(uint8_t *data);

void UART2_init(void);
uint8_t UART2_available(void);
uint8_t UART2_read(void);
void UART2_write(uint8_t data);
void UART2_write_string(uint8_t *data);


#endif //UART_H

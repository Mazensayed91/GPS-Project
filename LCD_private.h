#ifndef LCD_DRIVER_LCD_PRIVATE_H
#define LCD_DRIVER_LCD_PRIVATE_H

#define LCD_DATA GPIO_PORTB_DATA_R
#define LCD_CTRL GPIO_PORTB_DATA_R
/*******************************************************************************
*          Connect the controls of the lcd with pins 5,6,7 of Port D           *
*******************************************************************************/
#define RS 0x01
#define RW 0x02
#define EN 0x04

#endif //LCD_DRIVER_LCD_PRIVATE_H
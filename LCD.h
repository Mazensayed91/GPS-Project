#ifndef LCD_DRIVER_LCD_H
#define LCD_DRIVER_LCD_H

/*******************************************************************************
* Preprocessor Macros *
*******************************************************************************/

void delay_ms(int n);                       /* mili second delay function */
void delay_us(int n);                       /* micro second delay function */
void LCD_init(void);                        /* LCD initialization function */
void LCD_cmd(unsigned char command);        /*Used to send commands to LCD */
void LCD_write_data(unsigned char data);    /* Writes ASCII character */
void LCD_string (char *str);	            /* Send string to LCD function */

#endif //LCD_DRIVER_LCD_H

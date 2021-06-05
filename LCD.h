#ifndef LCD_DRIVER_LCD_H
#define LCD_DRIVER_LCD_H

/*******************************************************************************
* Preprocessor Macros *
*******************************************************************************/

void LCD_sendCommand(unsigned char command);
void LCD_displayCharacter(unsigned char data);
void LCD_init(void);
void LCD_displayString(const char *Str);
void LCD_goToRowColumn(unsigned char row,unsigned char col);
void LCD_displayStringRowColumn(unsigned char row,unsigned char col,const char *Str);
void LCD_intgerToString(int data);
void delayMs(int n);
void delayUs(int n);

#endif //LCD_DRIVER_LCD_H

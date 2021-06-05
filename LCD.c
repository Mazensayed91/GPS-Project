#include "LCD.h"
#include "LCD_config.h"
#include "LCD_private.h"
#include "tm4c123gh6pm.h"
#include "TM4C123GH6PM2.h"
#include "stdint.h"
#include "systick.h"
#include "systick_config.h"
#include "systick_priv.h"

void LCD_init(void)
{
	SYSCTL->RCGCGPIO |= 0x02; // Clock EN to GPIOB 
	LCD_PORT->DIR = 0xFF; // Set PORTB pins as output
	LCD_PORT->DEN = 0xFF; // Set PORTB pins as Digital

	/*******************************************************************************
	 *                      Initialization Sequence                                *
	 *******************************************************************************/
	//Step 1.   Power on, then delay > 100 ms
	delayMs(120); 
	//Step 2.   Instruction 0011b (3h), then delay > 4.1 ms
	LCD_sendCommand(0x30);
	delayMs(5);
	//Step 3.   Instruction 0011b (3h), then delay > 100 us
	LCD_sendCommand(0x30);
	delayUs(105);
	//Step 4.   Instruction 0011b (3h), then delay > 100 us
	LCD_sendCommand(0x30);
	delayUs(105);
	//Step 5.   Instruction 0010b (2h), then delay > 100 us
	LCD_sendCommand(0x20);
	delayUs(105);
	//Step 6.   Instruction 0010b (2h), then 1000b (8h), then delay > 53 us or check BF (4-bit data, 2-line)
	LCD_sendCommand(0x28); 
	//Step 7.   Instruction 0000b (0h), then 1000b (8h) then delay > 53 us or check BF
	//Step 8.   Instruction 0000b (0h), then 0001b (1h) then delay > 3 ms or check BF
	//Step 9.   Instruction 0000b (0h), then 0110b (6h), then delay > 53 us or check BF
	LCD_sendCommand(0x06); 
	LCD_sendCommand(0x01); // Clear screen
	LCD_sendCommand(0x0F); // Turn on display and Blink cursor
}

void LCD_sendCommand(unsigned char command)
{
  LCD_PORT->DATA &=~((1U<<0)|(1U<<1)); //Rs and RW
  LCD_PORT->DATA |= (1U<<2); //EN
  delayUs(0);
  LCD_PORT->DATA = (LCD_PORT->DATA & 0x0F) | (command & 0xF0);
  LCD_PORT->DATA = 0;
  
  LCD_PORT->DATA |= (1U<<2);
  delayUs(0);
  LCD_PORT->DATA = (LCD_PORT->DATA & 0x0F) | ((command & 0x0F) << 4);
  LCD_PORT->DATA = 0;
  if (command < 4)
    delayMs(2); 
  else
    delayUs(40);
} 
void LCD_displayCharacter(unsigned char data)
{
  LCD_PORT->DATA |= (1U<<0); //RS
  LCD_PORT->DATA &=~ (1U<<1); //RW
  delayMs(1);
  LCD_PORT->DATA |= (1U<<2); //EN
  delayMs(1);	
  LCD_PORT->DATA = (LCD_PORT->DATA & 0x0F) | (data & 0xF0);	
  delayMs(1);
  LCD_PORT->DATA &=~ (1U<<2);
  delayMs(1);
  LCD_PORT->DATA |= (1U<<2);
  delayMs(1);	
  LCD_PORT->DATA = (LCD_PORT->DATA & 0x0F) | ((data & 0x0F) << 4);
  delayMs(1);
  LCD_PORT->DATA &=~ (1U<<2);
  delayMs(1);	
} 
void LCD_displayString(const char *Str)
{
	unsigned char i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
	
}

void LCD_goToRowColumn(unsigned char row,unsigned char col)
{
	unsigned char Address;
	
	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
	}					
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000|Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION); 
}

void LCD_displayStringRowColumn(unsigned char row,unsigned char col,const char *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

void print_screen(char *str1,char *str2){
    LCD_sendCommand(CLEAR_DISPLAY);
    LCD_sendCommand(FIRST_ROW);
    delayMs(2);
    LCD_displayString(str1);
    LCD_sendCommand(SECOND_ROW);
    delayMs(2);
    LCD_displayString(str2);
}

/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n)
{
systick_delay_mili(n);
} 
/* delay n microseconds (16 MHz CPU clock) */
void delayUs(int n)
{
systick_delay_micro(n);
} 
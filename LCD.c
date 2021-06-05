#include "LCD.h"
#include "LCD_config.h"
#include "LCD_private.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"

void LCD_init(void)
{
    /*******************************************************************************
    * Make sure you initialize the port connected to the lcd first
    *******************************************************************************/
    delay_ms(20);
    LCD_cmd(0x30);
    delay_ms(5);
    LCD_cmd(0x30);
    delay_us(105);
    LCD_cmd(0x30);
    delay_us(105);
    LCD_cmd(0x20);
    delay_us(105);
    LCD_cmd(FUNCTION_SET_4BIT);
    LCD_cmd(CURSOR_OFF);
    LCD_cmd(CLEAR_DISPLAY);
    LCD_cmd(MOVE_CURSOR_RIGHT);
}

void LCD_write_data(unsigned char data){
    LCD_CTRL |= (RS);
    delay_ms(1);
    LCD_CTRL |= EN;
    delay_ms(1);
    LCD_DATA = (LCD_DATA & 0x0F) | (data & 0xF0);
    delay_ms(1);
    LCD_CTRL &= ~EN;
    delay_ms(1);

    LCD_CTRL |= EN;
    delay_ms(1);
    LCD_DATA = (LCD_DATA & 0x0F) | ((data & 0x0F) << 4);
    delay_ms(1);
    LCD_CTRL &= ~EN;
    delay_ms(1);
}

void LCD_cmd(unsigned char command){
    LCD_CTRL &= ~(RS);
    LCD_CTRL |= EN;
    delay_us(0);
    LCD_DATA = (LCD_DATA & 0x0F) | (command & 0xF0);
    delay_us(0);
    LCD_CTRL &= ~EN;
    delay_us(1);

    LCD_CTRL |= EN;
    delay_us(0);
    LCD_DATA = (LCD_DATA & 0x0F) | ((command & 0x0F) << 4);
    delay_us(0);
    LCD_CTRL &= ~EN;
    if(command < 4)
        delay_ms(2);
    else
        delay_us(43);
}

void LCD_string (char *str)	/* Send string to LCD function */
{
    int i = 0;
    while (str[i]!='\0'){
        LCD_write_data(str[i]);
        i++;
    }
}

void print_screen(char *str1,char *str2){
    LCD_cmd(CLEAR_DISPLAY);
    LCD_cmd(FIRST_ROW);
    delay_ms(2);
    LCD_string(str1);
    LCD_cmd(SECOND_ROW);
    delay_ms(2);
    LCD_string(str2);
}

/* Milli seconds delay function */
void delay_ms(int n)
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<3180;j++)
        {}
}

/* Micro seconds delay function */
void delay_us(int n)
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<3;j++)
        {}
}
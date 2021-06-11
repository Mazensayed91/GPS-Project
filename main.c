 /******************************************************************************
 *
 * Project: GPS
 *
 * File Name: main.c
 *
 * Description: Main file for GPS project
 *
 *******************************************************************************/
/*******************************************************************************
 *                               Connection                                    *
 *******************************************************************************/

#include "TM4C123GH6PM.h"
#include "LCD.h"
#include "stdint.h"
#include "systick_config.h"
#include "systick.h"
#include "systick_priv.h"
#include "GPIO.h"
#include "UART.h"
#include <stdlib.h>
#include <math.h>
#include "GPS.h"
#include "GPS_config.h"
#include "GPS_private.h"

char buf[100];
volatile char ind,flag,stringReceived;

///changed buffer size from 12 to 15
unsigned char latitude[15]; //char
unsigned char longitude[15];
unsigned char LCD_text[16];

unsigned char GPS_data;

point current, previous;
double total_distance = 0;
int point_taken = 0;

int main(void){
    UART2_init();
    UART0_init();
    LCD_init();
    initF();

    LCD_goToRowColumn(0,0);
    LCD_displayString("Press switch 1");
    LCD_goToRowColumn(1,0);
    LCD_displayString("to start");

    ///Busy wait until switch 1 pressed (Pin 4)
    while((GPIOF->DATA & (0x10)) == 0x10){};

    ///Waiting for first data
    LCD_sendCommand(CLEAR_SCREEN);
    LCD_goToRowColumn(0,2);
    LCD_displayString("GPS System");
    LCD_goToRowColumn(1,0);
    LCD_displayString("Waiting Data..");
    delayMs(5000);
}

void SystemInit(void)
{
/* Grant coprocessor access */
/* This is required since TM4C123G has a floating point coprocessor */
SCB->CPACR |= 0x00f00000;
}

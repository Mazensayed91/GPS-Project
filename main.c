 /******************************************************************************
 *
 * Project: GPS Tracking System
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
#include "LCD_config.h"
#include "LCD_private.h"
#include "stdint.h"
#include "systick_config.h"
#include "systick.h"
#include "systick_priv.h"
#include "GPIO.h"
#include "UART.h"
#include <stdlib.h>
#include <math.h>
#include "GPS.h"


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
    LCD_sendCommand(CLEAR_DISPLAY);
    LCD_goToRowColumn(0,2);
    LCD_displayString("GPS System");
    LCD_goToRowColumn(1,0);
    LCD_displayString("Waiting Data..");
    delayMs(5000);

    while (1)
    {
        get_gps_coordinates();
        UART0_write_string(latitude);
        UART0_write(',');
        UART0_write_string(longitude);
        UART0_write(';');
        current = convert_format(latitude, longitude);

        ///Calculate distance
        if (point_taken) {
            total_distance += calculate_distance(current, previous);
            LCD_floatToString((float)total_distance, LCD_text);

            ///Light the red lamp if distance exceeded 100 meter
            distance_100(total_distance);
            LCD_goToRowColumn(0, 0);
            LCD_displayString("Total Distance:");
            LCD_goToRowColumn(1, 0);
            LCD_displayString(LCD_text);
        }

        point_taken = 1;
        previous = current;
        ///Test to remove this delay
        delayMs(2000);

        ///End the trip by pushing switch 1 (pin 4)
        if ((GPIOF->DATA & (0x10)) == 0x00) {
            break;
        }
        LCD_sendCommand(CLEAR_DISPLAY); // Clear screen
    }
    while (1) {
        LCD_sendCommand(CLEAR_DISPLAY); // Clear screen
        LCD_goToRowColumn(0, 0);
        LCD_displayString("Dist traveled:");
        LCD_goToRowColumn(1, 0);
        LCD_displayString(LCD_text);
    }
}

void SystemInit(void)
{
/* Grant coprocessor access */
/* This is required since TM4C123G has a floating point coprocessor */
SCB->CPACR |= 0x00f00000;
}

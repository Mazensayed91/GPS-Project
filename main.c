#include "tm4c123gh6pm.h"
#include "TM4C123GH6PM2.h"
#include "stdint.h"
#include "LCD.h"
#include "LCD_config.h"
#include "LCD_private.h"
#include "GPIO.h"
#include "systick.h"
#include "systick_Priv.h"
#include "systick_config.h"


int main()
{
	LCD_init();
	while(1)
	{
			LCD_displayString("Latitude:");
			LCD_goToRowColumn(0,9);
			LCD_displayString("35.67");
			LCD_goToRowColumn(1,0);
			LCD_displayString("Longitude:");
			LCD_goToRowColumn(1,10);
			LCD_displayString("41.89");
			delayMs(500);
	}
}

void SystemInit(void)
{
/* Grant coprocessor access */
/* This is required since TM4C123G has a floating point coprocessor */
SCB->CPACR |= 0x00f00000;
}
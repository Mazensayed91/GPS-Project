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
	
}

void SystemInit(void)
{
/* Grant coprocessor access */
/* This is required since TM4C123G has a floating point coprocessor */
SCB->CPACR |= 0x00f00000;
}
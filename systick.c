#include "stdint.h"
#include "systick.h"
#include "systick_Priv.h"
#include "systick_config.h"
#include "tm4c123gh6pm.h"

void systick_init(void)
{
	NVIC_ST_CTRL_R = 0;            /* disable SysTick during setup */
    NVIC_ST_RELOAD_R = 0x00ffffff;    /* number of counts to wait */
    NVIC_ST_CURRENT_R = 0;         /* any value written to CURRENT clears */
	NVIC_ST_CTRL_R = 5;					/* enable SysTick with core clock */
}

void systick_delay(uint32_t delay)
{
	NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = delay-1;
    NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 5;
	while ((NVIC_ST_CTRL_R&0x00010000)==0)
	{
																	/* wait for COUNT flag */
	};
}

void systick_delay_micro(uint32_t n)			/*Delay for 1 micro*/
{		
		uint32_t i;
    for (i = 0; i < n; ++i) {
        systick_delay(DELAYMICRO);
    }
}

void systick_delay_mili(uint32_t n)			/*Delay for 1 mili*/
{
		uint32_t i;
    for (i = 0; i < n; ++i) {
        systick_delay(DELAYMILI);
    }
}

void systick_delay_sec(uint32_t n)			/*Delay for 1 sec*/
{
		uint32_t i;
    for (i = 0; i < n; ++i) {
        systick_delay(DELAYSEC);
    }
}
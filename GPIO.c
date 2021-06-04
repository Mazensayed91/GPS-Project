#include "stdint.h"
#include "GPIO.h"
#include "tm4c123gh6pm.h"


void PortA_Init() {  //command port (PA5 for RS ,PA6 for R/W, PA7 for E)
	
	SYSCTL_RCGCGPIO_R |= 0x01;     // 1) A clock
	while ((SYSCTL_PRGPIO_R & 0x01) == 0) {};         
	GPIO_PORTA_CR_R = 0xE0;           // allow changes to PA7-5       
	GPIO_PORTA_AMSEL_R = 0x00;        // 3) disable analog function
	GPIO_PORTA_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
	GPIO_PORTA_DIR_R = 0xE0;          // 5) PB7-PA5 output   
	GPIO_PORTA_AFSEL_R = 0x00;        // 6) no alternate function
	GPIO_PORTA_PUR_R = 0x00;          // disable pullup resistors         
	GPIO_PORTA_DEN_R = 0xE0;          // 7) enable digital pins PA7-PA0        
}

void distance(uint_t32 dis)
{
	if (dis >= 100) {

		GPIO_PORTF_DATA_R |= (1 << 1);

	}
}

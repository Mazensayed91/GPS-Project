#include "stdint.h"
#include "GPIO.h"
#include "tm4c123gh6pm.h"
#include "TM4C123GH6PM2.h"


void initA()
{ //command port (PA5 for RS ,PA6 for R/W, PA7 for E)
    SYSCTL->RCGCGPIO |= GPIO_PIN_1;
    while ((SYSCTL->PRGPIO & GPIO_PIN_1)!= GPIO_PIN_1){};
    GPIOA->AFSEL |= GPIO_PIN_10;
    GPIOA->PCTL = (GPIOA->PCTL & 0xFFFFFF00) | (GPIO_PCTL_PA0_U0RX | GPIO_PCTL_PA1_U0TX);
    GPIOA->DEN |= GPIO_PIN_10; // enable digital enable
}

void PortB_Init(){    // Data port

  SYSCTL->RCGCGPIO |= 0x02; // Clock EN to GPIOB
	GPIOB->DIR = 0xFF; // Set PORTB pins as output
	GPIOB->DEN = 0xFF; // Set PORTB pins as Digital
}

void initD(){
    SYSCTL->RCGCGPIO |= 0x08;
    while ((SYSCTL->PRGPIO & 0x08)!= 0x08){};
    GPIOD->AFSEL |= 0xC0;
    GPIOD->PCTL = (GPIOD->PCTL & 0x00FFFFFF) | (0x10000000 | 0x01000000);
    GPIOD->DEN |= 0xC0;
}

void initF() // Led and switches ports
{
    SYSCTL->RCGCGPIO |= 0x20;
    while ((SYSCTL->PRGPIO & 0x20)!= 0x20){};
    GPIOF->AFSEL = 0;
    GPIOF->PCTL = 0;
    GPIOF->AMSEL = 0;
    GPIOF->PUR = 0x11;
    GPIOF->DIR = 0x0E;
    GPIOF->DEN = 0x1F;
}

void distance_100(uint32_t dis)
{
    if (dis >= 100) {

        GPIOF->DATA |= (1 << 1);
    }
}

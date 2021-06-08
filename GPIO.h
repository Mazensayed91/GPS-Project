#ifndef MAIN_C_GPIO_H
#define MAIN_C_GPIO_H

#define GPIO_PIN_10         0x03
#define GPIO_PIN_1          0x01
#define GPIO_PCTL_PA0_U0RX      0x00000001
#define GPIO_PCTL_PA1_U0TX      0x00000010

void initF();
void initA();
void initD();
void distance_100(uint32_t dis);

#endif //MAIN_C_GPIO_H

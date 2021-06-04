#ifndef MAIN_C_SYSTIC_PRIV_H
#define MAIN_C_SYSTIC_PRIV_H

#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

#endif //MAIN_C_SYSTIC_PRIV_H

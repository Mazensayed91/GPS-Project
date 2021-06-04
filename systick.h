#ifndef MAIN_C_SYSTICK_H
#define MAIN_C_SYSTICK_H

void systick_init();
void systick_delay(uint32_t delay);
void systick_delay_micro(uint32_t n);
void systick_delay_mili(uint32_t n);
void systick_delay_sec(uint32_t n);

#endif //MAIN_C_SYSTICK_H

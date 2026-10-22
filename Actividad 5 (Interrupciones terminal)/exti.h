
#ifndef EXTI_H
#define EXTI_H

#include <stm32f10x.h>

extern volatile uint32_t int0_count;

void init_exti_pin(void);
void init_exti(void);

#endif

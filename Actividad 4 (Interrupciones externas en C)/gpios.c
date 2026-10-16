#include "gpios.h"

void gpio_init(void){

    RCC->APB2ENR |= (1 << 4);

    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |= (0x2 << 20);

    GPIOC->BSRR = (1 << 13);

}
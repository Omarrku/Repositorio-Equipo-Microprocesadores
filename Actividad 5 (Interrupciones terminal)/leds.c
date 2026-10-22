
#include <stm32f10x.h>
#include "leds.h"
#include "delay.h"

void init_led_pin(void){

    RCC->APB2ENR |= (1 << 4);

    // PC13 output push-pull, 2 MHz
    GPIOC->CRH &= ~(15 << 20);
    GPIOC->CRH |= (2 << 20);
}

void led_on_off(void){

    int x;

    for(x = 0; x < 5; x++){

        GPIOC->ODR &= ~(1 << 13);
        delay_ms(200);

        GPIOC->ODR |= (1 << 13);
        delay_ms(200);
    }
}

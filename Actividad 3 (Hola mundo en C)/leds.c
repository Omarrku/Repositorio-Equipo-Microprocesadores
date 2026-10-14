#include "leds.h"
#include "gpios.h"

void delay(void){

    volatile unsigned int i;

    for(i = 0; i < 600000; i++){

    }
}

void led_on_off(void){

    while(1){

        GPIOC->BRR = (1 << 13);
        delay();

        GPIOC->BSRR = (1 << 13);
        delay();

    }
}
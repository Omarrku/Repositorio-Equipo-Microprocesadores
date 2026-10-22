
#include <stm32f10x.h>
#include "delay.h"

void delay_ms(uint16_t t){

    volatile unsigned long j = 0;
    uint16_t i;

    for(i = 0; i < t; i++){

        for(j = 0; j < 6000; j++){

        }
    }
}

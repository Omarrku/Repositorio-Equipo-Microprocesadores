#include "leds.h"
#include "gpios.h"

void led_on_off(void){

    RCC->APB1ENR |= (1 << 0);

    TIM2->PSC = 8000 - 1;
    TIM2->ARR = 500 - 1;

    TIM2->EGR = 1;
    TIM2->SR = 0;

    TIM2->DIER |= (1 << 0);

    NVIC_EnableIRQ(TIM2_IRQn);

}

void TIM2_IRQHandler(void){

    if(TIM2->SR & (1 << 0)){

        TIM2->SR &= ~(1 << 0);

        if(GPIOC->ODR & (1 << 13)){

            GPIOC->BRR = (1 << 13);

        }
        else{

            GPIOC->BSRR = (1 << 13);

        }
    }
}
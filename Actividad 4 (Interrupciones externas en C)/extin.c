#include "extin.h"

void extin_init(void){

    RCC->APB2ENR |= (1 << 2);
    RCC->APB2ENR |= (1 << 0);

    GPIOA->BSRR = (1 << 0);

    GPIOA->CRL &= ~(0xF << 0);
    GPIOA->CRL |= (0x8 << 0);

    AFIO->EXTICR[0] &= ~(0xF << 0);

    EXTI->IMR |= (1 << 0);

    EXTI->FTSR |= (1 << 0);
    EXTI->RTSR |= (1 << 0);

    EXTI->PR = (1 << 0);

    NVIC_EnableIRQ(EXTI0_IRQn);

}

void EXTI0_IRQHandler(void){

    if(EXTI->PR & (1 << 0)){

        EXTI->PR = (1 << 0);

        if((GPIOA->IDR & (1 << 0)) == 0){

            GPIOC->BRR = (1 << 13);

            TIM2->CNT = 0;
            TIM2->SR = 0;
            TIM2->CR1 |= (1 << 0);

        }
        else{

            TIM2->CR1 &= ~(1 << 0);
            TIM2->SR = 0;

            GPIOC->BSRR = (1 << 13);

        }
    }
}
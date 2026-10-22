
#include <stm32f10x.h>
#include "exti.h"

volatile uint32_t int0_count = 0;

void EXTI0_IRQHandler(void){

    if(EXTI->PR & (1 << 0)){

        // Limpiar bandera de interrupcion
        EXTI->PR = (1 << 0);

        // Incrementar contador
        int0_count++;
    }
}

void init_exti_pin(void){

    // Habilitar GPIOA y AFIO
    RCC->APB2ENR |= (1 << 2) | (1 << 0);

    // PA0 como entrada pull-up
    GPIOA->CRL &= ~(15 << 0);
    GPIOA->CRL |= (8 << 0);

    // Activar pull-up de PA0
    GPIOA->ODR |= (1 << 0);
}

void init_exti(void){

    // Seleccionar PA0 para EXTI0
    AFIO->EXTICR[0] &= ~(15 << 0);

    // Interrupcion por flanco ascendente
    EXTI->RTSR |= (1 << 0);
    EXTI->FTSR &= ~(1 << 0);

    // Habilitar EXTI0
    EXTI->IMR |= (1 << 0);

    // Limpiar interrupcion pendiente
    EXTI->PR = (1 << 0);

    // Habilitar interrupcion en NVIC
    NVIC_EnableIRQ(EXTI0_IRQn);
}

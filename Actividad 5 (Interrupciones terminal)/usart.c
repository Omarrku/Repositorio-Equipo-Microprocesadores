
#include <stm32f10x.h>
#include "usart.h"

void init_usart1(void){

    uint32_t pclk2;
    uint32_t prescaler;
    uint32_t bits;

    // Habilitar USART1, GPIOA y AFIO
    RCC->APB2ENR |= (1 << 14) |
                    (1 << 2) |
                    (1 << 0);

    // Deshabilitar USART1 para configurar
    USART1->CR1 = 0;
    USART1->CR2 = 0;
    USART1->CR3 = 0;

    // PA9 = TX, alternate push-pull
    GPIOA->CRH &= ~(15 << 4);
    GPIOA->CRH |= (11 << 4);

    // PA10 = RX, floating input
    GPIOA->CRH &= ~(15 << 8);
    GPIOA->CRH |= (4 << 8);

    // Obtener frecuencia del reloj
    SystemCoreClockUpdate();

    bits = (RCC->CFGR >> 11) & 7;

    if(bits < 4){
        prescaler = 1;
    }
    else{
        prescaler = 1 << (bits - 3);
    }

    pclk2 = SystemCoreClock / prescaler;

    // Configurar USART a 9600 baudios
    USART1->BRR = (pclk2 + 4800) / 9600;

    // Habilitar USART, transmision y recepcion
    USART1->CR1 = USART_CR1_UE |
                  USART_CR1_TE |
                  USART_CR1_RE;
}

void usart1_sendbyte(unsigned char c){

    // Esperar registro TX disponible
    while((USART1->SR & USART_SR_TXE) == 0){
    }

    // Transmitir caracter
    USART1->DR = c;
}

void usart1_sendstring(char s[]){

    int i = 0;

    while(s[i] != '\0'){

        usart1_sendbyte(s[i]);
        i++;
    }

    // Esperar fin de transmision
    while((USART1->SR & USART_SR_TC) == 0){
    }
}

uint8_t usart1_receivebyte(void){

    // Esperar dato recibido
    while((USART1->SR & USART_SR_RXNE) == 0){
    }

    return (uint8_t)(USART1->DR & 0xFF);
}

// Enviar numero decimal a RealTerm
void usart1_sendnumber(uint32_t number){

    char buffer[11];
    int i = 0;

    do{

        buffer[i++] = (number % 10) + '0';
        number /= 10;

    }while(number > 0);

    while(i > 0){

        usart1_sendbyte(buffer[--i]);
    }
}

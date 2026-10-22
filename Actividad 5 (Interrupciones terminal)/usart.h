
#ifndef USART_H
#define USART_H

#include <stm32f10x.h>

void init_usart1(void);
void usart1_sendbyte(unsigned char c);
void usart1_sendstring(char s[]);
uint8_t usart1_receivebyte(void);
void usart1_sendnumber(uint32_t number);

#endif

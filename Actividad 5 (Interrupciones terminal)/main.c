
#include <stm32f10x.h>
#include "leds.h"
#include "exti.h"
#include "delay.h"
#include "usart.h"

int main(void){

    uint8_t receivedbyte;
    uint32_t interrupciones_atendidas = 0;
    uint32_t pendientes;

    SystemCoreClockUpdate();

    init_led_pin();
    GPIOC->ODR |= (1 << 13);

    init_exti_pin();
    init_exti();
    init_usart1();

    usart1_sendstring("\r\nenter character:\r\n");

    while(1){

        // Recibir caracteres desde RealTerm
        if(USART1->SR & USART_SR_RXNE){

            receivedbyte = usart1_receivebyte();

            // Responder con un asterisco
            usart1_sendbyte('*');
        }

        // Consultar contador de interrupciones
        pendientes = int0_count;

        // Procesar cada interrupcion en orden
        if(interrupciones_atendidas != pendientes){

            interrupciones_atendidas++;

            // Mostrar interrupcion en RealTerm
            usart1_sendstring("\r\n- Interrupcion ");

            usart1_sendnumber(
                interrupciones_atendidas
            );

            usart1_sendstring("\r\n");

            // Parpadear LED cinco veces
            led_on_off();
        }
    }
}

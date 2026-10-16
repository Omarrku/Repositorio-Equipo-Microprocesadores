#include "leds.h"
#include "gpios.h"
#include "extin.h"

int main(void){

    gpio_init();
    led_on_off();
    extin_init();

    while(1){

        __WFI();

    }
}
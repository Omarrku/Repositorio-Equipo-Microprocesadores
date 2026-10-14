#include "leds.h"
#include "gpios.h"

int main(void){

    gpio_init();

    led_on_off();

    while(1){

    }
}
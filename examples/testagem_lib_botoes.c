#include <stdio.h>
#include "pico/stdlib.h"
#include "button.h"

#define BOTAO_A 5
#define LED_BLUE 12

int main()
{

    button_init(BOTAO_A, PULLUP);
    
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, 0);

    volatile bool estado_A = 1;
    
    stdio_init_all();
    bool led_status = false;
    
    while (true) {
        if (button_toggle_on_press(BOTAO_A,&led_status))
        {
            gpio_put(LED_BLUE,led_status);
        }
    }
}

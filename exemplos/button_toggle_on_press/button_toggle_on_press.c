//2. Teste de button_toggle_on_press()

#include <stdio.h>
#include "pico/stdlib.h"
#include "button.h"

#define BOTAO 5
#define LED 12

bool led_status = false;

int main() {
    stdio_init_all();
    button_init(BOTAO, PULLUP);
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);
    gpio_put(LED, 0);

    printf("Testando button_toggle_on_press()\n");

    while (true) {
        if (button_toggle_on_press(BOTAO, &led_status)) {
            gpio_put(LED, led_status);
            printf("Toggle LED: %d\n", led_status);
        }
        sleep_ms(50);
    }

    return 0;
}
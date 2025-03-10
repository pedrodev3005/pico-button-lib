//3. Teste de button_pressed_for()

#include <stdio.h>
#include "pico/stdlib.h"
#include "button.h"

#define BOTAO 5
#define LED 12

int main() {
    stdio_init_all();
    button_init(BOTAO, PULLUP);
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);
    gpio_put(LED, 0);

    printf("Testando button_pressed_for()\n");

    while (true) {
        if (button_pressed_for(BOTAO, 2000)) {
            printf("Botão pressionado por mais de 2s!\n");
            gpio_put(LED, 1);
            sleep_ms(500);
            gpio_put(LED, 0);
        }
        sleep_ms(100);
    }

    return 0;
}
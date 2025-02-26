5 Testando button_wait_press()

#include <stdio.h>
#include "pico/stdlib.h"
#include "button.h"

#define BOTAO_A 5
#define LED_BLUE 12

int main() {
    stdio_init_all();
    button_init(BOTAO_A, PULLUP);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, 0);

    printf("Testando button_wait_press()...\n");
    printf("Pressione o botão para continuar!\n");

    button_wait_press(BOTAO_A);

    printf("Botão pressionado! Prosseguindo...\n");
    gpio_put(LED_BLUE, 1);  // Liga o LED após pressionar o botão

    while (true) {
        sleep_ms(100);
    }
}

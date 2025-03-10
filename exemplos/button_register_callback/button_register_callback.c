//4. Teste de button_register_callback()

#include <stdio.h>
#include "pico/stdlib.h"
#include "button.h"

#define BOTAO_A 5
#define BOTAO_B 6
#define LED_BLUE 12
#define LED_RED 13

void meu_callback(uint gpio, uint32_t events) {
    bool estado = button_read(gpio);
    if (gpio == BOTAO_A) gpio_put(LED_BLUE, estado);
    if (gpio == BOTAO_B) gpio_put(LED_RED, estado);
    printf("Botão %d: %s\n", gpio, estado ? "pressionado" : "solto");
}

int main() {
    stdio_init_all();
    button_init(BOTAO_A, PULLUP);
    button_init(BOTAO_B, PULLUP);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, 0);

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, 0);

    // Registra o callback com debounce automático
    button_register_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, meu_callback);
    button_register_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, meu_callback);

    printf("Testando button_register_callback() para BitDogLab!\n");

    while (true) sleep_ms(100);
}
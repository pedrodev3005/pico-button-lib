//1. Teste de button_read()

#include <stdio.h>
#include "pico/stdlib.h"
#include "button.h"

#define BOTAO 5  // Defina o pino do botão

int main() {
    stdio_init_all();
    sleep_ms(2000);
    button_init(BOTAO, PULLUP);

    printf("Testando button_read()\n");

    while (true) {
        bool estado = button_read(BOTAO);
        printf("Estado do botão: %d\n", estado);

    }

    return 0;
}
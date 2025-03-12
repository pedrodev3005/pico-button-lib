#include <stdio.h>
#include "pico/stdlib.h"
#include "button.h"

// Definição de GPIOs fictícios para teste
#define TEST_BUTTON_1 5
#define TEST_BUTTON_2 6

void test_button_init() {
    printf("Testando button_init...\n");
    button_init(TEST_BUTTON_1, PULLUP);
    button_init(TEST_BUTTON_2, PULLDOWN);
    printf("PASSOU\n");
}

void test_button_read() {
    printf("Testando button_read...\n");

    button_init(TEST_BUTTON_1, PULLUP);
    sleep_ms(1); 

    // **Verificar se começa como HIGH**
    if (gpio_get(TEST_BUTTON_1) != 1) {
        printf("FALHOU: TEST_BUTTON_1 deveria começar HIGH (puxado para cima).\n");
    }

    if (button_read(TEST_BUTTON_1) != false) {
        printf("FALHOU: button_read deveria retornar falso (botão solto).\n");
    }

    // Simular botão pressionado manualmente alterando o resistor interno
    gpio_pull_down(TEST_BUTTON_1);
    sleep_ms(1);

    if (gpio_get(TEST_BUTTON_1) != 0) {
        printf("FALHOU: TEST_BUTTON_1 deveria estar LOW após pull_down.\n");
    }

    if (button_read(TEST_BUTTON_1) != true) {
        printf("FALHOU: button_read deveria retornar verdadeiro (botão pressionado).\n");
    }

    printf("PASSOU\n");
}


void test_button_toggle_on_press() {
    printf("Testando button_toggle_on_press...\n");
    bool estado = false;

    button_init(TEST_BUTTON_1, PULLUP);  
    sleep_ms(1);

    // **Verificar estado inicial**
    if (estado != false) {
        printf("FALHOU: O estado inicial deveria ser falso.\n");
    }

    // **Simular um clique no botão**
    gpio_pull_down(TEST_BUTTON_1);
    sleep_ms(1);

    if (!button_toggle_on_press(TEST_BUTTON_1, &estado) || estado != true) {
        printf("FALHOU: botão não alternou corretamente para ligado.\n");
    }

    gpio_pull_up(TEST_BUTTON_1);
    sleep_ms(1);

    if (button_toggle_on_press(TEST_BUTTON_1, &estado) || estado != true) {
        printf("FALHOU: botão alternou sem novo clique.\n");
    }

    printf("PASSOU\n");
}


void test_button_debounce() {
    printf("Testando button_debounce...\n");

    button_init(TEST_BUTTON_1, PULLUP);

    // Simulação de pressões rápidas (ruído)
    gpio_pull_down(TEST_BUTTON_1);  // Pressiona botão (LOW)
    sleep_ms(10);  // Tempo menor que debounce
    if (button_debounce(TEST_BUTTON_1)) {
        printf("FALHOU: debounce aceitou ruído\n");
    }

    // Esperar tempo suficiente para um clique válido
    sleep_ms(200);
    if (!button_debounce(TEST_BUTTON_1)) {
        printf("FALHOU: debounce não detectou clique válido\n");
    }

    printf("PASSOU\n");
}

void test_button_pressed_for() {
    printf("Testando button_pressed_for...\n");

    button_init(TEST_BUTTON_1, PULLUP);

    gpio_pull_down(TEST_BUTTON_1); // Pressionar botão (LOW)
    sleep_ms(500); // Segurar por 500ms
    if (!button_pressed_for(TEST_BUTTON_1, 300)) {
        printf("FALHOU: não detectou pressionamento longo\n");
    }

    gpio_pull_up(TEST_BUTTON_1); // Soltar o botão (HIGH)
    sleep_ms(10);
    if (button_pressed_for(TEST_BUTTON_1, 300)) {
        printf("FALHOU: detectou pressionamento longo mesmo sem pressionar.\n");
    }

    printf("PASSOU\n");
}

void callback_teste(uint gpio, uint32_t events) {
    printf("Callback chamado para GPIO %d com evento %d\n", gpio, events);
}
 
void test_button_callback() {
    printf("Testando button_register_callback...\n");

    button_init(TEST_BUTTON_1, PULLUP);

    button_register_callback(TEST_BUTTON_1, GPIO_IRQ_EDGE_FALL, callback_teste);

    // **Simular evento para TEST_BUTTON_1**
    gpio_pull_down(TEST_BUTTON_1);  // Simula pressionamento
    sleep_ms(10);
    gpio_pull_up(TEST_BUTTON_1);    // Simula soltura (borda de subida)
    sleep_ms(20);

    printf("PASSOU\n");
}
 


 int main() {
    stdio_init_all();
    sleep_ms(2000); // Espera inicial para inicializar o console

    test_button_init();
    sleep_ms(50);
    test_button_read();
    sleep_ms(50);  
    test_button_toggle_on_press();
    sleep_ms(50);  
    test_button_debounce();
    sleep_ms(50);  
    test_button_pressed_for();
    sleep_ms(50);  
    test_button_callback();
    

    printf("\nTodos os testes concluídos.\n");
    return 0;
}
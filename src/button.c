#include "button.h"



// **Variáveis globais fixas para os botões**
static uint botao_A = 0;
static uint botao_B = 0;
static void (*callback_A)(uint, uint32_t) = NULL;
static void (*callback_B)(uint, uint32_t) = NULL;
static bool estado_anterior_A = true;
static bool estado_anterior_B = true;



void button_init(uint gpio, button_mode_t mode) {
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_IN);

    if (mode == PULLUP) {
        gpio_pull_up(gpio);
    } else {
        gpio_pull_down(gpio);
    }
}

bool button_read(uint gpio) {
    return gpio_get(gpio);
}

void button_set_interrupt(uint gpio, uint32_t event_mask, gpio_irq_callback_t callback) {
    gpio_set_irq_enabled_with_callback(gpio, event_mask, true, callback);
}

bool button_toggle_on_press(uint gpio, bool *state) {
    if (button_debounce(gpio)) { // Se o botão foi pressionado (debounce de 200ms sendo usado)
        *state = !(*state);   // Alterna o estado
        return true;          // Retorna que houve alternância
    }
    return false;
}

bool button_debounce(uint gpio) {
    static uint32_t last_press_time = 0;
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if (!button_read(gpio) && (current_time - last_press_time) > 200) { // 200ms de debounce
        last_press_time = current_time;
        return true; // Confirma que foi uma pressão real
    }
    return false;
}

void button_wait_press(uint gpio) {
    while (button_read(gpio)); // Espera enquanto o botão estiver solto
    sleep_ms(50);              // Pequeno debounce
}

bool button_pressed_for(uint gpio, uint32_t duration_ms) {
    if (!button_debounce(gpio)) { // Só continua se for um pressionamento válido
        return false;
    }

    uint32_t start_time = to_ms_since_boot(get_absolute_time());

    while (!button_read(gpio)) { // Enquanto o botão estiver pressionado
        if (to_ms_since_boot(get_absolute_time()) - start_time >= duration_ms) {
            return true; // Pressionamento longo detectado
        }
    }
    return false;
}

// **Função de Callback com debounce para interrupções**
void button_callback_internal(uint gpio, uint32_t events) {
    static uint32_t last_state_time_A = 0, last_state_time_B = 0;
    static bool last_state_A = true, last_state_B = true;
    
    bool estado_atual = button_read(gpio);
    uint32_t now = to_ms_since_boot(get_absolute_time());
    
    // **Debounce para BOTAO A**
    if (gpio == botao_A) {
        if (estado_atual != last_state_A) {
            if (now - last_state_time_A > DEBOUNCE_TIME_MS) {
                last_state_A = estado_atual;
                last_state_time_A = now;
                callback_A(gpio, events);  // Chama o callback apenas quando o estado muda
            }
        }
    }

    // **Debounce para BOTAO B**
    if (gpio == botao_B) {
        if (estado_atual != last_state_B) {
            if (now - last_state_time_B > DEBOUNCE_TIME_MS) {
                last_state_B = estado_atual;
                last_state_time_B = now;
                callback_B(gpio, events);  // Chama o callback apenas quando o estado muda
            }
        }
    }
}


// **Função para registrar um callback com debounce embutido**
void button_register_callback(uint gpio, uint32_t events, void (*callback)(uint, uint32_t)) {
    if (botao_A == 0) {  // Caso seja o primeiro botão registrado
        botao_A = gpio;
        callback_A = callback;
    } else if (botao_B == 0) {  // Caso seja o segundo botão registrado
        botao_B = gpio;
        callback_B = callback;
    }
    // Habilita a interrupção com a função interna de callback
    gpio_set_irq_enabled_with_callback(gpio, events, true, &button_callback_internal);
}
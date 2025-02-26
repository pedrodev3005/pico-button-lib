#include "button.h"

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


void button_register_callback(uint gpio, uint32_t event_mask, button_callback_t callback) {
    gpio_set_irq_enabled_with_callback(gpio, event_mask, true, (gpio_irq_callback_t)callback);
}
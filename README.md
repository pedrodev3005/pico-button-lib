---

# 🔘 Biblioteca de Botões para Raspberry Pi Pico

Uma biblioteca para **gerenciar botões** na **Raspberry Pi Pico**, permitindo leitura do estado, debounce, eventos assíncronos com interrupções e callbacks.

---

## 🚀 Recursos

✅ **Leitura direta** do estado do botão  
✅ **Debounce embutido** para leituras confiáveis  
✅ **Detecção de pressionamento longo**  
✅ **Interrupções** e **callbacks** para eventos assíncronos  
✅ **Suporte a até dois botões fixos** (`BOTAO_A` e `BOTAO_B`)  

---

## 📦 Instalação

1️⃣ **Clone o repositório**:
   ```sh
   git clone https://github.com/pedrodev3005/pico-button-lib.git
   cd pico-button-lib
   ```

2️⃣ **Adicione ao seu projeto**:  
   No seu `CMakeLists.txt`, inclua:
   ```cmake
   add_subdirectory(pico-button-lib)
   target_link_libraries(seu_projeto pico-button-lib)
   ```

3️⃣ **Inclua o cabeçalho no seu código**:
   ```c
   #include "button.h"
   ```

---

## 🛠️ Como Usar

### 🔹 Inicializando um botão
```c
button_init(5, PULLUP);  // Configura o botão no GPIO 5 com pull-up
```

### 🔹 Lendo o estado do botão
```c
bool estado = button_read(5);
if (estado) {
    printf("Botão pressionado!\n");
}
```

### 🔹 Alternando estado com pressionamento
```c
bool toggle = false;
if (button_toggle_on_press(5, &toggle)) {
    printf("Novo estado: %d\n", toggle);
}
```

### 🔹 Verificando se o botão foi pressionado por X milissegundos
```c
if (button_pressed_for(5, 2000)) { // 2 segundos
    printf("Botão pressionado por 2 segundos!\n");
}
```

### 🔹 Esperando um pressionamento (bloqueante)
```c
button_wait_press(5);
printf("Botão pressionado!\n");
```

### 🔹 Registrando um callback para eventos do botão
```c
void meu_callback(uint gpio, uint32_t events) {
    printf("Botão %d acionado! Evento: %u\n", gpio, events);
}

button_register_callback(5, GPIO_IRQ_EDGE_FALL, meu_callback);
```

---

## 📝 Exemplo Completo

```c
#include "button.h"
#include <stdio.h>

void callback(uint gpio, uint32_t events) {
    printf("Botão %d mudou de estado! Evento: %u\n", gpio, events);
}

int main() {
    stdio_init_all();

    button_init(5, PULLUP);
    button_register_callback(5, GPIO_IRQ_EDGE_FALL, callback);

    while (true) {
        if (button_pressed_for(5, 3000)) {
            printf("Botão segurado por 3s!\n");
        }
        sleep_ms(100);
    }
    return 0;
}
```

---

## 🔧 Funções Disponíveis

| Função                                   | Descrição |
|------------------------------------------|-----------|
| `button_init(pin, mode)`                 | Inicializa um botão no `pin` com `PULLUP` ou `PULLDOWN` |
| `button_read(pin)`                        | Retorna `true` se o botão estiver pressionado |
| `button_toggle_on_press(pin, *state)`     | Alterna o estado booleano ao pressionar o botão |
| `button_pressed_for(pin, ms)`             | Retorna `true` se o botão for pressionado por `ms` milissegundos |
| `button_wait_press(pin)`                  | Bloqueia a execução até o botão ser pressionado |
| `button_set_interrupt(pin, event_mask, callback)` | Ativa interrupções para um botão |
| `button_register_callback(pin, events, callback)` | Registra um callback para eventos de botão (até dois botões suportados) |

---

## 📄 Licença

Este projeto está sob a licença **MIT**, permitindo uso, modificação e distribuição livremente. 📜

---

### 🔥 O que foi ajustado no README?

- **Adicionei o suporte fixo para dois botões (A e B)** na explicação da função `button_register_callback`.  
- **Corrigi detalhes do debounce e interrupções**, para ficar coerente com a implementação da `button_callback_internal`.  
- **Expliquei que o debounce é embutido** para evitar acionamentos fantasmas.  
- **Melhorei a explicação das funções e exemplos**, para deixar tudo mais claro e direto.  

Se quiser mudar algo ou adicionar detalhes, só avisar! 🚀🔘

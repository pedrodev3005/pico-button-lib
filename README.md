---

# 🔘 Biblioteca de Botões para Raspberry Pi Pico

Uma biblioteca para **gerenciar botões** na **Raspberry Pi Pico**, mais especificamente na bitdoglab, permitindo leitura do estado, debounce, eventos assíncronos com interrupções e callbacks.

---

## 🚀 Recursos

✅ **Leitura direta** do estado do botão  
✅ **Debounce embutido** para leituras confiáveis  
✅ **Detecção de pressionamento longo**  
✅ **Interrupções** e **callbacks** para eventos assíncronos  
✅ **Suporte a até dois botões fixos** (`BOTAO_A` e `BOTAO_B`)  

---

## 📂 Estrutura do Projeto

```
📁 Código_fonte      # Biblioteca do buzzer
│── 📁 inc          # Arquivos de cabeçalho
│   ├── button.h
│
│── 📁 src          # Implementação da biblioteca
│   ├── button.c
│
│── README.md       # Documentação do projeto
│
📁 exemplos          # Exemplos de uso da biblioteca (cada subpasta é um projeto independente)
│── 📁 button_pressed_for            # Exemplo da função button_pressed_for()
│── 📁 button_read                   # Exemplo da função button_read()
│── 📁 button_register_callback      # Exemplo da função button_register_callback()
│── 📁 button_toogle_on_press        # Exemplo da função button_toogle_on_press()
│── 📁 button_wait_press             # Exemplo da função button_wait_press()
```
---

## 🛠️ Como Rodar os Exemplos  

### 🔹 1️⃣ Instale a Extensão da Raspberry Pi no VS Code  
Se ainda não tiver instalado, adicione a extensão **"Raspberry Pi Pico - C/C++ Project"** no **VS Code**.

### 🔹 2️⃣ Importe o Exemplo Desejado  
1. No VS Code, clique em **"Importar Projeto"**  
2. Selecione a **pasta do exemplo** dentro de `exemplos/`  
3. Compile e **grave na bitdoglab** 🚀  

**Exemplo:**
Se quiser testar a função `button_wait_press`, importe:  
📂 `exemplos/button_wait_press`

---

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

| Função                                    | Descrição |
|------------------------------------------ |-----------|
| `button_init(pin, mode)`                  | Inicializa um botão no `pin` com `PULLUP` ou `PULLDOWN` |
| `button_read(pin)`                        | Retorna `true` se o botão estiver pressionado |
| `button_toggle_on_press(pin, *state)`     | Alterna o estado booleano ao pressionar o botão |
| `button_pressed_for(pin, ms)`             | Retorna `true` se o botão for pressionado por `ms` milissegundos |
| `button_wait_press(pin)`                  | Bloqueia a execução até o botão ser pressionado |
| `button_register_callback(pin, events, callback)` | Registra um callback para eventos de botão (até dois botões suportados) |

---

## 📄 Licença

Este projeto está sob a licença **MIT**, permitindo uso, modificação e distribuição livremente. 📜

---


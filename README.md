# Tarefa Aula 03/02: Introdução às Interfaces de Comunicação Serial com RP2040 (UART, SPI e I2C)

## Descrição do Projeto
Este projeto utiliza o microcontrolador **RP2040** para controlar uma matriz de LEDs endereçáveis **WS2812B** e realizar a interação com o usuário por meio de dois botões (A e B). Além disso, inclui um display **SSD1306** para exibição de mensagens e a modificação da biblioteca de fontes.

### Componentes Utilizados
- **Raspberry Pi Pico (RP2040)**
- **Matriz 5x5 de LEDs WS2812B** (endereçáveis) - GPIO 7
- **LED RGB** - GPIOs 11 (Verde), 12 (Azul)
- **Botão A** - GPIO 5
- **Botão B** - GPIO 6
- **Display OLED SSD1306** (I2C - GPIO 14 e 15)

## Funcionalidades do Projeto
### 1. Modificação da Biblioteca `font.h`
- Adicionar caracteres minúsculos à biblioteca `font.h`, criando novos padrões, além de ícones personalizados.

### 2. Entrada de Caracteres via PC
- Os caracteres digitados no **Serial Monitor** do VS Code são exibidos no display SSD1306.
- Apenas um caractere será enviado por vez.
- Se um número de **0 a 9** for digitado, ele será exibido na matriz **WS2812B** com um padrão correspondente.

### 3. Interação com o Botão A
- Alterna o estado do **LED Verde** (ligado/desligado).
- Exibe uma mensagem informativa no display SSD1306.
- Envia um texto descritivo para o Serial Monitor.

### 4. Interação com o Botão B
- Alterna o estado do **LED Azul** (ligado/desligado).
- Exibe uma mensagem informativa no display SSD1306.
- Envia um texto descritivo para o Serial Monitor.

## Como Executar o Projeto
1. Compile o código no Raspberry Pi Pico utilizando o **CMakeLists.txt**.
2. Conecte o Raspberry Pi Pico ao PC via USB e abra o **Serial Monitor** no VS Code.
3. Pressione os botões A ou B para alternar os LEDs e observe as mensagens no display.
4. Digite caracteres no Serial Monitor para exibi-los no display.
5. Digite números de **0 a 9** para exibi-los na matriz **WS2812B**.

## Demonstração
Assista ao funcionamento do projeto neste [vídeo demonstrativo](https://drive.google.com/file/d/1mG8nyyZ_10PflgGESEHk-oKKaDJ3Q-89/view?usp=sharing).

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"

#include "ws2812b.pio.h"

// Definição dos pinos para conexão com os LEDs RGB
#define LED_G_PIN 11
#define LED_B_PIN 12

// Definição dos pino para a conexão com os Botões
#define BTN_A_PIN 5
#define BTN_B_PIN 6

// Definições para uso dos LEDs na Matriz 5x5
#define LED_MTX_COUNT 25
#define LED_MTX_LEVEL 20 // A intesidade está baixa para não causar incômodo (0-255, caso deseje alterar)
#define LED_MTX_PIN 7

// Definições para o uso da comunicação serial I2C
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define ADDRESS 0x3C

// Pix GRB
typedef struct pixel_t {
    uint8_t G, R, B;
} led_t;

led_t led_matrix[LED_MTX_COUNT]; // Buffer de pixels que compôem a matriz

uint32_t led_number_pattern[10] = {
    0xe5294e, // Número 0
    0x435084, // Número 1
    0xe4384e, // Número 2
    0xe4390e, // Número 3
    0xa53902, // Número 4
    0xe1390e, // Número 5
    0xe4394e, // Número 6
    0xe40902, // Número 7
    0xe5394e, // Número 8
    0xe5390e  // Número 9
};

/*
* Inicialização das GPIOs
*/
void init_gpio() {
    gpio_init(LED_G_PIN);
    gpio_init(LED_B_PIN);
    gpio_init(BTN_A_PIN);
    gpio_init(BTN_B_PIN);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    
    gpio_set_dir(LED_G_PIN, GPIO_OUT);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);
    gpio_set_dir(BTN_A_PIN, GPIO_IN);
    gpio_set_dir(BTN_B_PIN, GPIO_IN);

    gpio_pull_up(BTN_A_PIN);
    gpio_pull_up(BTN_B_PIN);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

// Variáveis para uso da PIO
PIO pio;
uint sm;

/*
* Inicialização da PIO
*/
void init_pio(uint pin) {
    uint offset = pio_add_program(pio0, &ws2812b_program);
    pio = pio0;

    sm = pio_claim_unused_sm(pio, false);

    ws2812b_program_init(pio, sm, offset, pin);
}

void init_display() {
    ssd1306_t ssd; // Inicializa a estrutura do display
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ADDRESS, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);   
}

/*
 * Atribuição de cor a um LED
 */
void set_led(const uint id, const uint8_t R, const uint8_t G, const uint8_t B) {
    led_matrix[id].R = R;
    led_matrix[id].G = G;
    led_matrix[id].B = B;
}

/*
 * Limpeza do buffer de LEDs
 */
void clear_leds() {
    for (uint i = 0; i < LED_MTX_COUNT; i++) {
        led_matrix[i].R = 0;
        led_matrix[i].G = 0;
        led_matrix[i].B = 0;
    }
}

// Formatação do valor GRB
uint32_t rgb_value(uint8_t B, uint8_t R, uint8_t G){
  return (G << 24) | (R << 16) | (B << 8);
}

/*
 * Transferência dos valores do buffer para a matriz de LEDs
 */
void write_leds() {
    uint32_t value;
    for (uint i = 0; i < LED_MTX_COUNT; ++i) {
        value = rgb_value(led_matrix[i].B, led_matrix[i].R, led_matrix[i].G);
        pio_sm_put_blocking(pio, sm, value);
    }
}


int main() {
    stdio_init_all();
    init_pio(LED_MTX_PIN);
    clear_leds();
    i2c_init(I2C_PORT, 400 * 1000);
    init_gpio();
    init_display();

    while (true) {
        printf("Interfaces de Comunicação Serial.\n");
        sleep_ms(1000);
    }
}

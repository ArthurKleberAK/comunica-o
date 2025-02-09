#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"
#include "hardware/clocks.h"
#include "inc/ssd1306.h"
#include "inc/font.h"
//arquivo .pio
#include "communication.pio.h"


// Definição dos pinos
#define UART_ID uart0 // Seleciona a UART0
#define BAUD_RATE 115200 // Define a taxa de transmissão
#define UART_TX_PIN 0 // Pino GPIO usado para TX
#define UART_RX_PIN 1 // Pino GPIO usado para RX
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
#define LED_RGB_G 12
#define LED_RGB_B 11
#define BOTAO_A 5
#define BOTAO_B 6
#define OUT_PIN 7

//número de LEDs
#define NUM_PIXELS 25

int PHYSICAL_LEDS_MAPPER[25] = {
    24, 23, 22, 21, 20,
    15, 16, 17, 18, 19,
    14, 13, 12, 11, 10,
    5, 6, 7, 8, 9,
    4, 3, 2, 1, 0};

//rotina para definição da intensidade de cores do led
uint32_t matrix_rgb(double b, double r, double g)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (R << 24) | (B << 16) | (G << 8);
}

//rotina para acionar a matrix de leds - ws2812b
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){

   for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        int led_matrix_location = PHYSICAL_LEDS_MAPPER[i];
        valor_led = matrix_rgb(r * desenho[led_matrix_location], g * desenho[led_matrix_location], b * desenho[led_matrix_location]);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

double matriz_0[25] = {
    0.0, 2.0, 2.0, 2.0, 0.0,  
    0.0, 2.0, 0.0, 2.0, 0.0, 
    0.0, 2.0, 0.0, 2.0, 0.0, 
    0.0, 2.0, 0.0, 2.0, 0.0, 
    0.0, 2.0, 2.0, 2.0, 0.0
    };
    // 1
    double matriz_1[25] = {
    0.0, 0.0, 2.0, 0.0, 0.0, 
    0.0, 2.0, 2.0, 0.0, 0.0, 
    0.0, 0.0, 2.0, 0.0, 0.0, 
    0.0, 0.0, 2.0, 0.0, 0.0, 
    0.0, 2.0, 2.0, 2.0, 0.0
    };
    // 2
    double matriz_2[25] = {
    0.0, 2.0, 2.0, 2.0, 0.0, 
    0.0, 0.0, 0.0, 2.0, 0.0, 
    0.0, 2.0, 2.0, 2.0, 0.0, 
    0.0, 2.0, 0.0, 0.0, 0.0, 
    0.0, 2.0, 2.0, 2.0, 0.0
    };
    //3
    double matriz_3[25] = 
    {
    0.0, 2.0, 2.0, 2.0, 0.0, 
    0.0, 0.0, 0.0, 2.0, 0.0, 
    0.0, 2.0, 2.0, 2.0, 0.0, 
    0.0, 0.0, 0.0, 2.0, 0.0, 
    0.0, 2.0, 2.0, 2.0, 0.0
    };
    //4
    double matriz_4[25] = 
    {
    0.0, 2.0, 0.0, 2.0, 0.0, 
    0.0, 2.0, 0.0, 2.0, 0.0, 
    0.0, 2.0, 2.0, 2.0, 0.0, 
    0.0, 0.0, 0.0, 2.0, 0.0, 
    0.0, 0.0, 0.0, 2.0, 0.0
    };
    //5
    double matriz_5[25] = {
    0.0, 2.0, 2.0, 2.0, 0.0, 
    0.0, 2.0, 0.0, 0.0, 0.0, 
    0.0, 2.0, 2.0, 2.0, 0.0, 
    0.0, 0.0, 0.0, 2.0, 0.0, 
    0.0, 2.0, 2.0, 2.0, 0.0
    };
    // 6 
    double matriz_6[25] = {
    0.0, 2.0, 2.0, 2.0, 0.0, 
    0.0, 2.0, 0.0, 0.0, 0.0, 
    0.0, 2.0, 2.0, 2.0, 0.0, 
    0.0, 2.0, 0.0, 2.0, 0.0, 
    0.0, 2.0, 2.0, 2.0, 0.0
    };
    //7
    double matriz_7[25] = {
    0.0, 2.0, 2.0, 2.0, 0.0, 
    0.0, 0.0, 0.0, 2.0, 0.0, 
    0.0, 0.0, 2.0, 0.0, 0.0, 
    0.0, 2.0, 0.0, 0.0, 0.0, 
    0.0, 2.0, 0.0, 0.0, 0.0
    };
    //8
    double matriz_8[25] = {
    0.0, 2.0, 2.0, 2.0, 0.0, 
    0.0, 2.0, 0.0, 2.0, 0.0, 
    0.0, 2.0, 2.0, 2.0, 0.0, 
    0.0, 2.0, 0.0, 2.0, 0.0, 
    0.0, 2.0, 2.0, 2.0, 0.0
    };
    //9
    double matriz_9[25] = {
    0.0, 2.0, 2.0, 2.0, 0.0, 
    0.0, 2.0, 0.0, 2.0, 0.0, 
    0.0, 2.0, 2.0, 2.0, 0.0, 
    0.0, 0.0, 0.0, 2.0, 0.0, 
    0.0, 0.0, 0.0, 2.0, 0.0
    };
    // Ponteiro para armazenar a matriz ativa
    double* matriz_atual = matriz_0;
    
// Variáveis globais para armazenar estados
volatile bool led_green_state = false;
volatile bool led_blue_state = false;

// Prototipo da função de interrupção
static void gpio_irq_handler(uint gpio, uint32_t events);
static volatile uint32_t last_time = 0;

ssd1306_t ssd; // Variável global para o display

void gpio_irq_handler(uint gpio, uint32_t events) {
    static uint32_t last_time = 0;
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    if (current_time - last_time > 500000) { // Debounce de 500ms
        last_time = current_time;       

        if (gpio_get(BOTAO_A)==0)
            {
              led_green_state = !led_green_state; //Alterna o estado do LED
              gpio_put(LED_RGB_G, led_green_state);
              printf("Estado do LED VERDE: %s\n", led_green_state ? "LIGADO" : "DESLIGADO");
                if (led_green_state == 1)
                {  
                  ssd1306_fill(&ssd, false);
                  ssd1306_send_data(&ssd);             
                  ssd1306_draw_string(&ssd, "LED VERDE ON ", 8, 10); // Desenha estado do LED verde
                  ssd1306_send_data(&ssd); // Atualiza o display 
                
                } else {
                  ssd1306_fill(&ssd, false);
                  ssd1306_send_data(&ssd);
                  ssd1306_draw_string(&ssd, "LED VERDE OFF ", 8, 10); // Desenha estado do LED verde
                  ssd1306_send_data(&ssd); // Atualiza o display
                }
            }
      
            else if (gpio_get(BOTAO_B)==0)
            {
              led_blue_state = !led_blue_state; // Alterna o estado do LED
              gpio_put(LED_RGB_B, led_blue_state);
              printf("Estado do LED AZUL: %s\n", led_blue_state ? "LIGADO" : "DESLIGADO");
                if (led_blue_state == 1)
                {
                  ssd1306_fill(&ssd, false);
                  ssd1306_send_data(&ssd);
                  ssd1306_draw_string(&ssd, "LED AZUL ON ", 8, 48); // Desenha estado do LED azul
                  ssd1306_send_data(&ssd); // Atualiza o display 
                } else {
                  ssd1306_fill(&ssd, false);
                  ssd1306_send_data(&ssd);
                  ssd1306_draw_string(&ssd, "LED AZUL OFF ", 8, 48); // Desenha estado do LED azul
                  ssd1306_send_data(&ssd); // Atualiza o display
                } 
            }
          }
        }

void desenha_caractere(char c)
{
    ssd1306_draw_string(&ssd, &c, 20, 30); // Desenha o caractere recebido no display
    ssd1306_send_data(&ssd); // Atualiza o display
}


// Loop principal
int main() {
    stdio_init_all(); // Inicializa UART
    
    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA); // Pull up the data line
    gpio_pull_up(I2C_SCL); // Pull up the clock line
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display

    ssd1306_fill(&ssd, false); // limpa o display
    ssd1306_send_data(&ssd);
   
    uart_init(uart0, 115200);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    i2c_init(i2c0, 400 * 1000); // Inicializa I2C com 400kHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_draw_string(&ssd, "Ola ! Aperte ", 8, 10); // Desenha estado do LED verde (inicial)
    ssd1306_draw_string(&ssd, " um dos botoes ", 8, 20); // Desenha estado do LED azul (inicial)
    ssd1306_send_data(&ssd); // Atualiza o display
  

// inicialização da matriz de LED 5x5
PIO pio = pio0;
    bool ok;
    uint32_t valor_led;
    double r , g , b ;

    r = 1;
    g = 1;
    b = 0;

    ok = set_sys_clock_khz(128000, false);
    stdio_init_all();

    uint offset = pio_add_program(pio, &communication_program);
    uint sm = pio_claim_unused_sm(pio, true);
    communication_program_init(pio, sm, offset, OUT_PIN);

    gpio_init(LED_RGB_G);
    gpio_init(LED_RGB_B);
  
    gpio_set_dir(LED_RGB_G, GPIO_OUT);
    gpio_set_dir(LED_RGB_B, GPIO_OUT);

    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);
    gpio_set_irq_enabled(BOTAO_A, GPIO_IRQ_EDGE_FALL, true);

    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_B);
    gpio_set_irq_enabled(BOTAO_B, GPIO_IRQ_EDGE_FALL, true);
    
    gpio_set_irq_callback(&gpio_irq_handler);
    irq_set_enabled(IO_IRQ_BANK0, true);

// Inicializa a UART
uart_init(UART_ID, BAUD_RATE);

// Configura os pinos GPIO para a UART
gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART); // Configura o pino 0 para TX
gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART); // Configura o pino 1 para RX

// Mensagem inicial
const char *init_message = "Ola, Seja bem vindo\r\n"
                           "Digite uma letra ou um numero de 0 a 9\r\n";
uart_puts(UART_ID, init_message);

    while (true) {
        {
            if (uart_is_readable(UART_ID)) {
            // Lê um caractere da UART
            char c = uart_getc(UART_ID);

                if (scanf("%c", &c) == 1)
                { // Lê caractere da entrada padrão
                 
                    printf("Recebido: '%c'\n", c);
    
                    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
                    {
                        desenha_caractere(c);
                    }
                    else if (c >= '0' && c <= '9')
                    {
                        desenha_caractere(c);
                        int num = c - '0';
                        switch (num) {
                            case 0: matriz_atual = matriz_0; break;
                            case 1: matriz_atual = matriz_1; break;
                            case 2: matriz_atual = matriz_2; break;
                            case 3: matriz_atual = matriz_3; break;
                            case 4: matriz_atual = matriz_4; break;
                            case 5: matriz_atual = matriz_5; break;
                            case 6: matriz_atual = matriz_6; break;
                            case 7: matriz_atual = matriz_7; break;
                            case 8: matriz_atual = matriz_8; break;
                            case 9: matriz_atual = matriz_9; break;
                        }              
                        desenho_pio(matriz_atual, valor_led, pio, sm, r, g, b);
                    
                    }
                }
                 // Envia de volta o caractere lido (eco)
            uart_putc(UART_ID, c);

            // Envia uma mensagem adicional para cada caractere recebido
            uart_puts(UART_ID, " <- Caracter Digitado\r\n");
            }
        }
        sleep_ms(40);
    }
    return 0;
 }

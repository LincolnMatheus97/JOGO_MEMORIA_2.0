#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "inc/matriz_LED/matriz_LED.h"
#include "inc/display_OLED/display_OLED.h"
#include "inc/buzzer/buzzer.h"
#include "inc/logica_jogo/logica_jogo.h"
#include "inc/joystick/joystick.h"

// Função principal
int main()
{
    // Inicializa as entradas e saídas do Pico SDK
    stdio_init_all();

    // Inicializa a matriz de LED's
    npInit(LED_PIN);
    npClear();
    npWrite();

    // Inicializa ADC para leitura do Joystick.
    adc_init();
    adc_gpio_init(JOY_X_PIN);
    adc_gpio_init(JOY_Y_PIN);

    // Inicializa botão A e B
    gpio_init(BT_B_PIN);
    gpio_set_dir(BT_B_PIN, GPIO_IN);
    gpio_pull_up(BT_B_PIN);
    gpio_init(BT_A_PIN);
    gpio_set_dir(BT_A_PIN, GPIO_IN);
    gpio_pull_up(BT_A_PIN);

    // Inicializa display OLED
    inicializacao_display();

    // Inicializa o buzzer
    inicializar_pwm_buzzer(PINO_BUZZER);

    // Inicializa o jogo
    inicializar_jogo();

    while (true)
    {
        npClear();

        // Exibir LEDs acertados
        for (int i = 0; i < LED_COUNT; i++)
        {
            if (acertos[i])
            {
                npSetLED(i, 0, 100, 0);
            }
        }

        // Exibir posição atual do LED branco
        npSetLED(pegar_indice_LED(led_x, led_y), 100, 100, 100);
        npWrite();

        // Verificar se o jogador acertou a sequência de LEDs
        if (debounce_botao(BT_B_PIN))
        {
            verificar_jogada();
        }

        sleep_ms(100);
    }
}
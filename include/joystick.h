#ifndef JOYSTICK_H // Include guard para evitar múltiplas inclusões
#define JOYSTICK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hardware/adc.h"
#include "hardware/timer.h"
#include "include/logica_jogo.h"
#include "include/matriz_LED.h"

// Definição dos pinos do Joystick, tamanho da Matriz de LEDs
#define JOY_X_PIN 26
#define JOY_Y_PIN 27
#define MATRIZ_LINHA 5
#define MATRIZ_COLUNA 5

int led_x = 0, led_y = 0;                // Posição do LED selecionado
static absolute_time_t ultimo_movimento; // Tempo do último movimento do Joystick

// Função callback de manipular a interrupção do temporizador do joystick
bool temporizador_joystick(struct repeating_timer *t)
{
    adc_select_input(0);
    uint16_t valor_x = adc_read();
    adc_select_input(1);
    uint16_t valor_y = adc_read();

    absolute_time_t agora = get_absolute_time();

    if (absolute_time_diff_us(ultimo_movimento, agora) > 200000)
    {
        bool movimento = false;

        if (valor_x > 4000 && led_y < MATRIZ_LINHA - 1)
        {
            led_y++; // Baixo
            movimento = true;
        }
        else if (valor_x < 1000 && led_y > 0)
        {
            led_y--; // Cima
            movimento = true;
        }

        if (valor_y > 4000 && led_x < MATRIZ_COLUNA - 1)
        {
            led_x++; // Direita
            movimento = true;
        }
        else if (valor_y < 1000 && led_x > 0)
        {
            led_x--; // Esquerda
            movimento = true;
        }

        // Atualiza o tempo do último movimento apenas se houver movimento lido
        if (movimento)
        {
            ultimo_movimento = agora;
        }
    }

    return true;
}

// Inicializa o temporizador de hardware para verificar o joystick
void inicializar_joystick()
{
    static struct repeating_timer tempo;
    ultimo_movimento = get_absolute_time();

    // Configura o temporizador para disparar a cada 50ms
    add_repeating_timer_ms(50, temporizador_joystick, NULL, &tempo);
}

#endif
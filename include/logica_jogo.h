#ifndef JOGO_MEMORIA_H // Include guard para evitar múltiplas inclusões
#define JOGO_MEMORIA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/timer.h"
#include "include/matriz_led.h"
#include "include/display_oled.h"
#include "include/buzzer.h"
#include "include/joystick.h"

// Definição dos pinos do Botões e tamanho Matriz de LEDs
#define BT_A_PIN 5
#define BT_B_PIN 6
#define MATRIZ_LINHA 5
#define MATRIZ_COLUNA 5

// Variáveis do jogo.
int sequencia[5];                        // Sequência de LEDs
int tamanho_sequencia = 1;               // Começamos com 3 LEDs
int indice_jogador = 0;                  // Índice do jogador na sequência
int nivel = 1;                           // Nível do jogador
int vida_jogador = 2;                    // Vidas do jogador
bool acertos[LED_COUNT] = {false};       // LEDs acertados

// Função para debouncing dos botões.
bool debounce_botao(uint pin)
{
    static uint32_t ultimo_pressionamento = 0;
    uint32_t pressionando = to_ms_since_boot(get_absolute_time());

    if (gpio_get(pin) == 0)
    {
        if (pressionando - ultimo_pressionamento > 300)
        {
            ultimo_pressionamento = pressionando;
            sleep_ms(50);
            return true;
        }
    }
    return false;
}

// Converte coordenadas (x, y) em um índice para a matriz de LEDs.
int pegar_indice_LED(int coord_x, int coord_y)
{
    coord_x = 4 - coord_x; // Inverte a coluna
    if (coord_y % 2 == 0)
    {
        return coord_y * 5 + coord_x;
    }
    else
    {
        return coord_y * 5 + (4 - coord_x);
    }
}

// Gera uma sequência de LEDs aleatória.
void sequencia_aleatoria_LED()
{
    for (int i = 0; i < tamanho_sequencia; i++)
    {
        int x = rand() % MATRIZ_COLUNA;
        int y = rand() % MATRIZ_LINHA;
        sequencia[i] = pegar_indice_LED(x, y);
    }
}

// Exibe a sequência de LEDs com Temporizadores de software.
void exibir_sequencia()
{

    absolute_time_t tempo_atual = get_absolute_time();

    for (int i = 0; i < tamanho_sequencia; i++)
    {
        npClear();
        npSetLED(sequencia[i], 0, 0, 100);
        npWrite();

        while (absolute_time_diff_us(tempo_atual, get_absolute_time()) < 500000)
        {
        } // Espera 500ms sem bloquear
        tempo_atual = get_absolute_time();

        npClear();
        npWrite();

        while (absolute_time_diff_us(tempo_atual, get_absolute_time()) < 250000)
        {
        } // Espera 250ms sem bloquear
        tempo_atual = get_absolute_time();
    }
}

// Indica erro na sequência  com temporizadores de software.
void indicar_erro()
{
    absolute_time_t inicio = get_absolute_time();

    for (int i = 0; i < 3; i++)
    {
        // Acende os LEDs vermelhos
        npClear();
        for (int j = 0; j < LED_COUNT; j++)
        {
            if (j == 0 || j == 4 || j == 6 || j == 8 || j == 12 || j == 16 || j == 18 || j == 20 || j == 24)
            {
                npSetLED(j, 100, 0, 0);
            }
        }
        npWrite();

        // Espera 200ms sem travar o jogo
        while (absolute_time_diff_us(inicio, get_absolute_time()) < 200000)
        {
        }

        inicio = get_absolute_time(); // Atualiza o tempo de referência

        // Apaga os LEDs
        npClear();
        npWrite();

        // Espera mais 200ms sem travar
        while (absolute_time_diff_us(inicio, get_absolute_time()) < 200000)
        {
        }

        inicio = get_absolute_time(); // Atualiza o tempo de referência
    }
}

// Indica sucesso no sequência com temporizadores de software.
void indicar_acerto()
{
    absolute_time_t inicio = get_absolute_time();

    for (int i = 0; i < 3; i++)
    {
        // Acende os LEDs verdes
        npClear();
        for (int j = 0; j < LED_COUNT; j++)
        {
            if (j == 3 || j == 5 || j == 7 || j == 11 || j == 19)
            {
                npSetLED(j, 0, 100, 0);
            }
        }
        npWrite();

        // Espera 200ms sem travar
        while (absolute_time_diff_us(inicio, get_absolute_time()) < 200000)
        {
        }

        inicio = get_absolute_time(); // Atualiza o tempo de referência

        // Apaga os LEDs
        npClear();
        npWrite();

        // Espera mais 200ms sem travar
        while (absolute_time_diff_us(inicio, get_absolute_time()) < 200000)
        {
        }

        inicio = get_absolute_time(); // Atualiza o tempo de referência
    }
}

// Indica vitoria no jogo com temporizadores de software.
void indicar_vitoria()
{
    iniciar_melodia();
    while (!debounce_botao(BT_A_PIN))
    {
        absolute_time_t tempo_inicio = get_absolute_time();
        while (absolute_time_diff_us(tempo_inicio, get_absolute_time()) < 10000) // 10ms
        {
            // Pisca os LEDs
            npClear();
            for (int j = 0; j < LED_COUNT; j++)
            {
                int aleatorio = rand() % 2 == 0 ? 0 : 100;
                int aleatorio2 = rand() % 2 == 0 ? 0 : 100;
                int aleatorio3 = rand() % 2 == 0 ? 0 : 100;

                // Se todos os aleatórios forem 0, muda para 1 para evitar LEDs Apagados e Brancos
                if (aleatorio == 0 && aleatorio2 == 0 && aleatorio3 == 0)
                {
                    aleatorio = 100;
                }
                npSetLED(j, aleatorio, aleatorio2, aleatorio3);
            }
            npWrite();
        }

        tempo_inicio = get_absolute_time();
        while (absolute_time_diff_us(tempo_inicio, get_absolute_time()) < 100000) // 100ms
        {
            // Apaga os LEDs
            npClear();
            npWrite();
        }
    }
}

// Reseta o jogo.
void reinicializar_jogo()
{
    nivel = 1;
    tamanho_sequencia = 1;
    indice_jogador = 0;
    vida_jogador = 3;

    memset(acertos, 0, sizeof(acertos)); // Zera os acertos
    parar_melodia();

    sleep_ms(500);
    char nivelMsg[20];
    sprintf(nivelMsg, "Nivel:%d Vida:%d", nivel, vida_jogador);
    display_mensagem(nivelMsg, "", "Memorize os LEDs", "Mova o Joystick", "", "Aperte o Botao B", "para confirmar", "o LED", true);
    sleep_ms(2200);

    sequencia_aleatoria_LED();
    exibir_sequencia();
}

// Reseta a jogada
void resetar_jogada()
{
    indice_jogador = 0;                  // Reseta o índice do jogador na sequência
    memset(acertos, 0, sizeof(acertos)); // Zera os acertos

    sleep_ms(500);
    char nivelMsg[20];
    sprintf(nivelMsg, "Nivel:%d Vida:%d", nivel, vida_jogador);
    display_mensagem(nivelMsg, "", "Memorize os LEDs", "Mova o Joystick", "", "Aperte o Botao B", "para confirmar", "o LED", true);
    sleep_ms(2200);

    exibir_sequencia(); // Exibe novamente a sequência atual
}

// Função para inicializar o jogo
void inicializar_jogo()
{
    // Inicializa o jogo da memória com uma semente aleatória
    uint32_t seed = time(NULL) ^ adc_read(); // Combina tempo com leitura do ADC
    srand(seed);

    // Inicializa a melodia
    iniciar_melodia();

    npWrite();
    npClear();
    display_mensagem("Bem Vindo ao", "Jogo da Memoria.", "", "Exercite a mente", "e divirta-se", "", "", "", true);
    sleep_ms(4000);
    display_mensagem("Grave a ordem", "certa dos LEDs", "para ganhar.", "", "Aperte Botao A", "Para Iniciar", "o jogo.", "", true);

    // Aguarda o jogador pressionar o botão A para iniciar o jogo.
    while (!debounce_botao(BT_A_PIN))
    {
    }

    // Inicializa o joystick
    inicializar_joystick();

    // Inicializa o jogo
    reinicializar_jogo();
}

// Verifica se o jogador acertou a sequência.
void verificar_jogada()
{
    // Pega o índice do LED selecionado pelo jogador
    int indice = pegar_indice_LED(led_x, led_y);

    // Se o jogador acertou o LED
    if (indice == sequencia[indice_jogador])
    {
        beep_suave(PINO_BUZZER, 250); // Toca um beep suave
        restaurar_pwm_melodia();      // Restaura a configuração do PWM para a melodia
        acertos[indice] = true;
        npSetLED(indice, 0, 100, 0);
        npWrite();
        indice_jogador++;

        // Se o jogador acertou toda a sequência
        if (indice_jogador == tamanho_sequencia)
        {
            // Se o jogador chegar ao nível 5, ele venceu
            if (nivel == 5)
            {
                display_mensagem("Parabens", "Voce venceu!", "Zerou o Game", "", "Aperte Botao A", "para reiniciar", "", "", true);
                indicar_vitoria();
                inicializar_jogo();
                return;
            }

            indicar_acerto();
            display_mensagem("Nivel Concluido", "", "Se esta pronto", "Aperte Botao A", "", "Para iniciar ", "nova sequencia", "", true);

            while (!debounce_botao(BT_A_PIN))
            {
            }

            nivel++;
            tamanho_sequencia++;
            indice_jogador = 0;
            memset(acertos, 0, sizeof(acertos)); // Zera os acertos

            sleep_ms(500);
            char nivelMsg[20];
            sprintf(nivelMsg, "Nivel:%d Vidas:%d", nivel, vida_jogador);
            display_mensagem(nivelMsg, "", "Memorize os LEDs", "Mova o Joystick", "", "Aperte o Botao B", "para confirmar", "o LED", true);
            sleep_ms(2500);
            sequencia_aleatoria_LED();
            exibir_sequencia();
        }
    }
    // Se o jogador errou o LED
    else
    {
        beep_grave(PINO_BUZZER, 250); // Toca um beep grave
        restaurar_pwm_melodia();      // Restaura a configuração do PWM para a melodia
        indicar_erro();
        vida_jogador--;

        if (vida_jogador > 0)
        {
            display_mensagem("Errou, Perdeu", "Uma Vida", "", "Aperte Botao A", "", "para tentar", "novamente", "", true);
            while (!debounce_botao(BT_A_PIN))
            {
            }
            resetar_jogada();
        }
        else
        {
            display_mensagem("Game Over, Nao", "Tem mais Vidas", "", "Aperte Botao A", "", "para reiniciar", "o jogo", "", true);
            while (!debounce_botao(BT_A_PIN))
            {
            }
            reinicializar_jogo();
        }
    }
}

#endif
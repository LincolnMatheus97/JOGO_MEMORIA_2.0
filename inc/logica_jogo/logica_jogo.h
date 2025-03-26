#ifndef LOGICA_JOGO_H // Include guard para evitar múltiplas inclusões
#define LOGICA_JOGO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/timer.h"
#include "inc/matriz_LED/matriz_LED.h"
#include "inc/display_OLED/display_oled.h"
#include "inc/buzzer/buzzer.h"
#include "inc/joystick/joystick.h"

// Definição dos pinos do Botões e tamanho Matriz de LEDs
#define BT_A_PIN 5
#define BT_B_PIN 6
#define MATRIZ_LINHA 5
#define MATRIZ_COLUNA 5

// Variáveis do jogo.
extern int sequencia[5];                    // Sequência de LEDs
extern int tamanho_sequencia;               // Começamos com 1 LED
extern int indice_jogador;                  // Índice do jogador na sequência
extern int nivel;                           // Nível do jogador
extern int vida_jogador;                    // Vidas do jogador
extern bool acertos[LED_COUNT];             // LEDs acertados

// Função para debouncing dos botões
bool debounce_botao(uint pin);

// Converter as coordenadas (x, y) em um índice para a matriz de LEDs
int pegar_indice_LED(int coord_x, int coord_y);

// Gera uma sequência de LEDs aleatória
void sequencia_aleatoria_LED();

// Exibe a sequência de LEDs com temporizadores de software
void exibir_sequencia();

// Indica erro na sequência com temporizadores de software
void indicar_erro();

// Indica sucesso na sequência com temporizadores de software
void indicar_acerto();

// Indica vitória no jogo com temporizadores de software
void indicar_vitoria();

// Reseta o jogo
void reinicializar_jogo();

// Reseta a jogada
void resetar_jogada();

// Inicializa o jogo
void inicializar_jogo();

// Verifica se o jogador acertou a sequência
void verificar_jogada();

#endif
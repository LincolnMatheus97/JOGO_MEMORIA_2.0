#ifndef JOYSTICK_H // Include guard para evitar múltiplas inclusões
#define JOYSTICK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hardware/adc.h"
#include "hardware/timer.h"
#include "inc/logica_jogo/logica_jogo.h"
#include "inc/matriz_LED/matriz_LED.h"

// Definição dos pinos do Joystick, tamanho da Matriz de LEDs
#define JOY_X_PIN 26
#define JOY_Y_PIN 27
#define MATRIZ_LINHA 5
#define MATRIZ_COLUNA 5

// Posição do LED selecionado
extern int led_x, led_y;

// Função de callback de manipular a interrupção do temporizador do joystick
bool temporizador_joystick(struct repeating_timer *t);

// incializa o joystick com o temporizador
void inicializar_joystick();

#endif
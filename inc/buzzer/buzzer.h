#ifndef BUZZER_H
#define BUZZER_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Configuração do pino do buzzer e configuração da frequência do buzzer (em Hz)
#define PINO_BUZZER 21
#define FREQUENCIA_BUZZER 100

// Função para inicializar o PWM do buzzer
void inicializar_pwm_buzzer(uint pin);

// Função de callback de manipular a interrupção do temporizador para tocar notas da melodia
bool tocar_nota(struct repeating_timer *t);

// Função para inciar a melodia
void iniciar_melodia();

// Função para parar a melodia
void parar_melodia();

// Função para restaurar o PWM do buzzer 
void restaurar_pwm_melodia();

// Funções para tocar sons de alerta suave
void beep_suave(uint pin, uint duration_ms);

// Funções para tocar sons de alerta grave
void beep_grave(uint pin, uint duration_ms);

#endif
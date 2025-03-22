#ifndef BUZZER_H // Include guard para evitar múltiplas inclusões
#define BUZZER_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Configuração do pino do buzzer e configuração da frequência do buzzer (em Hz)
#define PINO_BUZZER 21
#define FREQUENCIA_BUZZER 100

static struct repeating_timer tempo_melodia;    
static int indice_melodia = 0;               
static bool tocando_melodia = false;

// Definição de uma função para inicializar o PWM no pino do buzzer
void inicializar_pwm_buzzer(uint pin)
{
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (FREQUENCIA_BUZZER * 4096));
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(pin, 0);
}

// Notas musicais para a música
const uint notas_melodia[] = {
    262, 294, 330, 349, 392, 440, 494, 523, 
    0,                                      
    392, 349, 330, 294, 262                 
};

// Duração de cada nota (em ms)
const uint duracao_notas[] = {
    500, 500, 500, 500, 500, 500, 500, 500,
    200,
    500, 500, 500, 500, 500};

// Função de callback de manipular a interrupção do temporizador para tocar a melodia
bool tocar_nota(struct repeating_timer *t)
{
    if (!tocando_melodia)
        return false;

    if (indice_melodia >= sizeof(notas_melodia) / sizeof(notas_melodia[0])) 
    {
        indice_melodia = 0;
    }

    uint freq = notas_melodia[indice_melodia];    
    uint duracao = duracao_notas[indice_melodia]; 

    if (freq == 0)
    {
        pwm_set_gpio_level(PINO_BUZZER, 0);
    }
    else
    {
        uint slice_num = pwm_gpio_to_slice_num(PINO_BUZZER);
        uint32_t clock_freq = clock_get_hz(clk_sys);
        uint32_t top = clock_freq / freq - 1;
        pwm_set_wrap(slice_num, top);
        pwm_set_gpio_level(PINO_BUZZER, top / 2);            
    }

    indice_melodia++; 
    return true;      
}

// Função para iniciar a melodia com temporizador
void iniciar_melodia()
{
    if (tocando_melodia)
        return;

    indice_melodia = 0;
    tocando_melodia = true;

    add_repeating_timer_ms(300, tocar_nota, NULL, &tempo_melodia);
}

// Função para parar a melodia
void parar_melodia()
{
    tocando_melodia = false;
    pwm_set_gpio_level(PINO_BUZZER, 0); 
}

// Função para restaurar a configuração do PWM para a melodia
void restaurar_pwm_melodia()
{
    uint slice_num = pwm_gpio_to_slice_num(PINO_BUZZER);                                
    pwm_config config = pwm_get_default_config();                                       
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (FREQUENCIA_BUZZER * 4096)); 
    pwm_init(slice_num, &config, true);                                                 
    pwm_set_gpio_level(PINO_BUZZER, 0);                                                 
}

// Definição de uma função para emitir um beep suave
void beep_suave(uint pin, uint duration_ms)
{
    uint slice_num = pwm_gpio_to_slice_num(pin);

    pwm_config config = pwm_get_default_config();                          
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (4000 * 4096));
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(pin, 2048); 
    sleep_ms(duration_ms);         
    pwm_set_gpio_level(pin, 0);    
}

// Definição de uma função para emitir um beep grave
void beep_grave(uint pin, uint duration_ms)
{
    uint slice_num = pwm_gpio_to_slice_num(pin);

    pwm_config config = pwm_get_default_config();                         
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (500 * 4096)); 
    pwm_init(slice_num, &config, true);                                   
    pwm_set_gpio_level(pin, 2048); 
    sleep_ms(duration_ms);         
    pwm_set_gpio_level(pin, 0);    
}

#endif
#ifndef MATRIZ_LED_H // Include guard para evitar múltiplas inclusões
#define MATRIZ_LED_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2818b.pio.h"

// Definição do número dos pinos de LEDs e do pino de controle
#define LED_COUNT 25
#define LED_PIN 7

// Definição da struct de pixel GRB
struct pixel_t
{
    uint8_t G, R, B;
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t;

// Declaração do buffer de pixels que formam a matriz e variáveis para uso da máquina PIO.
extern npLED_t leds[LED_COUNT];
extern PIO np_pio;
extern uint sm;

// Inicializa a máquina PIO para controle da matriz de LEDs.
void npInit(uint pin);

// Ajuste de gamma para correção de brilho
uint8_t correcao_gamma(uint8_t value);

// Atribui uma cor RGB a um LED.
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b);

// Limpa o buffer de pixels.
void npClear();

// Escreve os dados do buffer nos LEDs.
void npWrite();

#endif
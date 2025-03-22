#ifndef DISPLAY_OLED_H // Include guard para evitar múltiplas inclusões
#define DISPLAY_OLED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "include/ssd1306.h"

// Definição dos pinos I2C
const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

// Estrutura do display OLED
ssd1306_t ssd;

// Buffer do OLED
static uint8_t ssd_buffer[ssd1306_buffer_length];
static struct render_area frame_area = {
    .start_column = 0,
    .end_column = ssd1306_width - 1,
    .start_page = 0,
    .end_page = ssd1306_n_pages - 1};

// Display de mensagem no OLED
void display_mensagem(const char *linha1, const char *linha2, const char *linha3, const char *linha4, const char *linha5,
                      const char *linha6, const char *linha7, const char *linha8, bool limpar)
{
    if (limpar)
    {
        memset(ssd_buffer, 0, ssd1306_buffer_length);
    }

    int pos_x = 0; // Iniciar o texto desde o começo da tela

    ssd1306_draw_string(ssd_buffer, pos_x, 0, (char *)linha1);
    ssd1306_draw_string(ssd_buffer, pos_x, 8, (char *)linha2);
    ssd1306_draw_string(ssd_buffer, pos_x, 16, (char *)linha3);
    ssd1306_draw_string(ssd_buffer, pos_x, 24, (char *)linha4);
    ssd1306_draw_string(ssd_buffer, pos_x, 32, (char *)linha5);
    ssd1306_draw_string(ssd_buffer, pos_x, 40, (char *)linha6);
    ssd1306_draw_string(ssd_buffer, pos_x, 48, (char *)linha7);
    ssd1306_draw_string(ssd_buffer, pos_x, 56, (char *)linha8);

    render_on_display(ssd_buffer, &frame_area);
}

// Inicialização do display OLED
void inicializacao_display()
{
    i2c_init(i2c1, ssd1306_i2c_clock * 5000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_init();

    // Calcular a área de renderização
    calculate_render_area_buffer_length(&frame_area);

    memset(ssd_buffer, 0, ssd1306_buffer_length);
    render_on_display(ssd_buffer, &frame_area);
}

#endif
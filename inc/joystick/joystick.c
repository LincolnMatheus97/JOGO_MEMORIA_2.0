#include "inc/joystick/joystick.h"

int coord_x_matriz = 0;                     // Posição da coordenada x na matriz de LED 
int coord_y_matriz = 0;                     // Posição da coordenada y na matriz de LED
static absolute_time_t ultimo_movimento;    // Tempo do último movimento do Joystick

// Função callback de manipular a interrupção do movimento do joystick
bool movimento_joystick(struct repeating_timer *t)
{
    adc_select_input(0);
    uint16_t valor_lido_x = adc_read();
    adc_select_input(1);
    uint16_t valor_lido_y = adc_read();

    absolute_time_t agora = get_absolute_time();

    if (absolute_time_diff_us(ultimo_movimento, agora) > 200000) // 200ms
    {
        bool movimento = false;

        if (valor_lido_x > 4000 && coord_y_matriz < MATRIZ_LINHA - 1)
        {
            coord_y_matriz++; // Baixo
            movimento = true;
        }
        else if (valor_lido_x < 1000 && coord_y_matriz > 0)
        {
            coord_y_matriz--; // Cima
            movimento = true;
        }

        if (valor_lido_y > 4000 && coord_x_matriz < MATRIZ_COLUNA - 1)
        {
            coord_x_matriz++; // Direita
            movimento = true;
        }
        else if (valor_lido_y < 1000 && coord_x_matriz > 0)
        {
            coord_x_matriz--; // Esquerda
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
    add_repeating_timer_ms(50, movimento_joystick, NULL, &tempo);
}
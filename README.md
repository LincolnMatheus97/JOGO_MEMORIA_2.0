# 🕹️ Sistema Embarcado - Jogo da Memória 2.0

Este é um projeto de um **Jogo da Memória** desenvolvido na placa didática **BitDogLab** utilizando um **Raspberry Pi Pico W**. O jogo utiliza a matriz de LEDs endereçáveis, display OLED, joystick, botões fisícos e buzzer para proporcionando uma experiência interativa, divertida e educativa para demonstrar os conhecimentos adquiridos na residência de sistemas embarcados **EmbarcaTech**.

⚠️ **Atenção**: Este projeto utiliza a versão **1.5.1** do **Pico SDK**. Certifique-se de estar utilizando a versão correta ao importar e compilar o código.

## 🔗 Funcionalidades

- Interface com **matriz de LED** para exibição do jogo
- Controle por **joystick** e **botões** para seleção do LED correto
- Exibição de mensagens em **display OLED**, como instruções e alertas
- Sinais sonoros pelo **buzzer**, para acertos e erros, e uma melodia tema do jogo
- Código modularizado, organizado em arquivos `.h` e `.c`

## 🛠️ Tecnologias e Ferramentas Utilizadas

- **Linguagem**: C
- **Placa**: BitDogLab com Raspberry Pi Pico W
- **IDE**: VS Code
- **Bibliotecas**: 
   - Bibliotecas padrão do C: stdio.h, stdlib.h, string.h, time.h, e ctype.h.
   - Bibliotecas do SDK do Raspberry Pi Pico: pico/stdlib.h, pico/binary_info.h, hardware/pio.h, hardware/clocks.h, hardware/adc.h, hardware/pwm.h e hardware/i2c.
   - Bibliotecas específicas do projeto: inc/matriz_LED/matriz_LED.h, inc/display_OLED/display_OLED.h, inc/display_OLED/ssd1306.h, inc/buzzer/buzzer.h, inc/logica_jogo/logica_jogo.h, inc/joystick/joystick.h e ws2818b.pio.h

## 📦 Estrutura do Projeto

```
JOGO_DA_MEMORIA_2.0/

├── .vscode/   # Configurações do VS Code 
├── build/     # Pasta de build 
├── inc/       # Arquivos de cabeçalho (.h) 
│ ├── buzzer/              # Configurações do Buzzer
│ │ ├── buzzer.c
│ │ ├── buzzer.h
│ ├── display_OLED/        # Configurações do display OLED
│ │ ├── display_OLED.c
│ │ ├── display_OLED.h
│ │ ├── ssd1306_font.h
│ │ ├── ssd1306_i2c.c.c
│ │ ├── ssd1306_i2c.h
│ │ ├── ssd1306.h
│ ├── joystick/            # Configurações do joystick
│ │ ├── joystick.c
│ │ ├── joystick.h
│ ├── logica_jogo/         # Configurações da logica do jogo
│ │ ├── logica_jogo.c
│ │ ├── logica_jogo.h
│ ├── matriz_LED/          # Configurações do matriz de LED
│ │ ├── matriz_LED.c
│ │ ├── matriz_LED.h
├── src/
│ ├── jogo_memoria_2.0.c    # Lógica Principal do projeto
├── .gitignore              # Arquivos ignorados pelo Git 
├── CMakeLists.txt          # Configuração do CMake 
├── pico_sdk_import.cmake   # Importação do Pico SDK 
├── README.md               # Documentação principal  
├── ws2818b.pio             # Maquina PIO para a configuração de comunicação para matriz de LED
```

## ⚙️ Como Executar

1. Clone o repositório:
   ```bash
   git clone https://github.com/LincolnMatheus97/JOGO_MEMORIA_2.0.git
   ```
2. Certifique-se de estar utilizando a versão **1.5.1** do **Pico SDK**.
3. Compile o código.
4. Coloque a placa **BitDogLab** no modo BOOTSEL, e conecte ao computador.
5. De Run no projeto e teste na placa.


## ▶️ Video Demonstrativo Do Projeto

<a href="https://youtu.be/T43sCktJM6U?si=tvjUCiUYUKlJvNsg">
  <img src="https://img.icons8.com/?size=100&id=108794&format=png&color=000000" alt="Video Demonstrativo" width="50" />
</a><br>
Clique no ícone acima para assistir ao vídeo demonstrativo.

---

Desenvolvido por [Lincoln Matheus](https://github.com/LincolnMatheus97).
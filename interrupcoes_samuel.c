#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#include "ws2818b.pio.h"

#define CONTADOR_LED 25
#define PINO_MATRIZ_LED 7

#define led_vermelho 13
#define button_a 5
#define button_b 6

struct pixel_t
{
	uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t LED_da_matriz;

// Declaração do buffer de pixels que formam a matriz.
LED_da_matriz leds[CONTADOR_LED];

// Variáveis para uso da máquina PIO.
PIO maquina_pio;
uint variavel_maquina_de_estado;

//-----PROTÓTIPOS-----
void inicializacao_maquina_pio(uint pino);
void iniciar_gpio();
void cor_ao_led(const uint indice, const uint8_t r, const uint8_t g, const uint8_t b, uint8_t intensidade);
void apagar_buffer();
void carregar_o_buffer();
void desenho(int num);
void piscar_led();
// ------MATRIZ-----
int tamanho_matriz = 5;
// Matriz 5x5
uint matrizint[5][5] = {
		{24, 23, 22, 21, 20},
		{15, 16, 17, 18, 19},
		{14, 13, 12, 11, 10},
		{5, 6, 7, 8, 9},
		{4, 3, 2, 1, 0}};


//-----VARIÁVEIS-----
static volatile uint32_t last_time = 0;
int _intensidade_ = 255;
int indice = 0;


//-----FUNÇÕES COMPLEMENTARES-----
static void interrupcao(uint gpio, uint32_t events);

void inicializacao_maquina_pio(uint pino)
{
	uint programa_pio, i;
	// Cria programa PIO.
	programa_pio = pio_add_program(pio0, &ws2818b_program);
	maquina_pio = pio0;

	// Toma posse de uma máquina PIO.
	variavel_maquina_de_estado = pio_claim_unused_sm(maquina_pio, false);
	if (variavel_maquina_de_estado < 0)
	{
		maquina_pio = pio1;
		variavel_maquina_de_estado = pio_claim_unused_sm(maquina_pio, true); // Se nenhuma máquina estiver livre, panic!
	}

	// Inicia programa na máquina PIO obtida.
	ws2818b_program_init(maquina_pio, variavel_maquina_de_estado, programa_pio, pino, 800000.f);

	// Limpa buffer de pixels.
	for (i = 0; i < CONTADOR_LED; ++i)
	{
		leds[i].R = 0;
		leds[i].G = 0;
		leds[i].B = 0;
	}
}


void cor_ao_led(const uint indice, const uint8_t r, const uint8_t g, const uint8_t b, uint8_t intensidade)
{

	if (intensidade > 255)
		intensidade = 255;
	if (intensidade < 0)
		intensidade = 0;

	// Ajusta os valores de RGB conforme a intensidade escolhida
	leds[indice].R = (r * intensidade);
	leds[indice].G = (g * intensidade);
	leds[indice].B = (b * intensidade);
}

void apagar_buffer()
{
	for (uint i = 0; i < CONTADOR_LED; ++i)
	{
		cor_ao_led(i, 0, 0, 0, 0);
	}
}

void carregar_o_buffer()
{
	// Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
	for (uint i = 0; i < CONTADOR_LED; ++i)
	{
		pio_sm_put_blocking(maquina_pio, variavel_maquina_de_estado, leds[i].G);
		pio_sm_put_blocking(maquina_pio, variavel_maquina_de_estado, leds[i].R);
		pio_sm_put_blocking(maquina_pio, variavel_maquina_de_estado, leds[i].B);
	}
	sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}

void iniciar_gpio()
{
    gpio_init(led_vermelho);
    gpio_set_dir(led_vermelho, GPIO_OUT);

    gpio_init(button_a);
    gpio_set_dir(button_a, GPIO_IN);
    gpio_pull_up(button_a);

    gpio_init(button_b);
    gpio_set_dir(button_b, GPIO_IN);
    gpio_pull_up(button_b);

    gpio_set_irq_enabled_with_callback(button_a, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &interrupcao);
    gpio_set_irq_enabled_with_callback(button_b, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &interrupcao);
}

void interrupcao(uint gpio, uint32_t events)
{

	// Obtém o tempo atual em microssegundos
	uint32_t current_time = to_us_since_boot(get_absolute_time());
	// Verifica se passou tempo suficiente desde o último evento
	if (current_time - last_time > 200000) // 200 ms de debouncing
	{
		last_time = current_time; // Atualiza o tempo do último evento
		// Verifica qual botão foi pressionado	

        if (gpio == button_a)
        {
            if (indice == 9){
                indice = 9;
            }else {
                indice++;
            }
        }
        if (gpio == button_b)
        {
            if (indice == 0){
                indice = 0;
            }else {
                indice--;
            }

    }
    }
}
 char matriz_0[5][5]={
  {'W','R','R','R','W'},
  {'W','R','W','R','w'},
  {'W','R','W','R','W'},
  {'W','R','W','R','W'},
  {'W','R','R','R','W'}
 };
char matriz_1[5][5]={
  {'W','W','R','W','W'},
  {'W','R','R','W','W'},
  {'W','W','R','W','W'},
  {'W','W','R','W','W'},
  {'W','R','R','R','W'}
 };
char matriz_2[5][5]={
  {'W','R','R','R','W'},
  {'W','W','W','R','W'},
  {'W','R','R','R','W'},
  {'W','R','W','W','W'},
  {'W','R','R','R','W'}
 };
char matriz_3[5][5]={
  {'W','R','R','R','W'},
  {'W','W','W','R','W'},
  {'W','W','R','W','W'},
  {'W','R','R','R','W'}
 };
char matriz_4[5][5]={
  {'W','R','W','R','W'},
  {'W','R','W','R','W'},
  {'W','R','R','R','W'},
  {'W','W','W','R','W'},
  {'W','W','W','R','W'}
 };

char matriz_5[5][5]={
  {'W','R','R','R','W'},
  {'W','R','W','W','W'},
  {'W','R','R','R','W'},
  {'W','W','W','R','W'},
  {'W','R','R','R','W'}
 };

 char matriz_6[5][5]={
  {'W','R','R','R','W'},
  {'W','R','R','R','W'},
  {'W','R','W','R','W'},
  {'W','R','R','R','W'}
 };

 char matriz_7[5][5]={
  {'W','R','R','R','W'},
  {'W','W','W','R','W'},
  {'W','W','W','R','W'},
  {'W','W','W','R','W'}
 };
 char matriz_8[5][5]={
  {'W','R','R','R','W'},
  {'W','R','W','R','W'},
  {'W','R','R','R','W'},
  {'W','R','W','R','W'},
  {'W','R','R','R','W'}
 };

 char matriz_9[5][5]={
  {'W','R','R','R','W'},
  {'W','R','W','R','W'},
  {'W','R','R','R','W'},
  {'W','W','W','R','W'},
  {'W','R','R','R','W'}
 };

  void desenho (int indice){
    char(*matriz_desenho)[5];

    if (indice == 0)
    {
        matriz_desenho = &matriz_0;
    }
    if(indice == 1){
        matriz_desenho = &matriz_1;
    }
    if(indice == 2){
        matriz_desenho = &matriz_2;
    }
    if(indice == 3){
        matriz_desenho = &matriz_3;
    }
    if(indice == 4){
        matriz_desenho = &matriz_4;
    }
    if(indice == 5){
        matriz_desenho = &matriz_5;
    }
    if(indice == 6){
        matriz_desenho = &matriz_6;
    }
    if(indice == 7){
        matriz_desenho = &matriz_7;
    }
    if(indice == 8){
        matriz_desenho = &matriz_8;
    }
    if(indice == 9){
        matriz_desenho = &matriz_9;
    }

    for (int x = 0; x < tamanho_matriz; x++)
	{
		for (int y = 0; y < tamanho_matriz; y++)
		{
			if (matriz_desenho[x][y] == 'R')
			{
				cor_ao_led(matrizint[x][y], 255, 0, 0, _intensidade_);
			}
			if (matriz_desenho[x][y] == 'G')
			{
				cor_ao_led(matrizint[x][y], 0, 255, 0, _intensidade_);
			}
			if (matriz_desenho[x][y] == 'B')
			{
				cor_ao_led(matrizint[x][y], 0, 0, 255, _intensidade_);
			}
			if (matriz_desenho[x][y] == 'Y')
			{
				cor_ao_led(matrizint[x][y], 255, 255, 0, _intensidade_);
			}
			if (matriz_desenho[x][y] == 'P')
			{
				cor_ao_led(matrizint[x][y], 255, 0, 255, _intensidade_);
			}
			if (matriz_desenho[x][y] == 'C')
			{
				cor_ao_led(matrizint[x][y], 0, 255, 255, _intensidade_);
			}
			if (matriz_desenho[x][y] == 'W')
			{
				cor_ao_led(matrizint[x][y], 255, 255, 255, 64);
                			}
			if (matriz_desenho[x][y] == '*')
			{
				cor_ao_led(matrizint[x][y], 0, 0, 0, _intensidade_);
			}
		}
		// Atualiza a matriz de LEDs e espera um tempo antes de mudar a cor
		carregar_o_buffer();
		sleep_ms(10); // 300ms entre as mudanças de cor
	}
  }

int main()
{
    stdio_init_all();
    inicializacao_maquina_pio(PINO_MATRIZ_LED);
    iniciar_gpio();
    _intensidade_ = 140;
    gpio_set_irq_enabled_with_callback(button_b, GPIO_IRQ_EDGE_FALL, true, &interrupcao);
	gpio_set_irq_enabled_with_callback(button_a, GPIO_IRQ_EDGE_FALL, true, &interrupcao);
    
    bool contador = true;

    while (true) {
        gpio_put(led_vermelho, 1);
        sleep_ms(100);
        gpio_put(led_vermelho, 0);
        sleep_ms(100);
        desenho(indice);
               
    }

}
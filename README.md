# interrupcoes_samuel

 Projeto: Controle de Matriz de LEDs WS2812 com Raspberry Pi Pico
Descrição do Projeto
Este projeto consiste em controlar uma matriz de LEDs WS2812 5x5 utilizando um Raspberry Pi Pico. A matriz exibe números de 0 a 9, que podem ser incrementados ou decrementados por meio de dois botões. O LED RGB integrado pisca continuamente como indicador de funcionamento. O projeto foi desenvolvido como parte de um trabalho escolar para consolidar o entendimento de interrupções, debouncing e controle de LEDs.

Funcionalidades
Exibição de Números na Matriz de LEDs:

Os números de 0 a 9 são exibidos em uma matriz 5x5 de LEDs WS2812.

Cada número é representado por um padrão fixo de cores (vermelho e branco).

Controle por Botões:

O botão A incrementa o número exibido.

O botão B decrementa o número exibido.

O tratamento de bouncing dos botões é feito via software.

LED RGB Integrado:

O LED RGB pisca continuamente (5 vezes por segundo) como indicador de funcionamento.

Uso de Interrupções:

As funcionalidades dos botões são implementadas utilizando interrupções (IRQ).

Componentes Utilizados
Raspberry Pi Pico

Matriz de LEDs WS2812 5x5

Botões (A e B)

LED RGB integrado

Resistores de pull-up internos

Estrutura do Código
O código está organizado da seguinte forma:

Inicialização:

Configuração dos pinos GPIO.

Inicialização da máquina PIO para controle dos LEDs WS2812.

Funções Principais:

inicializacao_maquina_pio: Configura a máquina PIO para controlar os LEDs.

cor_ao_led: Define a cor de um LED específico na matriz.

apagar_buffer: Apaga todos os LEDs da matriz.

carregar_o_buffer: Envia os dados de cor para a matriz de LEDs.

desenho: Mapeia os padrões de números para a matriz de LEDs.

interrupcao: Trata as interrupções dos botões com debouncing.

Matrizes de Desenho:

Cada número de 0 a 9 é representado por uma matriz 5x5 de caracteres, onde:

'R' representa vermelho.

'W' representa branco.

'*' representa LED apagado.

Loop Principal:

Controla o piscar do LED RGB e atualiza a exibição da matriz de LEDs conforme o número selecionado.

Como Executar o Projeto
Requisitos:

Hardware: Raspberry Pi Pico, matriz de LEDs WS2812, botões, jumpers e protoboard.

Software: Ambiente de desenvolvimento configurado para Raspberry Pi Pico (ex: VS Code com extensão Pico SDK).

Passos:

Conecte a matriz de LEDs ao pino GPIO 7 do Raspberry Pi Pico.

Conecte os botões A e B aos pinos GPIO 5 e 6, respectivamente.

Conecte o LED RGB aos pinos GPIO 11, 12 e 13.

Compile e carregue o código no Raspberry Pi Pico.

Funcionamento:

Ao ligar o circuito, o LED RGB começará a piscar.

Use os botões A e B para navegar entre os números de 0 a 9 na matriz de LEDs.

Vídeo de Demonstração
Um vídeo de demonstração do projeto está disponível aqui (https://youtube.com/shorts/DWpK-x3tgiA).

Autor
Nome: Samuel Henrique Lopes Ribeiro

Instituição: Embarcatech

Data: 02/02/2025


#include "Cores.h"

/*
 * Matriz de cores global
 * 
 * Definição concreta da paleta de cores do jogo. Cada linha representa uma cor
 * com seus componentes RGB (Red, Green, Blue). Os índices são usados nos sprites
 * para referenciar cores específicas.
 * 
 * Formato:
 * - 9 cores disponíveis (índices 0-8)
 * - Cada cor com 3 componentes (R, G, B) no intervalo [0.0, 1.0]
 */
float cores[9][3] = {
    {0, 0, 0},       // 0 - Preto (Fundo)
    {1, 1, 1},       // 1 - Branco (Contorno)
    {0.1, 0.3, 0.8}, // 2 - Azul (Corpo)
    {0.5, 0.5, 0.5}, // 3 - Cinza (Asas)
    {1, 1, 0},       // 4 - Amarelo (Centro do fogo)
    {1, 0.5, 0},     // 5 - Laranja (Chamas)
    {0.6, 0.9, 1.0}, // 6 - Azul Claro (Vidro)
    {1.0, 0.0, 1.0}, // 7 - Vermelho
    {0.0, 1.0, 0.0}  // 8 - Verde
};
#pragma once  
#include "Shoot.h"  

/*
 * Alien
 * Classe que representa um alienígena inimigo no jogo
 * 
 * Gerencia a posição, movimento, renderização e ataques de um alienígena.
 * Cada instância representa um inimigo na formação alienígena.
 */
class Alien {
public:
    float x, y;  ///< Posição atual do alien no espaço 2D (coordenadas centrais)

    /*
     * Construtor do Alien
     * startX: Posição inicial no eixo X
     * startY: Posição inicial no eixo Y
     * 
     * Inicializa o alienígena nas coordenadas especificadas,
     * armazenando-as nos atributos x e y da classe.
     */
    Alien(float startX, float startY);

    /*
     * Move o alienígena
     * dx: Deslocamento no eixo X
     * dy: Deslocamento no eixo Y
     * 
     * Atualiza a posição do alien somando os deslocamentos
     * às coordenadas atuais (x e y).
     */
    void move(float dx, float dy);

    /*
     * Renderiza o alienígena na tela
     * offsetX: Deslocamento horizontal opcional para posicionamento (padrão 0)
     * offsetY: Deslocamento vertical opcional para posicionamento (padrão 0)
     * 
     * Desenha o sprite do alien usando OpenGL, convertendo uma matriz
     * de pixels em quadrados coloridos. Os parâmetros opcionais permitem
     * ajustar a posição de desenho quando necessário.
     */
    void draw(float offsetX = 0, float offsetY = 0);

    /*
     * Faz o alienígena atirar
     * 
     * Retorna: Um objeto Shoot configurado como tiro inimigo
     * 
     * Cria um novo tiro:
     * - Posição: ligeiramente abaixo do alien (y - 0.05)
     * - Velocidade: -0.02 (movimento para baixo)
     * - Direção: -1 (indicando tiro inimigo)
     */
    Shoot shoot();
};
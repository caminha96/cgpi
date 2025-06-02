#include "AlienBoss.h"
#include <GL/glut.h>
#include "Cores.h"

/*
 * Construtor do Alien
 * startX: Posição inicial no eixo X
 * startY: Posição inicial no eixo Y
 *
 * Inicializa o alienígena nas coordenadas especificadas,
 * armazenando-as nos atributos x e y da classe.
 */
AlienBoss::AlienBoss(float startX, float startY) : x(startX), y(startY) {}

/*
 * Move o alienígena
 * dx: Deslocamento no eixo X
 * dy: Deslocamento no eixo Y
 *
 * Atualiza a posição do alien somando os deslocamentos
 * às coordenadas atuais (x e y).
 */
void AlienBoss::move(float dx, float dy) {
    x += dx;
    y += dy;
}

int alienBoss[18][15] = {
    {0,0,0,0,0,0,0,5,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,5,4,5,0,0,0,0,0,0},
    {0,0,0,0,0,5,4,4,4,5,0,0,0,0,0},
    {0,0,0,0,5,4,4,4,4,4,5,0,0,0,0},
    {0,0,0,0,5,4,4,4,4,4,5,0,0,0,0},
    {0,0,0,0,3,5,5,5,5,5,3,0,0,0,0},
    {0,0,0,0,0,3,3,5,3,3,0,0,0,0,0},
    {0,0,0,0,0,2,2,2,2,2,0,0,0,0,0},
    {0,0,0,2,2,2,3,3,3,2,2,2,0,0,0},
    {0,0,2,3,3,3,3,3,3,3,3,3,2,0,0},
    {0,2,3,3,6,6,6,6,6,6,6,3,3,2,0},
    {2,3,3,6,6,8,8,8,8,8,6,6,3,3,2},
    {2,3,6,6,8,9,9,8,9,9,8,6,6,3,2},
    {2,3,6,6,6,8,8,8,8,8,6,6,6,3,2},
    {2,3,3,6,6,6,8,8,8,6,6,6,3,3,2},
    {0,2,3,3,6,6,6,8,6,6,6,3,3,2,0},
    {0,0,2,3,3,3,3,3,3,3,3,3,2,0,0},
    {0,0,0,2,2,2,2,2,2,2,2,2,0,0,0},
};

/*
 * Renderiza o alienígena na tela
 * offsetX: Deslocamento horizontal para posicionamento
 * offsetY: Deslocamento vertical para posicionamento
 *
 * Desenha o sprite do alien convertendo a matriz de pixels
 * em quadrados coloridos usando OpenGL:
 * 1. Percorre cada elemento da matriz 18x15
 * 2. Ignora pixels com valor 0 (transparentes)
 * 3. Para outros valores, usa a paleta global para definir a cor
 * 4. Desenha quadrados na posição calculada
 */
void AlienBoss::draw(float offsetX, float offsetY) {
    float size = 0.03f;  // Tamanho de cada "pixel" do sprite

    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 15; j++) {
            int cor = alienBoss[i][j];
            if (cor == 0) continue;  // Pula pixels transparentes

            // Define a cor usando a paleta global
            glColor3f(cores[cor][0], cores[cor][1], cores[cor][2]);

            // Calcula posição do quadrado
            float xPos = offsetX + j * size;
            float yPos = offsetY - i * size;

            // Desenha o quadrado
            glBegin(GL_QUADS);
                glVertex2f(xPos, yPos);
                glVertex2f(xPos + size, yPos);
                glVertex2f(xPos + size, yPos - size);
                glVertex2f(xPos, yPos - size);
            glEnd();
        }
    }
}

/*
 * Faz o alienígena atirar
 *
 * Retorna: Um objeto Shoot configurado como tiro inimigo
 *
 * Cria um novo tiro com as seguintes características:
 * - Posição: ligeiramente abaixo do alien (y - 0.05)
 * - Velocidade: -0.02 (movimento para baixo)
 * - Direção: -1 (indicando tiro inimigo)
 * - O tiro é criado ativo por padrão (active = true)
 */
Shoot AlienBoss::shoot() {
    return Shoot(x, y - 0.05f, -0.02f, -1);
}
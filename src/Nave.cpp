#include "Nave.h"
#include <GL/glut.h>
#include "Cores.h"

/*
 * Construtor da Nave
 * startX: Posição inicial no eixo X
 * startY: Posição inicial no eixo Y
 * 
 * Inicializa a nave nas coordenadas especificadas.
 * A matriz de pixels é definida para criar o visual da nave.
 */

int nave[30][30] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,1,6,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,1,6,6,6,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,6,6,6,6,6,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,6,6,6,6,6,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,6,6,6,6,6,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,6,6,6,6,6,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,6,6,6,6,6,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,6,6,6,6,6,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,2,7,7,7,7,7,7,7,7,7,2,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,2,2,7,7,7,7,7,7,7,7,7,2,2,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,2,2,2,1,1,1,1,1,1,1,1,1,2,2,2,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,2,2,2,2,1,1,1,1,1,1,1,1,1,2,2,2,2,0,0,0,0,0,0,0},
    {0,0,2,0,0,2,2,2,2,2,1,1,1,1,2,1,1,1,1,2,2,2,2,2,0,0,2,0,0,0},
    {0,0,2,0,2,2,2,2,2,2,1,1,1,2,2,2,1,1,1,2,2,2,2,2,2,0,2,0,0,0},
    {0,0,2,2,2,2,2,2,2,2,1,1,1,2,2,2,1,1,1,2,2,2,2,2,2,2,2,0,0,0},
    {0,0,2,2,2,2,2,2,2,2,1,1,1,2,2,2,1,1,1,2,2,2,2,2,2,2,2,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,5,5,4,4,4,4,4,5,5,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,5,4,4,4,4,4,4,4,5,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,5,4,4,4,4,4,5,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,5,4,4,4,5,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,5,4,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

/*
 * Desenha a nave na tela
 * 
 * Renderiza a nave usando a matriz de pixels, onde cada valor
 * diferente de zero representa um quadrado colorido.
 * A nave é centralizada nas coordenadas (x,y).
 */
Nave::Nave(float startX, float startY) : x(startX), y(startY) {}

    const float size = 0.013f;  // Tamanho base de cada "pixel"
void Nave::desenha() const {
    // Percorre toda a matriz 30x30
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            int cor = nave[i][j];
            
            // Pula pixels transparentes
            if (cor == 0) continue;
            
            // Define a cor usando a paleta global
            glColor3f(cores[cor][0], cores[cor][1], cores[cor][2]);
            
            // Calcula posição do pixel (centralizado na nave)
            float px = x + (j - 15) * size * 0.5f;
            float py = y - (i - 15) * size * 0.5f;
            
            // Desenha o quadrado
            glBegin(GL_QUADS);
                glVertex2f(px, py);
                glVertex2f(px + size * 0.5f, py);
                glVertex2f(px + size * 0.5f, py - size * 0.5f);
                glVertex2f(px, py - size * 0.5f);
            glEnd();
        }
    }
}

/*
 * Move a nave para a esquerda
 * 
 * Atualiza a posição X da nave com velocidade fixa (0.05 unidades),
 * respeitando o limite esquerdo da tela (-0.95).
 */
void Nave::moverEsquerda() {
    if (x - 0.05f > -0.95f)  // Verifica limite esquerdo
        x -= 0.05f;          // Move para esquerda
}

/*
 * Move a nave para a direita
 * 
 * Atualiza a posição X da nave com velocidade fixa (0.05 unidades),
 * respeitando o limite direito da tela (0.95).
 */
void Nave::moverDireita() {
    if (x + 0.05f < 0.95f)  // Verifica limite direito
        x += 0.05f;         // Move para direita
}
#include "Shoot.h"     
#include <GL/glut.h>    

/*
 * Atualiza a posição do tiro
 * 
 * Move o tiro na direção especificada (para cima ou para baixo)
 * e desativa-o quando sai dos limites da tela.
 */
void Shoot::update() {
    if (!active) return;  // Ignora tiros inativos

    // Movimenta o tiro (direção +1 = subindo, -1 = descendo)
    y += speed * direction;

    // Desativa o tiro se sair da área visível (y entre -1.0 e 1.0)
    if (y > 1.0f || y < -1.0f) {
        active = false;
    }
}

/*
 * Renderiza o tiro na tela
 * 
 * Desenha um retângulo vertical na posição atual do tiro.
 * Tiros aliados (direção +1) são brancos, inimigos (direção -1) são vermelhos.
 */
void Shoot::draw() const {
    if (!active) return;  // Não desenha tiros inativos

    // Seleciona cor baseada na direção
    if (direction == +1) {
        glColor3f(1.0f, 1.0f, 1.0f);  // Branco (tiro da nave)
    } else if (direction == -1) {
        glColor3f(1.0f, 0.0f, 0.0f);  // Vermelho (tiro inimigo)
    }

    // Desenha um retângulo vertical (mais alto que largo)
    glBegin(GL_QUADS);
        glVertex2f(x - 0.01f, y - 0.03f);  // Canto inferior esquerdo
        glVertex2f(x + 0.01f, y - 0.03f);  // Canto inferior direito
        glVertex2f(x + 0.01f, y + 0.03f);  // Canto superior direito
        glVertex2f(x - 0.01f, y + 0.03f);  // Canto superior esquerdo
    glEnd();

    // Reseta cor para branco (boa prática)
    glColor3f(1.0f, 1.0f, 1.0f);
}
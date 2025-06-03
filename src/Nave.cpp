#include "Nave.h"
#include <GL/glut.h>
#include "Cores.h" // Certifique-se que Cores.h define 'cores' e que 'nave[30][30]' está acessível

// Definição da matriz da nave (como no seu código original)
int nave[30][30] = {
    // ... (seus dados da matriz da nave aqui) ...
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


// Definição das constantes estáticas
const float Nave::HIT_ANIMATION_DURATION = 30.0f; // Duração de 30 frames/updates
const float Nave::HIT_ROTATION_SPEED = 24.0f;   // 24 graus por frame (resulta em 2 rotações completas em 30 frames)

// Variável 'size' original do seu Nave.cpp
const float size = 0.013f;  // Tamanho base de cada "pixel"

Nave::Nave(float startX, float startY) : x(startX), y(startY),
                                         isHitAnimating(false),
                                         hitRotationAngle(0.0f),
                                         hitAnimationTimer(0.0f) {}

void Nave::startHitAnimation() {
    // Reinicia a animação a cada hit
    isHitAnimating = true;
    // Não resetamos hitRotationAngle para 0 aqui, para que a rotação pareça contínua se atingida múltiplas vezes.
    // Se preferir que cada hit comece a rotação do zero, descomente a linha abaixo:
    // hitRotationAngle = 0.0f;
    hitAnimationTimer = HIT_ANIMATION_DURATION;
}

void Nave::updateHitAnimation() {
    if (isHitAnimating) {
        hitRotationAngle += HIT_ROTATION_SPEED;
        if (hitRotationAngle >= 360.0f) {
            hitRotationAngle -= 360.0f; // Mantém o ângulo entre 0 e 359.9...
        }

        hitAnimationTimer -= 1.0f; // Decrementa o timer a cada chamada

        if (hitAnimationTimer <= 0.0f) {
            isHitAnimating = false;
            hitRotationAngle = 0.0f; // Reseta o ângulo ao final da animação
        }
    }
}

void Nave::desenha() const {
    glPushMatrix(); // Salva a matriz de transformação atual

    // 1. Transladar para a posição da nave (este será o novo (0,0) para rotação e desenho)
    glTranslatef(x, y, 0.0f);

    // 2. Se a animação de "hit" estiver ativa, aplicar a rotação
    if (isHitAnimating) {
        glRotatef(hitRotationAngle, 0.0f, 0.0f, 1.0f); // Rotaciona em torno do eixo Z (que agora passa pelo centro da nave)
    }

    // 3. Desenhar a nave. As coordenadas dos pixels agora são relativas ao (0,0) atual.
    const float pixelRenderDim = size * 0.5f; // A dimensão (largura/altura) de cada quadrado do pixel da nave

    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            int cor = ::nave[i][j]; // Acessa a matriz global 'nave'

            if (cor == 0) continue; // Pula pixels transparentes

            // Define a cor usando a paleta global (presumindo que 'cores' é global ou acessível)
            glColor3f(cores[cor][0], cores[cor][1], cores[cor][2]);

            // Calcula as coordenadas do canto superior-esquerdo do pixel, relativas ao centro da nave (0,0 atual)
            // (j - 15.0f) centraliza horizontalmente.
            // -(i - 15.0f) centraliza verticalmente e inverte o eixo i para corresponder ao Y do OpenGL.
            float local_x_corner = (j - 15.0f) * pixelRenderDim;
            float local_y_corner = -(i - 15.0f) * pixelRenderDim;

            // Desenha o quadrado
            glBegin(GL_QUADS);
                glVertex2f(local_x_corner,                    local_y_corner);                      // Canto superior-esquerdo
                glVertex2f(local_x_corner + pixelRenderDim, local_y_corner);                      // Canto superior-direito
                glVertex2f(local_x_corner + pixelRenderDim, local_y_corner - pixelRenderDim);      // Canto inferior-direito
                glVertex2f(local_x_corner,                    local_y_corner - pixelRenderDim);      // Canto inferior-esquerdo
            glEnd();
        }
    }

    glPopMatrix(); // Restaura a matriz de transformação anterior
}

void Nave::moverEsquerda() {
    // Opcional: impedir movimento se estiver na animação de "hit"
    if (isHitAnimating) return;

    if (x - 0.05f > -0.95f)
        x -= 0.05f;
}

void Nave::moverDireita() {
    // Opcional: impedir movimento se estiver na animação de "hit"
    if (isHitAnimating) return;

    if (x + 0.05f < 0.95f)
        x += 0.05f;
}
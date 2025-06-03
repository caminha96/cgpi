#include <GL/glut.h>  
#include "Game.h"
bool keyStates[256] = {false};

Game game;  // Instância global do jogo
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Limpa o buffer de cor
    glLoadIdentity();              // Reseta a matriz de transformação

    game.draw();                   // Desenha todos os elementos do jogo

    glutSwapBuffers();             // Troca os buffers (double buffering)
}
void keyDown(unsigned char key, int x, int y) {
    keyStates[key] = true;

        // Adicione apenas esta verificação extra:
    if (key == ' ' && (game.estadoJogo == GAME_OVER || game.estadoJogo == VITORIA)) {
        game.restart();
    }
}
void keyUp(unsigned char key, int x, int y) {
    keyStates[key] = false;
}

void update(int value) {
    // Movimento para esquerda (teclas A ou a)
    if (keyStates['a'] || keyStates['A']) {
        game.moveNaveEsquerda();
    }

    // Movimento para direita (teclas D ou d)
    if (keyStates['d'] || keyStates['D']) {
        game.moveNaveDireita();
    }

    // Disparo (barra de espaço)
    if (keyStates[' ']) {
        static bool canShoot = true;  // Controle de rate limiting

        if (canShoot) {
            game.naveShoot();
            canShoot = false;

            // Temporizador para permitir novo disparo após 300ms
            glutTimerFunc(300, [](int) { canShoot = true; }, 0);
        }
    }

    game.update();               // Atualiza estado do jogo
    glutPostRedisplay();         // Marca a janela para redesenho
    glutTimerFunc(33, update, 0); // Agenda próxima atualização (≈30 FPS)
}
int main(int argc, char** argv) {
    // Inicialização do GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Double buffering + cores RGB
    glutInitWindowSize(800, 800);                 // Tamanho da janela 800x800
    glutCreateWindow("Independece Day");  // Cria a janela

    // Configuração do OpenGL
    glClearColor(0, 0, 0, 1);                    // Cor de fundo preta
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);                   // Sistema de coordenadas normalizado
    glMatrixMode(GL_MODELVIEW);

    // Registro de callbacks
    glutKeyboardFunc(keyDown);    // Tecla pressionada
    glutKeyboardUpFunc(keyUp);    // Tecla liberada
    glutDisplayFunc(display);     // Renderização
    glutTimerFunc(0, update, 0);  // Inicia o loop de atualização

    glutMainLoop();  // Inicia o loop principal do GLUT
    return 0;
}
#ifndef ALIENBOSS_H
#define ALIENBOSS_H
#include "Shoot.h"

/*
 * AlienBoss
 * Classe que representa o chefe final alienígena no jogo
 * Gerencia a posição, movimento, disparos e renderização do chefe alienígena.
 * O AlienBoss é um inimigo especial com comportamento diferente dos aliens comuns.
 */
class AlienBoss {
public:
    int life;
    // Inicializa o chefe alienígena na posição especificada.
    AlienBoss(float startX, float startY);
    // Atualiza a posição do boss somando os deslocamentos às coordenadas atuais
    void move(float dx, float dy);
    // Renderiza o sprite do boss usando OpenGL, aplicando os offsets se necessário
    void draw(float offsetX, float offsetY);
    // Cria e retorna um novo tiro na posição atual do boss
    Shoot shoot();
    bool isAlive();      // Verifica se o boss ainda está vivo
    void takeDamage();   // Reduz a vida do boss
    float x, y; // Armazenam a posição atual do AlienBoss (coordenadas X e Y)

};

#endif 
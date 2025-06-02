#ifndef SHOOT_H
#define SHOOT_H

/*
 * Shoot
 * Classe que gerencia os tiros do jogo (tanto da nave quanto dos aliens)
 * 
 * Controla posição, movimento, estado e renderização dos tiros.
 */
class Shoot {
public:
    // Atributos públicos (poderiam ser privados com métodos de acesso)
    float x, y;        // Posição atual do tiro no espaço 2D
    float speed;       // Velocidade de movimento do tiro
    int direction;     // Direção do tiro (+1 = pra cima, -1 = pra baixo)
    bool active;       // Flag que indica se o tiro está ativo/visível

    /*
     * Construtor padrão - cria tiro inativo
     * 
     * Inicializa todos os valores com 0/false. Útil para criação de arrays.
     */
    Shoot() : x(0), y(0), speed(0), direction(0), active(false) {}

    /*
     * Construtor parametrizado - cria tiro ativo
     * x: Posição inicial X
     * y: Posição inicial Y
     * speed: Velocidade do tiro
     * direction: Direção do movimento (+1 ou -1)
     * 
     * Cria um tiro pronto para ser usado, marcado como ativo.
     */
    Shoot(float x, float y, float speed, int direction) :
        x(x), y(y), speed(speed), direction(direction), active(true) {}

    /*
     * Atualiza a posição do tiro
     * Movimenta o tiro baseado na speed e direction.
     * Deve ser chamado a cada frame do jogo.
     */
    void update();

    /*
     * Renderiza o tiro usando OpenGL.
     * O visual muda conforme a direção (tiros aliados são brancos, inimigos vermelhos).
     */
    void draw() const;
};

#endif 
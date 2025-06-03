#ifndef NAVE_H
#define NAVE_H

// #include <GL/glut.h> // Se não estiver já incluído por outros headers que Nave.h possa incluir indiretamente

class Nave {
public:
    float x, y;
    bool isHitAnimating;      // Indica se a animação de "atingido" está ativa
    float hitRotationAngle;   // Ângulo atual da rotação de "atingido"
    float hitAnimationTimer;  // Timer para controlar a duração da animação

    // Constantes para a animação
    static const float HIT_ANIMATION_DURATION; // Duração em número de "updates" ou "frames"
    static const float HIT_ROTATION_SPEED;     // Velocidade da rotação em graus por update/frame

    Nave(float startX, float startY);
    void desenha() const;
    void moverEsquerda();
    void moverDireita();

    void startHitAnimation();  // Para iniciar a animação de "hit"
    void updateHitAnimation(); // Para atualizar a animação a cada frame
};

#endif // NAVE_H
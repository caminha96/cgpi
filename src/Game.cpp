#include "Game.h"
#include <GL/glut.h>
#include <cstdlib>    // Para rand(), RAND_MAX
#include <algorithm>  // Para std::remove_if, std::swap
#include <cmath>      // Para fabs, sin
#include <string>     // Para std::to_string
#include "AlienBoss.h"

extern Game game;
float randomFloat(float min, float max) {
    if (min > max) std::swap(min, max); // Garante min <= max
    return min + (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * (max - min);
}
Game::Game() : direction(0.02f), estadoJogo(PLAYING), nivel(1), aliensMortos(0), vidas(3), alienBoss(nullptr) {
    initAliens();
    initNave();
    initStars();
}
Game::~Game() {
    delete alienBoss;
}

// ADICIONADO: Implementação das funções de estrelas
void Game::initStars(int numberOfStars) {
    stars.clear();
    stars.reserve(numberOfStars); // Opcional: pré-aloca memória
    for (int i = 0; i < numberOfStars; ++i) {
        Star star;
        star.x = randomFloat(-1.0f, 1.0f); // Posição X aleatória na tela
        star.y = randomFloat(-1.0f, 1.0f); // Posição Y aleatória na tela inicial
        star.speed = randomFloat(0.0005f, 0.003f); // Velocidade de "queda" ajustada para ~30FPS
        star.brightness = randomFloat(0.1f, 0.7f); // Brilho variado (mais sutil)
        stars.push_back(star);
    }
}

void Game::updateStars() {
    for (auto& star : stars) {
        star.y -= star.speed; // Move a estrela para baixo

        // Se a estrela sair da tela por baixo, reposiciona-a no topo
        if (star.y < -1.05f) { // Um pouco abaixo de -1.0 para desaparecer completamente
            star.y = 1.05f;    // Reposiciona um pouco acima de 1.0
            star.x = randomFloat(-1.0f, 1.0f);
            // Opcional: re-randomizar velocidade e brilho para mais variedade
            // star.speed = randomFloat(0.0005f, 0.003f);
            // star.brightness = randomFloat(0.1f, 0.7f);
        }
    }
}

void Game::drawStars() {
    // glPointSize(1.0f); // Você pode definir um tamanho para as estrelas aqui se desejar
    glPointSize(2.5f);
    glBegin(GL_POINTS);
    for (const auto& star : stars) {
        // Define a cor da estrela baseada no seu brilho
        glColor3f(star.brightness, star.brightness, star.brightness * 0.9f + 0.1f);
        glVertex2f(star.x, star.y);
    }
    glEnd();
}

void Game::initAliens() {
    aliens.clear();
    const float startX = -0.6f;
    const float startY = 1.0f;
    const float espacamentoX = 0.3f;
    const float espacamentoY = 0.25f;
    

    for (int linha = 0; linha < 3; ++linha) {
        for (int coluna = 0; coluna < 5; ++coluna) {
            float x = startX + coluna * espacamentoX;
            float y = startY - linha * espacamentoY;
            aliens.emplace_back(x, y);
        }
    }
}
void Game::initNave() {
    naves.clear();
    naves.emplace_back(0, -0.85f);
}
void Game::moveNaveEsquerda() {
    if (!naves.empty()) {
        naves[0].moverEsquerda();
    }
}
void Game::moveNaveDireita() {
    if (!naves.empty()) {
        naves[0].moverDireita();
    }
}
void Game::naveShoot() {
    if (!naves.empty() && !naves[0].isHitAnimating) { // Opcional: impedir tiro durante a animação
        const float velocidadeTiro = 0.05f;
        shoots.emplace_back(naves[0].x, naves[0].y + 0.1f, velocidadeTiro, +1);
    }
}
void Game::alienShoot(int index) {
    if (index >= 0 && static_cast<size_t>(index) < aliens.size()) {
        const float velocidadeTiro = 0.03f;
        shoots.emplace_back(aliens[index].x, aliens[index].y - 0.1f, velocidadeTiro, -1);
    }
}
void Game::bossShoot() {
    if (alienBoss && alienBoss->life > 0) {
        const float velocidadeTiro = 0.04f;
        shoots.emplace_back(alienBoss->x, alienBoss->y - 0.1f, velocidadeTiro, -1);
    }
}
void Game::restart() {
    estadoJogo = PLAYING;
    aliens.clear();
    naves.clear();
    shoots.clear();
    initAliens();
    initNave();
    initStars();
    direction = 0.02f;
    nivel = 1;
    aliensMortos = 0;
    vidas = 3;
    if (alienBoss) {
        delete alienBoss;
        alienBoss = nullptr;
    }
}
void Game::updateShoots() {
    for (auto& shoot : shoots) {
        shoot.update();
    }
    shoots.erase(
        std::remove_if(shoots.begin(), shoots.end(),
        [](const Shoot& s) { return !s.active; }),
        shoots.end()
    );
}
bool Game::colidiu(const Shoot& tiro, const Nave& nave) {
    const float larguraNave = 0.2f;
    const float alturaNave = 0.1f;
    return (tiro.x >= nave.x - larguraNave/2 && tiro.x <= nave.x + larguraNave/2) &&
           (tiro.y >= nave.y - alturaNave/2 && tiro.y <= nave.y + alturaNave/2);
}
void Game::checarColisoes() {
    bool bossFoiDestruido = false;

    for (auto& tiro : shoots) {
        if (tiro.direction == -1) { // Tiro do alien/boss em direção à nave
            if (!naves.empty() && colidiu(tiro, naves[0])) {
                tiro.active = false;

                if (!naves[0].isHitAnimating) { // Só perde vida e respawna se não estiver já na animação de hit (evita hits múltiplos no mesmo "dano")
                                                // Ou remova essa condição se quiser que cada hit conte independentemente
                    naves[0].startHitAnimation(); // <<-- INICIA A ANIMAÇÃO DE ROTAÇÃO AQUI
                    vidas--;
                    if (vidas <= 0) {
                        estadoJogo = GAME_OVER;
                    } else {
                        // A nave será reposicionada, e a animação de rotação continuará lá.
                        // Se quiser um delay antes do respawn, a lógica seria mais complexa.
                        respawnNave();
                    }
                }
                break;
            }
        }
        // ... (resto da lógica de colisão com aliens e boss) ...
        if (tiro.direction == +1) { // Tiro da nave
            for (auto& alien : aliens) {
                if (fabs(tiro.x - alien.x) < 0.09f && fabs(tiro.y - alien.y) < 0.09f) {
                    tiro.active = false;
                    alien.y = -999;
                    aliensMortos++;
                    if (nivel == 1 && aliensMortos >= 15) {
                        nivel = 2;
                        aliensMortos = 0;
                        initAliens();
                        direction = 0.025f;
                    }
                    break;
                }
            }
            // Colisão com o Boss
            if (alienBoss != nullptr && alienBoss->isAlive()) {
                float bossWidth = 15 * 0.03f; // Essas dimensões devem ser consistentes
                float bossHeight = 18 * 0.03f;
                if (tiro.x >= alienBoss->x - bossWidth/2 &&
                    tiro.x <= alienBoss->x + bossWidth/2 &&
                    tiro.y <= alienBoss->y + bossHeight/2 &&
                    tiro.y >= alienBoss->y - bossHeight/2) {

                    tiro.active = false;
                    alienBoss->takeDamage();

                    if (!alienBoss->isAlive()) {
                        delete alienBoss;
                        alienBoss = nullptr;
                        bossFoiDestruido = true;
                    }
                }
            }
        }
    }

    aliens.erase(
        std::remove_if(aliens.begin(), aliens.end(),
        [](const Alien& a) { return a.y < -900; }),
        aliens.end()
    );

    if (nivel == 2 && aliens.empty() && alienBoss == nullptr && !bossFoiDestruido) {
        alienBoss = new AlienBoss(0.0f, 0.8f);
    }
}
void Game::update() {
    if (estadoJogo == GAME_OVER || estadoJogo == VITORIA) return;
    updateStars();
    if (nivel == 2 && aliens.empty() && alienBoss == nullptr /*&& !bossFoiDestruido - essa condição estava em checarColisoes*/) {
        // Checar se o boss foi destruído antes de declarar vitória se ele existiu neste nível.
        // Se o boss nunca apareceu (ex: aliens eliminados antes do boss spawnar), então é vitória.
        // A lógica exata aqui pode depender de como 'bossFoiDestruido' é gerenciado entre updates.
        // Para simplificar, vamos assumir que se não há aliens e não há boss (ou já foi destruído), é vitória.
        estadoJogo = VITORIA;
        return; // Adicionado return para não continuar o update no estado de VITORIA
    }

    // Atualiza a animação da nave (se houver alguma)
    if (!naves.empty()) {
        naves[0].updateHitAnimation(); // <<-- ATUALIZA A ANIMAÇÃO DA NAVE AQUI
    }

    bool changeDirection = false;
    for (auto& alien : aliens) {
        alien.move(direction, 0);
        if (alien.x > 0.9f || alien.x < -0.9f) {
            changeDirection = true;
        }
        if (alien.y < -0.8f) {
            estadoJogo = GAME_OVER;
            return; // Adicionado return para não continuar o update no estado de GAME_OVER
        }
    }
    // ... (resto da sua função Game::update()) ...
    if (changeDirection) {
        direction = -direction;
        for (auto& alien : aliens) {
            alien.move(0, -0.01f);
        }
    }
    int chanceTiro = (nivel == 1) ? 5 : 15;
    if (!aliens.empty() && (rand() % 1000) < chanceTiro) {
        if (!aliens.empty()) { // Checagem extra para evitar acesso fora dos limites se aliens ficou vazio entre a checagem e o uso
             alienShoot(rand() % aliens.size());
        }
    }
    if (nivel == 2) {
        static float zigzagOffset = 0.01f;
        static bool esquerda = false;
        for (auto& alien : aliens) {
            alien.move(esquerda ? -zigzagOffset : zigzagOffset, -0.005f);
        }
        esquerda = !esquerda;
    }

    updateShoots(); // Mover updateShoots antes de checarColisoes para que os tiros se movam antes da checagem
    checarColisoes(); // checarColisoes pode mudar estadoJogo para GAME_OVER ou VITORIA

    if (estadoJogo == GAME_OVER || estadoJogo == VITORIA) return; // Checar novamente após colisões

    if (alienBoss && alienBoss->life > 0) {
        static float bossTime = 0.0f; // Considere mover timers como este para membros da classe Game se persistirem entre diferentes bosses ou resets
        bossTime += 0.016f; // Supondo aproximadamente 60FPS, para uma velocidade mais consistente
        alienBoss->x = 0.7f * sin(bossTime);
        // A posição Y do Boss estava sendo atualizada para 1.0f + ..., o que o colocaria fora da tela para cima.
        // Ajustando para mantê-lo visível, por exemplo:
        alienBoss->y = 0.7f + 0.1f * sin(bossTime * 0.5f); // Ajustado para uma posição Y mais razoável

        int chanceTiroBoss = 40;
        if ((rand() % 1000) < chanceTiroBoss) {
            bossShoot();
        }
    }
}
void Game::drawBossHealthBar() const {
    if (alienBoss == nullptr || !alienBoss->isAlive()) return;

    const float maxHealth = 33.0f; // Vida máxima do boss
    float currentHealth = static_cast<float>(alienBoss->life);
    float healthPercentage = currentHealth / maxHealth;

    // Posição e tamanho da barra de vida
    float barWidth = 0.4f;  // Largura total da barra
    float barHeight = 0.02f; // Altura da barra
    float barX = -0.2f;     // Posição X (centralizada)
    float barY = 0.9f;      // Posição Y (topo da tela)

    // Desenha o fundo da barra (vazia)
    glColor3f(0.5f, 0.5f, 0.5f); // Cinza
    glBegin(GL_QUADS);
        glVertex2f(barX, barY);
        glVertex2f(barX + barWidth, barY);
        glVertex2f(barX + barWidth, barY - barHeight);
        glVertex2f(barX, barY - barHeight);
    glEnd();

    // Desenha a parte cheia (vida atual)
    if (healthPercentage > 0) {
        // Cor muda de verde para vermelho conforme a vida diminui
        float r = 1.0f - healthPercentage;
        float g = healthPercentage;
        float b = 0.0f;
        glColor3f(r, g, b);
        
        glBegin(GL_QUADS);
            glVertex2f(barX, barY);
            glVertex2f(barX + barWidth * healthPercentage, barY);
            glVertex2f(barX + barWidth * healthPercentage, barY - barHeight);
            glVertex2f(barX, barY - barHeight);
        glEnd();
    }

    // Bordas para melhor visualização
    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(barX, barY);
        glVertex2f(barX + barWidth, barY);
        glVertex2f(barX + barWidth, barY - barHeight);
        glVertex2f(barX, barY - barHeight);
    glEnd();
}
void Game::draw() {
    static float bossX = 0.0f;
    static float bossSpeed = 0.01f;
    static float bossAngle = 0.0f;
    drawStars();
    drawBossHealthBar();
    if (estadoJogo == GAME_OVER) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2f(-0.15f, 0.0f);
        const char* msg = "GAME OVER";
        for (const char* c = msg; *c != '\0'; ++c) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }

        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(-0.35f, -0.1f);
        const char* restartMsg = "Para reiniciar pressione espaco";
        for (const char* c = restartMsg; *c != '\0'; ++c) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
    }
    if (estadoJogo == VITORIA) {
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2f(-0.15f, 0.0f);
    const char* msg = "VITORIA!";
        for (const char* c = msg; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }

        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(-0.35f, -0.1f);
        const char* restartMsg = "Para reiniciar pressione espaco";
        for (const char* c = restartMsg; *c != '\0'; ++c) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
    }
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.95f, 0.9f);
    std::string vidasText = "Vidas: " + std::to_string(vidas);
    for (char c : vidasText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    for (auto& alien : aliens) {
        alien.draw(alien.x, alien.y);
    }
    for (auto& shoot : shoots) {
        shoot.draw();
    }
    for (auto& nave : naves) {
        nave.desenha();
    }
    if (alienBoss && alienBoss->life > 0) {
        alienBoss->draw(alienBoss->x, alienBoss->y);
    }
}
void Game::respawnNave() {
    if (!naves.empty()) {
        naves[0].x = 0.0f;
        naves[0].y = -0.85f;
    }
}

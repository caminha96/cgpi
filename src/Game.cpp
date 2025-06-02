#include "Game.h"
#include <GL/glut.h>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "AlienBoss.h"
#include <string>  

extern Game game;
Game::Game() : direction(0.02f), estadoJogo(PLAYING), nivel(1), aliensMortos(0), vidas(3), alienBoss(nullptr) {
    initAliens();
    initNave();
}
Game::~Game() {
    delete alienBoss;
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
    if (!naves.empty()) {
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
    for (auto& tiro : shoots) {
        if (tiro.direction == -1) {
            if (!naves.empty() && colidiu(tiro, naves[0])) {
                tiro.active = false;
                vidas--;

                if (vidas <= 0) {
                    estadoJogo = GAME_OVER;
                } else {
                    respawnNave();
                }
                break;
            }
        }
        if (tiro.direction == +1) {
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
            if (nivel == 2 && aliens.empty() && alienBoss == nullptr) {
                alienBoss = new AlienBoss(0.0f, 0.8f);
            }
        }
    }
    aliens.erase(
        std::remove_if(aliens.begin(), aliens.end(),
        [](const Alien& a) { return a.y < -900; }),
        aliens.end()
    );

    if (nivel == 2 && aliens.empty() && alienBoss == nullptr) {
        alienBoss = new AlienBoss(0.0f, 0.8f);
    }
}
void Game::update() {
    if (estadoJogo == GAME_OVER) return;
    bool changeDirection = false;
    for (auto& alien : aliens) {
        alien.move(direction, 0);

        if (alien.x > 0.9f || alien.x < -0.9f) {
            changeDirection = true;
        }

        if (alien.y < -0.8f) {
            estadoJogo = GAME_OVER;
        }
    }
    if (changeDirection) {
        direction = -direction;
        for (auto& alien : aliens) {
            alien.move(0, -0.01f);
        }
    }
    int chanceTiro = (nivel == 1) ? 5 : 15;
    if (!aliens.empty() && (rand() % 1000) < chanceTiro) {
        alienShoot(rand() % aliens.size());
    }
    if (nivel == 2) {
        static float zigzagOffset = 0.01f;
        static bool esquerda = false;
        for (auto& alien : aliens) {
            alien.move(esquerda ? -zigzagOffset : zigzagOffset, -0.005f);
        }
        esquerda = !esquerda;
    }
    checarColisoes();
    updateShoots();
    if (alienBoss && alienBoss->life > 0) {
        static float bossTime = 0.0f;
        bossTime += 0.03f;
        alienBoss->x = 0.7f * sin(bossTime);
        alienBoss->y = 1.0f + 0.2f * sin(bossTime * 0.5f);
    }
    if (alienBoss && alienBoss->life > 0) {
        int chanceTiro = 40; // Ajuste conforme dificuldade
        if ((rand() % 1000) < chanceTiro) {
            bossShoot();
        }
    }

}
void Game::draw() {
    static float bossX = 0.0f;
    static float bossSpeed = 0.01f;
    static float bossAngle = 0.0f;
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

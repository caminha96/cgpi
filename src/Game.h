#pragma once  
#include <vector>
#include "Alien.h"
#include "Shoot.h"
#include "Nave.h"
#include "AlienBoss.h"

/*
 * GameState
 * Enumera os possíveis estados do jogo
 */
enum GameState {
    PLAYING,    ///< Jogo em andamento normal
    GAME_OVER,
    VITORIA   ///< Fim de jogo (derrota)
};

struct Star {
    float x, y;       // Posição da estrela
    float speed;      // Velocidade de movimento da estrela
    float brightness; // Brilho (afetará a cor)
};

/*
 * Game
 * Classe principal que gerencia toda a lógica do jogo
 * 
 * Controla entidades, estados, colisões e fluxo do jogo.
 */
class Game {
public:
    // ENTIDADES DO JOGO
    std::vector<Alien> aliens;   ///< Vetor de aliens inimigos
    std::vector<Nave> naves;     ///< Vetor contendo a(s) nave(s) do jogador
    std::vector<Shoot> shoots;   ///< Vetor de tiros (aliados e inimigos)

    // ESTADO DO JOGO
    float direction;             ///< Direção atual dos aliens (-1 = esquerda, 1 = direita)
    GameState estadoJogo;        ///< Estado atual (PLAYING ou GAME_OVER)
    AlienBoss* alienBoss;        ///< Ponteiro para o chefe final (opcional)
    int nivel;                   ///< Nível atual de dificuldade
    int aliensMortos;            ///< Contador de aliens destruídos
    int vidas;                   ///< Vidas restantes do jogador

    /*
     * Construtor - Inicializa o jogo com valores padrão
     */
    Game();

    /*
     * Destrutor - Libera recursos alocados
     */
    ~Game();

    // INICIALIZAÇÃO
    void initAliens();  ///< Cria a formação inicial de aliens
    void initNave();    ///< Posiciona a nave do jogador

    // CONTROLE PRINCIPAL
    void update();  ///< Atualiza toda a lógica do jogo
    void draw();    ///< Renderiza todos os elementos na tela

    // SISTEMA DE TIROS
    void alienShoot(int index);  ///< Faz um alien específico atirar
    void naveShoot();            ///< Dispara tiro da nave do jogador
    void updateShoots();         ///< Atualiza posição de todos os tiros

    // CONTROLES DA NAVE
    void moveNaveEsquerda();  ///< Move nave para esquerda
    void moveNaveDireita();   ///< Move nave para direita

    // GERENCIAMENTO DO JOGO
    void restart();          ///< Reinicia o jogo completamente
    void checarColisoes();   ///< Verifica todas as colisões

    void drawBossHealthBar() const;

    void bossShoot();

    /*
     * Verifica colisão entre tiro e nave
     * tiro: Referência ao objeto Shoot
     * nave: Referência ao objeto Nave
     * true: se houve colisão, false caso contrário
     */
    static bool colidiu(const Shoot& tiro, const Nave& nave);

private:
    /*
     * Reposiciona a nave após perder vida
     * 
     * Chamado quando o jogador leva dano mas ainda tem vidas restantes.
     * Posiciona a nave no centro da parte inferior da tela.
     */
    void respawnNave();
    // Adicionado: Membros e métodos para o fundo de estrelas
    std::vector<Star> stars;
    void initStars(int numberOfStars = 200); // Para inicializar as estrelas
    void updateStars();                      // Para mover as estrelas
    void drawStars();                        // Para desenhar as estrelas
};
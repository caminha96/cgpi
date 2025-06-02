#pragma once  

/**
 * Nave
   Classe que controla a espaçonave do jogador
 * 
 * Gerencia posição, movimento e renderização da nave do jogador.
 * A nave é representada por uma matriz de pixels e pode se mover horizontalmente.
 */
class Nave {
public:
    float x, y;          ///< Posição atual da nave no espaço 2D (coordenadas centrais)
    int matriz[30][30]{}; ///< Matriz que define o formato pixelado da nave (valores correspondem a cores)

    /**
     * Construtor da nave
     * startX: Posição inicial no eixo X
     * startY: Posição inicial no eixo Y
     * 
     * Inicializa a nave nas coordenadas especificadas e prepara a matriz de desenho.
     */
    Nave(float startX, float startY);

    /*
     * Renderiza a nave na tela
     * 
     * Desenha a nave usando a matriz de pixels, convertendo os valores em quadrados coloridos.
     * O desenho é feito com base na posição atual (x,y) da nave.
     */
    void desenha() const;

    /*
     * Move a nave para a esquerda
     * 
     * Atualiza a posição X da nave, garantindo que não saia dos limites da tela.
     * A velocidade de movimento é fixa (deve ser definida na implementação).
     */
    void moverEsquerda();

    /*
     * Move a nave para a direita
     * 
     * Atualiza a posição X da nave, garantindo que não saia dos limites da tela.
     * A velocidade de movimento é fixa (deve ser definida na implementação).
     */
    void moverDireita();
};
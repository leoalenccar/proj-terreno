#ifndef TERRENO_H
#define TERRENO_H

#include "../imagem/imagem.h"
#include <string>

class Terreno
{
    int expoente;
    int altura, largura;
    int **mapa;
    unsigned int sementeInicial;
    unsigned int semente;
    int altMinimo, altMaximo;

    // aloca memória para o mapa
    void alocarEspaco(int alt, int larg);

    // libera memória
    void limpar();

    // calcula 2^n + 1
    int potencia(int n);

    // gerador de números pseudoaleatórios (LCG)
    int gerarNumero();

    // etapa diamond
    // vertical e horizontal
    void diamond(int linha, int coluna, int alcance, int variacao);

    // etapa square
    void square(int linha, int coluna, int alcance, int variacao);

    // algoritmo principal de geração de terreno
    void diamondSquare(int tamanho, int variacao);

public:

    // construtor
    Terreno(int exp = 0, int seed = 1, int min = 0, int max = 100);

    // destrutor
    ~Terreno();

    // retorna largura do terreno
    int obterLargura();

    // retorna altura do terreno
    int obterAltura();

    // retorna a semente inicial
    int obterSemente();

    // retorna altura mínima
    int obterAltMinimo();

    // retorna altura máxima
    int obterAltMaximo();

    // retorna a altura em uma posição específica
    int obterAltura(int lin, int col);

    // insere uma altura no mapa
    void inserirAltura(int lin, int col, int alt);

    // gera valor aleatório dentro do intervalo [altMinimo, altMaximo]
    int aleatorio();

    // gera valor aleatório dentro de um intervalo específico
    int aleatorio(int minimo, int maximo);

    // gera o mapa usando diamond-square
    void gerarMapa();

    // converte o terreno em imagem usando uma paleta de cores
    Imagem carregarTerreno(std::string arquivoPALETA, float fator, int dist, int map);

    // salva o mapa em arquivo
    bool salvarHeightMap(std::string arquivo);

    // lê um mapa de um arquivo
    bool lerHeightMap(std::string arquivo);
};

#endif
#ifndef IMAGEM_H
#define IMAGEM_H

#include <string>
#include "../cor.h"

// define Pixel como Cor
using Pixel = Cor;

class Imagem
{
    int altura, largura;
    Pixel **pixels;

    // aloca memória para a matriz de pixels
    void alocarEspaco(int alt, int larg);

    // libera a memória alocada (usado no destrutor e em leituras)
    void limpar();

public:
    Imagem(int alt = 0, int larg = 0);

    ~Imagem();

    int obterLargura();

    int obterAltura();

    // altera a cor de um pixel (x, y)
    // retorna false se a posição for inválida
    bool pintar(int x, int y, Cor cor);

    // retorna a cor do pixel (x, y)
    Cor obterCor(int x, int y);

    // lê uma imagem no formato PPM a partir de arquivo
    bool lerPPM(std::string arquivo);

    // salva a imagem atual no formato PPM
    bool salvarPPM(std::string arquivo);
};

#endif
#ifndef PALETA_H
#define PALETA_H

#include <string>
#include "../cor.h"

class Paleta
{
    int capacidade;
    int tamanho;
    Cor *cores;

    // função que aumenta a capacidade do array
    void aumentarCapacidade();

public:

    // construtor: inicializa a paleta com capacidade = 1
    Paleta(int cap = 1);

    // construtor: inicializa a paleta a partir de um arquivo
    Paleta(std::string arquivo);

    // destrutor
    ~Paleta();

    // retorna a quantidade de cores armazenadas
    int obterTamanho();

    // adiciona uma nova cor à paleta
    void adicionarCor(Cor cor);

    // retorna a cor armazenada na posição n
    Cor obterCor(int n);
};

#endif
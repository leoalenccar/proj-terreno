#ifndef SEQUENCIA_H
#define SEQUENCIA_H

// template permite que a classe funcione com qualquer tipo de dado
template <typename S>

class Sequencia
{
    int capacidade;
    int quantidade;
    S *dados;

    // função responsável por aumentar a capacidade do array
    // dobra o tamanho atual e copia os elementos antigos
    void aumentarCapacidade();

public:

    // construtor
    Sequencia(int cap = 2);

    // destrutor
    ~Sequencia();

    // retorna a quantidade atual de elementos
    int obterTamanho(){return quantidade;}

    // adiciona um novo elemento ao final da sequência
    // caso a capacidade seja atingida, dobra o tamanho do array
    void adicionar(S n);

    // operador de acesso
    // permite acessar ou modificar elementos pelo índice
    S &operator[](int indice);

    // remove o último elemento da sequência
    void removerUltimo();
};

#endif
#include "sequencia.h"
#include <iostream>

template <typename S>
void Sequencia<S>::aumentarCapacidade()
{
    capacidade *= 2;
    S *novo = new S[capacidade];

    for (int i = 0; i < quantidade; i++)
    {
        novo[i] = dados[i];
    }

    delete[] dados;

    dados = novo;
}

template <typename S>
Sequencia<S>::Sequencia(int cap) : capacidade(cap), quantidade(0)
{
    dados = new S[capacidade];
}

template <typename S>
Sequencia<S>::~Sequencia()
{
    delete[] dados;
}

template <typename S>
int Sequencia<S>::obterTamanho(){return quantidade;}

template <typename S>
void Sequencia<S>::adicionar(S n)
{
    if (tamanho >= capacidade)
    {
        aumentarCapacidade();
    }

    dados[quantidade] = n;

    quantidade++;
}

template <typename S>
S &Sequencia<S>::operator[](int indice)
{
    if (indice < 0 || indice >= quantidade)
    {
        std::cerr << "Erro: índice inválido!" << std::endl;
    }
    return dados[indice];
}

template <typename S>
void Sequencia<S>::removerUltimo()
{
    if (quantidade <= 0)
    {
        std::cerr << "Erro: remoção de sequência vazia!" << std::endl;
    }

    quantidade--;
}
#include "terreno.h"
#include "../imagem/imagem.h"
#include "../paleta/paleta.h"
#include <iostream>
#include <cmath>
#include <fstream>

void Terreno::alocarEspaco(int alt, int larg)
{
    mapa = new int *[alt];
    for (int i = 0; i < alt; i++)
    {
        mapa[i] = new int[larg];
    }
}

void Terreno::limpar()
{
    // verifica se há memória alocada
    if (mapa == nullptr)return;

    for (int i = 0; i < altura; i++)
    {
        delete[] mapa[i];
    }

    delete[] mapa;

    mapa = nullptr;
}


// 2^n + 1
int Terreno::potencia(int n)
{
    if (n == 0)
    {
        return 1;
    }
    return std::pow(2, n) + 1;
}

// gerador de números pseudoaleatórios (LCG - Linear Congruential Generator)
int Terreno::gerarNumero()
{
    // A = 1103515245, C = 12345, M = 2^31 - 1
    semente = (semente * 1103515245 + 12345) & 0x7fffffff;
    return semente;
}

void Terreno::diamond(int linha, int coluna, int alcance, int variacao)
{
    int cont = 0;
    float media = 0.0;

    // verifica o vizinho de cima
    if (linha - alcance >= 0)
    {
        media += mapa[linha - alcance][coluna];
        cont++;
    }

    // verifica o vizinho de baixo
    if (linha + alcance < altura)
    {
        media += mapa[linha + alcance][coluna];
        cont++;
    }

    // verifica o vizinho da esquerda
    if (coluna - alcance >= 0)
    {
        media += mapa[linha][coluna - alcance];
        cont++;
    }

    // verifica o vizinho da direita
    if (coluna + alcance < largura)
    {
        media += mapa[linha][coluna + alcance];
        cont++;
    }

    // não tem vizinhos válidos
    if (cont == 0)
    {
        mapa[linha][coluna] = aleatorio(-variacao, variacao);
        return;
    }

    // tem vizinhos válidos (cont > 0)
    // calcula a média dos valores vizinhos e adiciona um ruído aleatório
    if (cont > 0)
    {
        media /= cont;

        int ruido = aleatorio(-variacao, variacao);

        int novoValor = (int)(media + ruido);

        mapa[linha][coluna] = novoValor;
    }
}


void Terreno::square(int linha, int coluna, int alcance, int variacao)
{
    int cont = 0;
    float media = 0.0;

    // verifica o vizinho superior esquerdo
    if (linha - alcance >= 0 && coluna - alcance >= 0)
    {
        media += mapa[linha - alcance][coluna - alcance];
        cont++;
    }

    // verifica o vizinho superior direito
    if (linha - alcance >= 0 && coluna + alcance < largura)
    {
        media += mapa[linha - alcance][coluna + alcance];
        cont++;
    }

    // verifica o vizinho inferior esquerdo
    if (linha + alcance < altura && coluna - alcance >= 0)
    {
        media += mapa[linha + alcance][coluna - alcance];
        cont++;
    }

    // verifica o vizinho inferior direito
    if (linha + alcance < altura && coluna + alcance < largura)
    {
        media += mapa[linha + alcance][coluna + alcance];
        cont++;
    }

    // não tem vizinhos válidos
    if (cont == 0)
    {
        mapa[linha][coluna] = aleatorio(-variacao, variacao);
        return;
    }

    // tem vizinhos válidos (cont > 0)
    // calcula a média dos valores vizinhos e adiciona um ruído aleatório
    if (cont > 0)
    {
        media /= cont;

        int ruido = aleatorio(-variacao, variacao);

        int novoValor = (int)(media + ruido);

        mapa[linha][coluna] = novoValor;
    }
}

void Terreno::diamondSquare(int tamanho, int variacao)
{
    int metade = tamanho / 2;

    while (metade >= 1)
    {
        // PASSO SQUARE
        for (int linha = metade; linha < tamanho; linha += (metade * 2))
        {
            for (int coluna = metade; coluna < tamanho; coluna += (metade * 2))
            {
                // calcula valor baseado nos 4 cantos (diagonais)
                square(linha, coluna, metade, variacao);
            }
        }

        // PASSO DIAMOND
        for (int linha = 0; linha < tamanho; linha += metade)
        {
            for (int coluna = ((linha / metade) % 2 == 0 ? metade : 0); coluna < tamanho; coluna += (metade * 2))
            {
                diamond(linha, coluna, metade, variacao);
            }
        }

        metade /= 2;

        variacao *= 0.6;

        if (variacao < 1)
        {
            variacao = 1;
        }
    }
}

Terreno::Terreno(int exp, int seed, int min, int max)
    : expoente(exp), sementeInicial(seed), semente(seed), altMinimo(min), altMaximo(max)
{
    // calcula dimensões do mapa
    altura = potencia(expoente);
    largura = potencia(expoente);

    alocarEspaco(altura, largura);

    // inicializa o mapa com zero
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            mapa[i][j] = 0;
        }
    }
}


Terreno::~Terreno()
{
    limpar();
}

int Terreno::obterLargura(){return largura;}

int Terreno::obterAltura(){return altura;}

int Terreno::obterSemente(){return sementeInicial;}

int Terreno::obterAltMinimo(){return altMinimo;}

int Terreno::obterAltMaximo(){return altMaximo;}

int Terreno::obterAltura(int lin, int col)
{
    if ((col >= largura || lin >= altura) || (col < 0 || lin < 0))
    {
        std::cerr << "Erro! Posição inválida.\n";
        static int erro = 0;
        return erro;
    }
    return mapa[lin][col];
}


// gera um valor aleatório dentro do intervalo [altMinimo, altMaximo]
int Terreno::aleatorio()
{
    int intervalo = (altMaximo - altMinimo) + 1;
    int valor = gerarNumero();
    return altMinimo + (valor % intervalo);
}

// gera valor aleatório entre minimo e maximo
int Terreno::aleatorio(int minimo, int maximo)
{
    if (maximo < minimo)
    {
        int temp = minimo;
        minimo = maximo;
        maximo = temp;
    }

    int valor = gerarNumero();

    double t = static_cast<double>(valor) / 0x7FFFFFFF;

    int novoValor = minimo + static_cast<int>(t * (maximo - minimo + 1));

    if (novoValor > maximo)
    {
        novoValor = maximo;
    }

    return novoValor;
}

void Terreno::inserirAltura(int lin, int col, int alt)
{
    mapa[lin][col] = alt;
}

void Terreno::gerarMapa()
{
    // canto superior esquerdo
    mapa[0][0] = aleatorio();

    // canto superior direito
    mapa[0][largura - 1] = aleatorio();

    // canto inferior esquerdo
    mapa[altura - 1][0] = aleatorio();

    // canto inferior direito
    mapa[altura - 1][largura - 1] = aleatorio();

    int menor = altMinimo;
    int maior = altMaximo;

    if (altMaximo < altMinimo)
    {
        menor = altMaximo;
        maior = altMinimo;
    }

    int distInicial = (maior - menor) / 2;
    if (distInicial < 1)
    {
        distInicial = 1;
    }

    diamondSquare(largura, distInicial);

    // ajusta valores para permanecerem dentro dos limites
    for (int linha = 0; linha < altura; linha++)
    {
        for (int coluna = 0; coluna < largura; coluna++)
        {
            if (mapa[linha][coluna] < altMinimo)
                mapa[linha][coluna] = altMinimo;
            if (mapa[linha][coluna] > altMaximo)
                mapa[linha][coluna] = altMaximo;
        }
    }
}

Imagem Terreno::carregarTerreno(std::string arquivoPALETA, float fator, int dist, int map)
{
    Paleta paleta(arquivoPALETA);

    int numCores = paleta.obterTamanho();

    Imagem img(altura, largura);

    int min = obterAltMinimo();
    int max = obterAltMaximo();

    int sombreados = 0;

    for (int y = 0; y < altura; y++)
    {
        for (int x = 0; x < largura; x++)
        {
            int alturaAtual = mapa[y][x];

            // normaliza altura para intervalo [0,1]
            double t = double(alturaAtual - min) / (max - min);

            // mapeia para índice da paleta
            int indice = static_cast<int>(t * (numCores - 1));

            if (indice < 0) indice = 0;
            if (indice >= numCores) indice = numCores - 1;

            Cor cor = paleta.obterCor(indice);

            // cálculo de sombra baseado no vizinho noroeste
            int limitarAgua = min + (int)((max - min) * 0.28);

            if (y - dist >= 0 && x - dist >= 0 && alturaAtual > limitarAgua)
            {
                int alturaNoroeste = mapa[y - dist][x - dist];
                if (alturaAtual < alturaNoroeste)
                {
                    // escurece a cor
                    cor.r = static_cast<unsigned char>(cor.r * fator);
                    cor.g = static_cast<unsigned char>(cor.g * fator);
                    cor.b = static_cast<unsigned char>(cor.b * fator);
                }
            }
            img.pintar(y, x, cor);
        }
    }
    return img;
}

bool Terreno::salvarHeightMap(std::string arquivo)
{
    std::ofstream file(arquivo);

    if (file.is_open() == false)
    {
        return false;
    }

    file << altura << " " << largura << std::endl;

    file << sementeInicial << std::endl;

    file << altMinimo << " " << altMaximo << std::endl;

    for (int linha = 0; linha < altura; linha++)
    {
        for (int coluna = 0; coluna < largura; coluna++)
        {
            file << mapa[linha][coluna];

            if (coluna < largura - 1)
            {
                file << " ";
            }
        }

        file << std::endl;
    }

    return true;
}

bool Terreno::lerHeightMap(std::string arquivo)
{
    std::ifstream file(arquivo);

    if (file.is_open() == false)
    {
        return false;
    }

    file >> altura >> largura;

    file >> sementeInicial;
    semente = sementeInicial;

    file >> altMinimo >> altMaximo;

    alocarEspaco(altura, largura);

    for (int linha = 0; linha < altura; linha++)
    {
        for (int coluna = 0; coluna < largura; coluna++)
        {
            int altitude;
            file >> altitude;
            mapa[linha][coluna] = altitude;
        }
    }

    return true;
}
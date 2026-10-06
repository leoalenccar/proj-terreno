#include "imagem.h"
#include <iostream>
#include <fstream>

void Imagem::alocarEspaco(int alt, int larg)
{
    limpar();

    altura = alt;
    largura = larg;

    pixels = new Pixel *[altura];

    for (int i = 0; i < altura; i++)
    {
        pixels[i] = new Pixel[largura];

        // inicializa todos os pixels com preto
        for (int j = 0; j < largura; j++)
        {
            pixels[i][j] = Pixel{0, 0, 0};
        }
    }
}

void Imagem::limpar()
{
    if (pixels == nullptr) return;

    for (int i = 0; i < altura; i++)
    {
        delete[] pixels[i];
    }

    delete[] pixels;

    pixels = nullptr;
    
    largura = 0;
    altura = 0;
}

// construtor
Imagem::Imagem(int alt, int larg) : altura(alt), largura(larg), pixels(nullptr)
{
    if (larg > 0 && alt > 0)
    {
        alocarEspaco(alt, larg);
    }
}

// destrutor
Imagem::~Imagem()
{
    limpar();
}

int Imagem::obterLargura(){return largura;}

int Imagem::obterAltura(){return altura;}

bool Imagem::pintar(int linha, int coluna, Cor cor)
{
    // retorna false caso a posição seja inválida ou não haja imagem
    if (pixels == nullptr)
    {
        return false;
    }
    if (linha < 0 || linha >= altura || coluna < 0 || coluna >= largura)
    {
        return false;
    }

    // altera o valor do pixel
    pixels[linha][coluna] = cor;

    return true;
}

Cor Imagem::obterCor(int linha, int coluna)
{
    Cor preto = {0, 0, 0};

    // caso inválido, retorna preto (0,0,0)
    if (pixels == nullptr)
    {
        return preto;
    }
    if (linha < 0 || linha >= altura || coluna < 0 || coluna >= largura)
    {
        return preto;
    }

    return pixels[linha][coluna];
}

bool Imagem::lerPPM(std::string arquivo)
{
    // abre o arquivo para leitura
    std::ifstream file(arquivo);

    // verifica se o arquivo foi aberto corretamente
    if (file.is_open() == false)
    {
        return false;
    }

    std::string formato;
    int largura_arquivo, altura_arquivo;
    int maxIntensidade;

    file >> formato >> largura_arquivo >> altura_arquivo >> maxIntensidade;

    largura = largura_arquivo;
    altura = altura_arquivo;

    alocarEspaco(altura, largura);

    for (int linha = 0; linha < altura; linha++)
    {
        for (int coluna = 0; coluna < largura; coluna++)
        {
            int R, G, B;

            file >> R >> G >> B;

            // armazena convertendo para unsigned char
            pixels[linha][coluna] = Pixel{
                static_cast<unsigned char>(R),
                static_cast<unsigned char>(G),
                static_cast<unsigned char>(B)};
        }
    }

    return true;
}

bool Imagem::salvarPPM(std::string arquivo)
{
    std::ofstream file(arquivo);

    if (!file.is_open())return false;

    // escreve cabeçalho do PPM
    file << "P3\n";
    file << largura << " " << altura << "\n";
    file << "255\n";

    // escreve os pixels linha por linha
    for (int linha = 0; linha < altura; linha++)
    {
        for (int coluna = 0; coluna < largura; coluna++)
        {
            file << static_cast<int>(pixels[linha][coluna].r) << " "
                 << static_cast<int>(pixels[linha][coluna].g) << " "
                 << static_cast<int>(pixels[linha][coluna].b);

            if (coluna < largura - 1)
                file << " ";
        }
        file << "\n";
    }

    return true;
}
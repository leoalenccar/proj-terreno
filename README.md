# proj-terreno

Projeto da disciplina ITP para geração procedural de mapas de terrenos aleatórios em C++.

O programa gera um mapa de altitudes usando o algoritmo **Diamond-Square** e o converte em uma imagem colorida no formato PPM com sombreamento.

![Exemplo de terreno](./src/exemplo/exemplo.png)

## Estrutura do projeto

```
src/
├── cor.h
├── sequencia/
│   ├── sequencia.h
│   └── sequencia.cpp
├── paleta/
│   ├── paleta.h
│   └── paleta.cpp
├── imagem/
│   ├── imagem.h
│   └── imagem.cpp
├── terreno/
│   ├── terreno.h
│   └── terreno.cpp
├── exemplo/
│   ├── exemplo.png
│   ├── exemplo.ppm
│   └── matrizAltitude.r16
└── main/
    ├── main.cpp
    ├── cores.hex
    └── cores_60.hex
```

## Como compilar

```bash
cd src/main

g++ main.cpp ../paleta/paleta.cpp ../imagem/imagem.cpp ../terreno/terreno.cpp -o gerador
```

## Como executar

```bash
./gerador
```

O programa irá pedir:

- **Paleta de cores**: escolha entre 30 ou 60 cores
- **Tamanho do mapa**: selecione um tamanho com opções de 17×17 até 1025×1025
- **Semente**: digite um número inteiro (a mesma semente sempre gera o mesmo terreno)
- **Arquivo de saída**: digite um nome para o arquivo em que o mapa será salvo

## Dependências

A imagem gerada pode ser visualizada com a extensão [PPM Viewer para VS Code](https://marketplace.visualstudio.com/items?itemName=ngtystr.ppm-pgm-viewer-for-vscode).

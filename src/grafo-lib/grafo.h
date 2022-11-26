#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INFINITO  2147483647 // Como o algoritmo de floyd-Warshall utiliza uma marcação INFINITO, foi utilizado
                             // o maior numero que uma variavel do tipo int pode armazenar como INFINITO

typedef struct vertVizi* apontadorVerticeVizinho;
typedef struct vertVizi{
    int numeroDoVertice;
    float pesoAresta;
    apontadorVerticeVizinho proximo;
}VerticeVizinho;

typedef struct{
    int numeroDoVertice;
    apontadorVerticeVizinho primeiro;
    apontadorVerticeVizinho ultimo;
}Vertice;

typedef struct{
    int quantidadeDeVertices;
    Vertice *vertice;
}Grafo;

bool leituraSequenciaGraus(Grafo *grafo, char nomeArquivo[]);

int ordemGrafo(Grafo *grafo);

int tamanhoGrafo(Grafo *grafo);

char* verticesVizinhos(Grafo *grafo, int vertice);

int verticeGrau(Grafo *grafo, int vertice);

char* sequenciaGrausGrafo(Grafo *grafo);

float excentricidadeVertice(Grafo *grafo, int vertice);

float raioGrafo(Grafo *grafo);

float diametroGrafo(Grafo *grafo);

char* centroGrafo(Grafo *grafo);

float centralidadeProximidade(Grafo *grafo, int vertice);

char* caminhoMinimoEntreVertice(Grafo *grafo, int verticeOrigem, int verticeDestino);

float distanciaEntreVertice(Grafo *grafo, int verticeOrigem, int verticeDestino);

void buscaProfundidade(Grafo *grafo, int vertice);

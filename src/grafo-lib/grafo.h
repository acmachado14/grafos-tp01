#include <stdio.h>
#include <stdlib.h>

typedef struct vertVizi{
    int numeroDovertice;
    float pesoAresta;
    struct vertVizi *proximo;
    struct vertVizi *ultimo;
}VerticeVizinho;

typedef struct{
    int numeroDoVertice;
    VerticeVizinho *verticeVizinho;
}Vertice;

typedef struct{
    int quantidadeDeVertices;
    Vertice *vertice;
}Grafo;

void inicialiGrafo(Grafo *grafo, int quantidadeVertices);
void inserirVertices(Vertice *vertice, int numeroDoVertice);
void setQuantidadeVertices(Grafo *grafo, int quantidadeVertices);
int getQuantidadeVertices(Grafo *grafo);
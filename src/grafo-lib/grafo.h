#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void inicializaGrafo(Grafo *grafo, int quantidadeVertices);

void inserirVertices(Vertice *vertice, int numeroDoVertice);

void setQuantidadeVertices(Grafo *grafo, int quantidadeVertices);

int getQuantidadeVertices(Grafo *grafo);

void inserirAresta(Grafo *grafo, int verticeOrigem, int verticeDestino, float pesoAresta);

void inserirArestaAuxiliar(Vertice *vertice, int verticeDestino, float pesoAresta);

void leituradados(Grafo *grafo);

int ordemGrafo(Grafo *grafo);

int tamanhoGrafo(Grafo *grafo);

char* verticesVizinhos(Grafo *grafo, int verticeOrigem);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define infinito  2147483647 // Como o algoritmo de floyd-Warshall utiliza uma marcação infinito, foi utilizado 
                             // o maior numero que uma variavel do tipo int pode armazenar como infinito

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

bool leituraSequenciaGraus(Grafo *grafo, char nomeArquivo[]);

int ordemGrafo(Grafo *grafo);

int tamanhoGrafo(Grafo *grafo);

char* verticesVizinhos(Grafo *grafo, int vertice);

int verticeGrau(Grafo *grafo, int vertice);

char* sequenciaGrausGrafo(Grafo *grafo);

void quickSort(int **sequenciaGraus, int Esq, int Dir);

void particaoQuickSort(int **sequenciaGraus, int Esq, int Dir,int *i, int *j);

void  FloydWarshall(Grafo *grafo, float ***matrizDistancia, int ***matrizCaminho);

float excentricidadeVertice(Grafo *grafo, int vertice);

float raioGrafo(Grafo *grafo);

float diametroGrafo(Grafo *grafo);

char* centroGrafo(Grafo *grafo);

float centralidadeProximidade(Grafo *grafo, int vertice);

char* caminhoMinimoEntreVertice(Grafo *grafo, int verticeOrigem, int verticeDestino);

float distanciaEntreVertice(Grafo *grafo, int verticeOrigem, int verticeDestino);

void buscaProfundidade(Grafo *grafo, int vertice);

void buscaProfundidadeAux(Grafo *grafo, int vertice, int *visitados, int ***arestas);
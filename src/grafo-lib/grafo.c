#include "grafo.h"

void inicializaGrafo(Grafo *grafo, int quantidadeVertices){
    setQuantidadeVertices(grafo, quantidadeVertices);
    grafo->vertice = (Vertice*)malloc(quantidadeVertices * sizeof(Vertice));
    for(int i = 0; i < quantidadeVertices; i++){
        inserirVertices(&grafo->vertice[i], i);
    }
}
void inserirVertices(Vertice *vertice, int numeroDoVertice){
    vertice->numeroDoVertice = numeroDoVertice;
    vertice->verticeVizinho = NULL;
}
void setQuantidadeVertices(Grafo *grafo, int quantidadeVertices){
    grafo->quantidadeDeVertices = quantidadeVertices;
}
int getQuantidadeVertices(Grafo *grafo){
    return grafo->quantidadeDeVertices;
}
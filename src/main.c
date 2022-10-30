#include "grafo-lib/grafo.h"

int main(){
    int i, j;
    Grafo grafo;
    char nomeArquivo[] = "Djikstra";
    leituraSequenciaGraus(&grafo, nomeArquivo);
    printf("Ordem grafo: %d\n", ordemGrafo(&grafo));
    printf("Tamanho grafo: %d\n", tamanhoGrafo(&grafo));
    printf("Vertices vizinhos do 5: %s\n", verticesVizinhos(&grafo, 5)); // exemplo
    printf("Grau do vertice 5: %d\n", verticeGrau(&grafo, 5));
    printf("Sequencia de graus: %s\n", sequenciaGrausGrafo(&grafo));
    printf("Busca de Profundidade: \n");
    buscaProfundidade(&grafo,1);
    printf("Excentricidade do vertice 1: %f\n", excentricidadeVertice(&grafo, 1));
    printf("Raio grafo: %f\n", raioGrafo(&grafo));
    printf("Diametro grafo: %f\n", diametroGrafo(&grafo));
    printf("Centro grafo: %s\n", centroGrafo(&grafo));
    printf("Centralidade proximidade do vertice 5: %f\n", centralidadeProximidade(&grafo, 5));
    printf("Distancia entre vertice: %f\n", distanciaEntreVertice(&grafo, 1, 7));
    printf("Caminho: %s\n", caminhoMinimoEntreVertice(&grafo, 1, 9));
    return 0;
}

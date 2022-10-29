#include "grafo-lib/grafo.h"

int main(){
    int i, j;
    Grafo grafo;
    leituraSequenciaGraus(&grafo);
    printf("Ordem grafo: %d\n", ordemGrafo(&grafo));
    printf("Tamanho grafo: %d\n", tamanhoGrafo(&grafo));
    printf("Vertices vizinhos do 5: %s\n", verticesVizinhos(&grafo, 5)); // exemplo
    printf("Grau do vertice 5: %d\n", verticeGrau(&grafo, 5));
    printf("Sequencia de graus: %s\n", sequenciaGrausGrafo(&grafo));
    printf("Busca de Profundidade: \n");
    buscaProfundidade(&grafo,1);
    printf("Excentricidade: %f\n", excentricidadeVertice(&grafo, 1));
    return 0;
}

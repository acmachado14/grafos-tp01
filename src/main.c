#include "grafo-lib/grafo.h"

int main(){
    int i, j;
    Grafo grafo;
    leituradados(&grafo);
    printf("Ordem grafo: %d\n", ordemGrafo(&grafo));
    printf("Tamanho grafo: %d\n", tamanhoGrafo(&grafo));
    printf("Vertices vizinhos do 5: %s\n", verticesVizinhos(&grafo, 5)); // exemplo
    return 0;
}
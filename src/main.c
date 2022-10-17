#include "grafo-lib/grafo.h"

int main(){
    printf("Initial\n");
    int i, j;
    Grafo grafo;
    leituradados(&grafo);
    printf("Ordem grafo: %d\n", ordemGrafo(&grafo));
    printf("Tamanho grafo: %d\n", tamanhoGrafo(&grafo));
    return 0;
}
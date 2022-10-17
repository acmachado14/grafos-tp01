#include "grafo.h"

void inicializaGrafo(Grafo *grafo, int quantidadeVertices){
    setQuantidadeVertices(grafo, quantidadeVertices);
    grafo->vertice = (Vertice*)malloc(quantidadeVertices * sizeof(Vertice));
    for(int i = 0; i < quantidadeVertices; i++){
        inserirVertices(&grafo->vertice[i], i);
    }
}

void inserirVertices(Vertice *vertice, int numeroDoVertice){
    vertice->numeroDoVertice = numeroDoVertice + 1; // Incrementa 1 pois o vertice 1 esta na posicao 0, o vertice 2
                                                    // esta na posicao 1 e assim por adiante, na lista de adijacencia, 
                                                    // que foi criada na variaver 'vertice' que esta dentro da struct Grafo
    vertice->primeiro = NULL;
    vertice->ultimo = NULL;
}

void setQuantidadeVertices(Grafo *grafo, int quantidadeVertices){
    grafo->quantidadeDeVertices = quantidadeVertices;
}

int getQuantidadeVertices(Grafo *grafo){
    return grafo->quantidadeDeVertices;
}

void inserirAresta(Grafo *grafo, int verticeOrigem, int verticeDestino, float pesoAresta){
    inserirArestaAuxiliar(&grafo->vertice[verticeOrigem - 1], verticeDestino, pesoAresta);
    // Foi decrementado 1 pois o vertice 'verticeOrigem' esta uma possicao antes na lista de adijacencia
}

void inserirArestaAuxiliar(Vertice *vertice, int verticeDestino, float pesoAresta){
    if(vertice->primeiro == NULL){
        vertice->primeiro = (apontadorVerticeVizinho)malloc(sizeof(VerticeVizinho));
        vertice->ultimo = vertice->primeiro;
    }
    else{
        vertice->ultimo->proximo = (apontadorVerticeVizinho)malloc(sizeof(VerticeVizinho));
        vertice->ultimo = vertice->ultimo->proximo;
    }
    vertice->ultimo->proximo = NULL;
    vertice->ultimo->numeroDoVertice = verticeDestino;
    vertice->ultimo->pesoAresta = pesoAresta;
}

void leituradados(Grafo *grafo){
    char nomeArquivo[43];
    printf("Digite o nome do arquivo que sera lido: ");
    scanf("%s", nomeArquivo);
    char diretorio[50] = "routine/grafos-txt/";
    strcat(strcat(diretorio, nomeArquivo), ".txt");
    FILE *file;
    file = fopen(diretorio, "r");
    if(file == NULL){
        printf("Erro na abertura do arquivo de entrada !!!!!!!!\n");
        return;
    }
    int quantidadeDeVertices, verticeOrigem, verticeDestino;
    float pesoAresta;
    fscanf(file, "%d ", &quantidadeDeVertices);
    inicializaGrafo(grafo, quantidadeDeVertices);
    while (!feof(file)){
        fscanf(file,"%d %d %f", &verticeOrigem, &verticeDestino, &pesoAresta);
        inserirAresta(grafo, verticeOrigem, verticeDestino, pesoAresta);
    }
    fclose(file);
}

int ordemGrafo(Grafo *grafo){
    return getQuantidadeVertices(grafo);
}

int tamanhoGrafo(Grafo *grafo){
    int i, quantidadeArestas = 0;
    apontadorVerticeVizinho verticeVizinho;
    for(i = 0; i < getQuantidadeVertices(grafo); i++){
        verticeVizinho = grafo->vertice[i].primeiro;
        while (verticeVizinho != NULL){
            quantidadeArestas++;
            verticeVizinho = verticeVizinho->proximo;
        }
    }
    return quantidadeArestas;
}


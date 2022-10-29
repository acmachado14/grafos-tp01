#include "grafo.h"


void inicializaGrafo(Grafo *grafo, int quantidadeVertices){
    setQuantidadeVertices(grafo, quantidadeVertices);
    grafo->vertice = (Vertice*)malloc(quantidadeVertices * sizeof(Vertice));
    for(int i = 0; i < quantidadeVertices; i++){
        inserirVertices(&grafo->vertice[i], i + 1); // Incrementa 1 pois o vertice 1 esta na posicao 0, o vertice 2
                                                    // esta na posicao 1 e assim por adiante, na lista de adijacencia, 
                                                    // que foi criada na variaver 'vertice' que esta dentro da struct Grafo
    }
}

void inserirVertices(Vertice *vertice, int numeroDoVertice){
    vertice->numeroDoVertice = numeroDoVertice;
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
    inserirArestaAuxiliar(&grafo->vertice[verticeDestino - 1], verticeOrigem, pesoAresta);
    // Foi decrementado 1 pois o vertice 'verticeOrigem' esta uma possicao anterior na lista de adijacencia
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

void leituraSequenciaGraus(Grafo *grafo){
    char nomeArquivo[43] = "grafo1";
    //printf("Digite o nome do arquivo que sera lido: ");
    //scanf("%s", nomeArquivo);
    char diretorio[50] = "routine/grafos-txt/";
    strcat(strcat(diretorio, nomeArquivo), ".txt");
    FILE *file;
    file = fopen(diretorio, "r");
    if(file == NULL){ // Nao diferencia o nome de um arquivo com letra maiuscula para um arquivo com letra minuscula
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
    return quantidadeArestas / 2;
}

char* verticesVizinhos(Grafo *grafo, int vertice){
    apontadorVerticeVizinho verticeVizinho;
    char aux[20] = "";
    char *vertices = (char*)malloc(sizeof(char));
    char verticeAux[10];
    strcpy(vertices, aux);

    verticeVizinho = grafo->vertice[vertice - 1].primeiro;
    while (verticeVizinho != NULL){
        sprintf(verticeAux, "%d", verticeVizinho->numeroDoVertice);
        strcat(vertices, verticeAux);
        strcat(vertices, " ");
        verticeVizinho = verticeVizinho->proximo;
    }
    if(strlen(vertices) < 1){
        strcat(vertices, "O vertice nao possui vizinhos");
    }
    return vertices;
}

int verticeGrau(Grafo *grafo, int vertice){
    apontadorVerticeVizinho verticeVizinho;
    int grauVertice = 0;
    verticeVizinho = grafo->vertice[vertice - 1].primeiro;
    while (verticeVizinho != NULL){
        if(verticeVizinho->numeroDoVertice == vertice){
            grauVertice += 2;
        }
        else{
            grauVertice++;
        }
        verticeVizinho = verticeVizinho->proximo;
    }
    return grauVertice;
}

char* sequenciaGrausGrafo(Grafo *grafo){
    int quantidadeVertices = getQuantidadeVertices(grafo);
    int *sequenciaGraus;
    sequenciaGraus = (int*)malloc(quantidadeVertices * sizeof(int));
    int i;
    for(i = 0; i < quantidadeVertices; i++){
        sequenciaGraus[i] = verticeGrau(grafo, i + 1);
    }

    quickSort(&sequenciaGraus, 0, quantidadeVertices - 1);

    char aux[20] = "";
    char *sequeGraus = (char*)malloc(sizeof(char));
    char verticeAux[10];
    strcpy(sequeGraus, aux);

    for(i = 0; i < quantidadeVertices; i++){
        sprintf(verticeAux, "%d", sequenciaGraus[i]);
        strcat(sequeGraus, verticeAux);
        strcat(sequeGraus, " ");
    }
    return sequeGraus;
}

void quickSort(int **sequenciaGraus, int Esq, int Dir){
    int i, j;
    particaoQuickSort(sequenciaGraus , Esq, Dir, &i, &j);
    if (Esq < j){
        quickSort(sequenciaGraus, Esq, j);
    }
    if (i < Dir){
        quickSort(sequenciaGraus, i, Dir);
    }
}

void particaoQuickSort(int **sequenciaGraus, int Esq, int Dir,int *i, int *j){
    int pivo, aux;
    *i = Esq;
    *j = Dir;
    pivo = (*sequenciaGraus)[(*i + *j)/2]; // obtem o pivo
    do{
        while (pivo < (*sequenciaGraus)[*i]){
            (*i)++;
        }
        while (pivo > (*sequenciaGraus)[*j]){
            (*j)--;
        }
        if (*i <= *j){ 
            aux = (*sequenciaGraus)[*i];
            (*sequenciaGraus)[*i] = (*sequenciaGraus)[*j]; 
            (*sequenciaGraus)[*j] = aux;
            (*i)++; 
            (*j)--;
        }
    } while (*i <= *j);
}

void floydWarshall(Grafo *grafo, float ***matrizDistancia, int ***matrizCaminho){
    int i, j, k, quantidadeVertices;
    apontadorVerticeVizinho verticeVizinho;
    quantidadeVertices = getQuantidadeVertices(grafo);
    bool existeAresta;
    for(i = 0; i < quantidadeVertices; i++){
        for(j = 0; j < quantidadeVertices; j++){
            if(i == j){
                (*matrizDistancia)[i][j] = 0.0;
            }
            else{
                verticeVizinho = grafo->vertice[i].primeiro;
                existeAresta = false;
                while (verticeVizinho != NULL){
                    if(verticeVizinho->numeroDoVertice == j + 1){
                        existeAresta = true;
                        break;
                    }
                    verticeVizinho = verticeVizinho->proximo;
                }
                if(existeAresta){
                    (*matrizDistancia)[i][j] = verticeVizinho->pesoAresta;
                }
                else{
                    (*matrizDistancia)[i][j] = infinito;
                }
            }
        }
    }
    for(i = 0; i < quantidadeVertices; i++){
        for(j = 0; j < quantidadeVertices; j++){
            if((*matrizDistancia)[i][j] == infinito){
                (*matrizCaminho)[i][j] = 0;
            }
            else{
                (*matrizCaminho)[i][j] = i;
            }
        }
    }

    for(k = 0; k < quantidadeVertices; k++){
        for(i = 0; i < quantidadeVertices; i++){
            for(j = 0; j < quantidadeVertices; j++){
                if((*matrizDistancia)[i][j] > ((*matrizDistancia)[i][k] + (*matrizDistancia)[k][j])){
                    (*matrizDistancia)[i][j] = ((*matrizDistancia)[i][k] + (*matrizDistancia)[k][j]);
                    (*matrizCaminho)[i][j] = (*matrizCaminho)[k][j];
                }
            }
        }
    }
}

float excentricidadeVertice(Grafo *grafo, int vertice){
    int i, quantidadeVertices;
    float **matrizDistancia;
    int **matrizCaminho;
    float excentricidade = 0;
    quantidadeVertices = getQuantidadeVertices(grafo);
    matrizCaminho = (int**)malloc(quantidadeVertices * sizeof(int*));
    matrizDistancia= (float**)malloc(quantidadeVertices * sizeof(float*));
    for(i = 0; i < quantidadeVertices; i++){
        matrizCaminho[i] = (int*)malloc(quantidadeVertices * sizeof(int));
        matrizDistancia[i] = (float*)malloc(quantidadeVertices * sizeof(float));
    }
    floydWarshall(grafo, &matrizDistancia, &matrizCaminho);
    if(matrizDistancia[vertice - 1][vertice - 1] < 0){
        return infinito * -1;
    }
    for(i = 0; i < quantidadeVertices; i++){
        if(matrizDistancia[vertice - 1][i] > excentricidade){
            excentricidade = matrizDistancia[vertice - 1][i];
        }
    }
    return excentricidade; // Olhar novamente
}

float raioGrafo(Grafo *grafo){
    int i, quantidadeVertices;
    float raio, excentricidade;
    quantidadeVertices = getQuantidadeVertices(grafo);
    for(i = 0; i < quantidadeVertices; i++){
        excentricidade = excentricidadeVertice(grafo, i + 1);
        if(i == 0){
            raio = excentricidade;
        }
        else if(excentricidade < raio){
            raio = excentricidade;
        }
    }
    return raio;
}

float diametroGrafo(Grafo *grafo){
    int i, quantidadeVertices;
    float diametro, excentricidade;
    quantidadeVertices = getQuantidadeVertices(grafo);
    for(i = 0; i < quantidadeVertices; i++){
        excentricidade = excentricidadeVertice(grafo, i + 1);
        if(i == 0){
            diametro = excentricidade;
        }
        else if(excentricidade > diametro){
            diametro = excentricidade;
        }
    }
    return diametro;
}

char* centroGrafo(Grafo *grafo){
    char aux[20] = "";
    char *centro = (char*)malloc(sizeof(char));
    char vertice[11];
    int i, quantidadeVertices;
    float raio, excentricidade;
    quantidadeVertices = getQuantidadeVertices(grafo);
    for(i = 0; i < quantidadeVertices; i++){
        excentricidade = excentricidadeVertice(grafo, i + 1);

        if(i == 0){
            raio = excentricidade;
            sprintf(vertice, "%d", i + 1);
            strcat(centro, vertice);
            strcat(centro, " ");
        }
        else {
            if(excentricidade < raio){
                raio = excentricidade;
                sprintf(vertice, "%d", i + 1);
                strcat(centro, aux);
                strcat(centro, vertice);
                strcat(centro, " ");
            }
            if(excentricidade == raio){
                sprintf(vertice, "%d", i + 1);
                strcat(centro, vertice);
                strcat(centro, " ");
            }
        }

    }
}

float centralidadeProximidade(Grafo *grafo, int vertice){
    int i, quantidadeVertices;
    float **matrizDistancia;
    int **matrizCaminho;
    float centralidade = 0;
    bool existeCicuitoNegativo = false;
    quantidadeVertices = getQuantidadeVertices(grafo);
    matrizCaminho = (int**)malloc(quantidadeVertices * sizeof(int*));
    matrizDistancia= (float**)malloc(quantidadeVertices * sizeof(float*));
    for(i = 0; i < quantidadeVertices; i++){
        matrizCaminho[i] = (int*)malloc(quantidadeVertices * sizeof(int));
        matrizDistancia[i] = (float*)malloc(quantidadeVertices * sizeof(float));
    }
    floydWarshall(grafo, &matrizDistancia, &matrizCaminho);
    for(i = 0; i < quantidadeVertices; i++){
        if(matrizDistancia[i][i] < 0){
            existeCicuitoNegativo = true;
        }
        centralidade += matrizDistancia[vertice - 1][i];
    }
    if(existeCicuitoNegativo){
        return 0;
    }
    return (quantidadeVertices - 1) / centralidade;
}

void buscaProfundidade(Grafo *grafo, int vertice){
    int i, quantidadeVertices = getQuantidadeVertices(grafo);
    int *visitados;
    visitados = (int*)malloc(quantidadeVertices * sizeof(int));
    for(i = 0; i < quantidadeVertices; i++){
        visitados[i] = 0;
    }

    int **arestas;
    arestas = (int**)malloc(quantidadeVertices * sizeof(int*));
    for(i = 0; i < quantidadeVertices; i++){
        arestas[i] = (int*)malloc(quantidadeVertices * sizeof(int));
    }

    printf("Sequencias de vertices visitados: ");
    buscaProfundidadeAux(grafo, vertice, visitados, &arestas);
    printf("\n");

    printf("Arestas nao usadas: ");
    for(i = 0; i < quantidadeVertices; i++){
        for(int j = 0; j < quantidadeVertices; j++){
            if(arestas[i][j] == 0 && i != j){
                printf("%d%d ", i + 1, j + 1);
            }
        }
    }
    printf("\n");

    free(visitados);
}

void buscaProfundidadeAux(Grafo *grafo, int vertice, int *visitados, int ***arestas){
    apontadorVerticeVizinho verticeVizinho;
    visitados[vertice - 1] = 1;
    printf("%d ", vertice);
    verticeVizinho = grafo->vertice[vertice - 1].primeiro;
    
    (*arestas)[vertice - 1][verticeVizinho->numeroDoVertice - 1] = 0;
    (*arestas)[verticeVizinho->numeroDoVertice - 1][vertice - 1] = 0;
    while (verticeVizinho != NULL){
        if(visitados[verticeVizinho->numeroDoVertice - 1] == 0){
            buscaProfundidadeAux(grafo, verticeVizinho->numeroDoVertice, visitados, arestas);
            (*arestas)[vertice - 1][verticeVizinho->numeroDoVertice - 1] = 1;
            (*arestas)[verticeVizinho->numeroDoVertice - 1][vertice - 1] = 1;
        }
        verticeVizinho = verticeVizinho->proximo;
    }
}

#include "grafo.h"

typedef struct v* apontadorProximo;
typedef struct v{
    int numeroDoVertice;
    int grau;
    bool statusAresta;
    apontadorProximo proximo;
}VerticeGrau;

typedef struct{
    int verticeOrigem;
    apontadorProximo primeiro;
    apontadorProximo ultimo;
}VerticeAresta;

void inicializaGrafo(Grafo *grafo, int quantidadeVertices);

void inserirVertices(Vertice *vertice, int numeroDoVertice);

void setQuantidadeVertices(Grafo *grafo, int quantidadeVertices);

int getQuantidadeVertices(Grafo *grafo);

void inserirAresta(Grafo *grafo, int verticeOrigem, int verticeDestino, float pesoAresta);

void inserirArestaAuxiliar(Vertice *vertice, int verticeDestino, float pesoAresta);

void quickSort(int **sequenciaGraus, int Esq, int Dir);

void particaoQuickSort(int **sequenciaGraus, int Esq, int Dir,int *i, int *j);

void  FloydWarshall(Grafo *grafo, float ***matrizDistancia, int ***matrizCaminho);

void buscaProfundidadeAux(Grafo *grafo, int vertice, int *visitados, int ***arestas);

int verificaCicloAux(int limite, int tam, int ***arestas, int vcaminho[], int pos);

int podeIncluir(int limite, int i, int ***arestas, int vcaminho[], int pos);

void inserirVerticeGrauDecrescente(VerticeGrau **verticeGrau, int numeroDoVertice, int grau);

void inserirVerticeAresta(VerticeAresta *verticeAresta, int numeroVertice);

void inicializaVerticeAresta(VerticeAresta *verticeAresta, int numeroVertive);

void kruskal(Grafo *grafo,int origem, int **pai);


// Função que inicializa a lista de adjacência que será usada para guardar o grafo
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

// Função que auxilia na inserção de arestas
void inserirArestaAuxiliar(Vertice *vertice, int verticeDestino, float pesoAresta){
    // Caso o verticeOrigem não tenha ainda nenhuma aresta cadastrada, essa aresta se torna a primeira na lista de adjacência
    if(vertice->primeiro == NULL){
        vertice->primeiro = (apontadorVerticeVizinho)malloc(sizeof(VerticeVizinho));
        vertice->ultimo = vertice->primeiro;
    }
    //Caso já tenha alguma aresta cadastrada, a aresta a ser cadastrada será adicionada ao final da lista de adjacência
    else{
        vertice->ultimo->proximo = (apontadorVerticeVizinho)malloc(sizeof(VerticeVizinho));
        vertice->ultimo = vertice->ultimo->proximo;
    }
    vertice->ultimo->proximo = NULL;
    vertice->ultimo->numeroDoVertice = verticeDestino;
    vertice->ultimo->pesoAresta = pesoAresta;
}

// Função que irá ler os dados do arquivo txt
bool leituraSequenciaGraus(Grafo *grafo, char nomeArquivo[]){
    char diretorio[50] = "routine/grafos-txt/";
    strcat(strcat(diretorio, nomeArquivo), ".txt");
    FILE *file;
    file = fopen(diretorio, "r");
    if(file == NULL){
        printf("\nErro na abertura do arquivo de entrada !!!!!!!!\n\n");
        return false;
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
    return true;
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
    char *vertices = (char*)malloc(sizeof(char));
    char verticeAux[10];
    strcpy(vertices, "");
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
    // A função calcula o grau de cada vertice, e coloca eles em um vetor, usa o algoritimo
    // quick sort para ordenar estes vetor em ordem decrescente. A função transforma os graus em string, e retorna
    // uma string que com a sequencia de graus.
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
    strcpy(sequeGraus, "");
    for(i = 0; i < quantidadeVertices; i++){
        sprintf(verticeAux, "%d", sequenciaGraus[i]);
        strcat(sequeGraus, verticeAux);
        strcat(sequeGraus, " ");
    }
    return sequeGraus;
}

// O algoritimo quick sort e usado para colocar a sequencia de graus em ordem decrescente
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

// Algoritimo de Floyd Warshall e usado para determinar o caminho minimo entre 2 vertices e a distancia entre eles
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
                    (*matrizDistancia)[i][j] = INFINITO;
                }
            }
        }
    }
    for(i = 0; i < quantidadeVertices; i++){
        for(j = 0; j < quantidadeVertices; j++){
            if((*matrizDistancia)[i][j] == INFINITO){
                (*matrizCaminho)[i][j] = 0;
            }
            else{
                (*matrizCaminho)[i][j] = i + 1;
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
    // A função roda o algoritmo de Floyd Warshall e pega a excentricidade do vertice. Retorna -INFINITO caso
    // o vertice fassa parte de um ciclo negativo
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
        return INFINITO * -1;
    }
    for(i = 0; i < quantidadeVertices; i++){
        if(matrizDistancia[vertice - 1][i] > excentricidade){
            excentricidade = matrizDistancia[vertice - 1][i];
        }
    }
    return excentricidade;
}

float raioGrafo(Grafo *grafo){
    // Calcula a excentricidade de todos os vertices e retorna a menor excentricidade
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
    // Calcula a excentricidade de todos os vertices e retorna a maior excentricidade
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
    // Calcula a excentricidade de todos os vertices e retorna os vertices com a menor excentricidade
    char *centro = (char*)malloc(sizeof(char));
    char vertice[11];
    int i, quantidadeVertices;
    float raio = 0, excentricidade;
    quantidadeVertices = getQuantidadeVertices(grafo);
    for(i = 0; i < quantidadeVertices; i++){
        excentricidade = excentricidadeVertice(grafo, i + 1);
        if(excentricidade == INFINITO * -1){
            return NULL;
        }
        if(i == 0){
            raio = excentricidade;
            strcpy(centro, "");
            sprintf(vertice, "%d", i + 1);
            strcat(centro, vertice);
            strcat(centro, " ");
        }
        else {
            if(excentricidade < raio){
                raio = excentricidade;
                sprintf(vertice, "%d", i + 1);
                strcpy(centro, "");
                strcat(centro, vertice);
                strcat(centro, " ");
            }
            else if(excentricidade == raio){
                sprintf(vertice, "%d", i + 1);
                strcat(centro, vertice);
                strcat(centro, " ");
            }
        }

    }
    return centro;
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

char* caminhoMinimoEntreVertice(Grafo *grafo, int verticeOrigem, int verticeDestino){
    // Calcula o caminho minimo entre vertices com base no algoritimo de floyd Warshall
    float distancia;
    int i, j, quantidadeVertices = getQuantidadeVertices(grafo);
    int verticeCaminho = verticeDestino;
    float **matrizDistancia;
    int **matrizCaminho;
    char *caminhoMinimo = (char*)malloc(sizeof(char));
    int *caminho = (int*)calloc(quantidadeVertices, sizeof(int));
    matrizCaminho = (int**)malloc(quantidadeVertices * sizeof(int*));
    matrizDistancia= (float**)malloc(quantidadeVertices * sizeof(float*));
    for(i = 0; i < quantidadeVertices; i++){
        matrizCaminho[i] = (int*)malloc(quantidadeVertices * sizeof(int));
        matrizDistancia[i] = (float*)malloc(quantidadeVertices * sizeof(float));
    }

    floydWarshall(grafo, &matrizDistancia, &matrizCaminho);
    j = quantidadeVertices - 1;
    caminho[j] = verticeCaminho;
    while (verticeOrigem != matrizCaminho[verticeOrigem - 1][verticeCaminho - 1]){
        j--;
        verticeCaminho = matrizCaminho[verticeOrigem - 1][verticeCaminho - 1];
        caminho[j] = verticeCaminho;
        if(matrizDistancia[verticeCaminho - 1][verticeCaminho - 1] < 0){
            return NULL;
        }
    }
    j--;
    verticeCaminho = matrizCaminho[verticeOrigem - 1][verticeCaminho - 1];
    caminho[j] = verticeCaminho;
    if(matrizDistancia[verticeCaminho - 1][verticeCaminho - 1] < 0){
        return NULL;
    }
    char verticeAux[11];
    strcpy(caminhoMinimo, "");
    for(i = 0; i < quantidadeVertices; i++){
        if(caminho[i] != 0){
            sprintf(verticeAux, "%d", caminho[i]);
            strcat(caminhoMinimo, verticeAux);
            strcat(caminhoMinimo, " ");
        }
    }
    return caminhoMinimo;
}

float distanciaEntreVertice(Grafo *grafo, int verticeOrigem, int verticeDestino){
    // Calcula a distancia entre vertices com base no algoritimo de floyd Warshall
    float distancia;
    int i, quantidadeVertices;
    float **matrizDistancia;
    int **matrizCaminho;
    quantidadeVertices = getQuantidadeVertices(grafo);
    matrizCaminho = (int**)malloc(quantidadeVertices * sizeof(int*));
    matrizDistancia= (float**)malloc(quantidadeVertices * sizeof(float*));
    for(i = 0; i < quantidadeVertices; i++){
        matrizCaminho[i] = (int*)malloc(quantidadeVertices * sizeof(int));
        matrizDistancia[i] = (float*)malloc(quantidadeVertices * sizeof(float));
    }
    floydWarshall(grafo, &matrizDistancia, &matrizCaminho);
    if(matrizDistancia[verticeOrigem - 1][verticeOrigem - 1] < 0 || matrizDistancia[verticeDestino - 1][verticeDestino - 1] < 0){
        return INFINITO * -1;
    }
    return matrizDistancia[verticeOrigem - 1][verticeDestino - 1];
}

void buscaProfundidade(Grafo *grafo, int vertice){
    int i, quantidadeVertices = getQuantidadeVertices(grafo);
    int *visitados;
    visitados = (int*)malloc(quantidadeVertices * sizeof(int));
    for(i = 0; i < quantidadeVertices; i++){
        visitados[i] = 0;
    }

    apontadorVerticeVizinho verticeVizinho;

    int **arestas;
    arestas = (int**)malloc(quantidadeVertices * sizeof(int*));
    for(i = 0; i < quantidadeVertices; i++){
        arestas[i] = (int*)malloc(quantidadeVertices * sizeof(int));
    }

    for(i = 0; i < quantidadeVertices; i++){
        verticeVizinho = grafo->vertice[i].primeiro;
        while(verticeVizinho != NULL){
            arestas[i][verticeVizinho->numeroDoVertice - 1] = 1;
            arestas[verticeVizinho->numeroDoVertice - 1][i] = 1;
            verticeVizinho = verticeVizinho->proximo;
        }
    }

    printf("Sequencias de vertices visitados: ");
    buscaProfundidadeAux(grafo, vertice, visitados, &arestas);
    printf("\n");

    printf("Arestas nao usadas: ");
    for(i = 0; i < quantidadeVertices; i++){
        for(int j = 0; j < quantidadeVertices; j++){
            if(arestas[i][j] == 1){
                printf("(%d-%d)", i + 1, j + 1);
            }
        }
    }
    printf("\n");

    free(visitados);
}

void buscaProfundidadeAux(Grafo *grafo, int vertice, int *visitados, int ***arestas){
    apontadorVerticeVizinho verticeVizinho;
    visitados[vertice - 1]++;
    printf("%d ", vertice);
    verticeVizinho = grafo->vertice[vertice - 1].primeiro;

    while (verticeVizinho != NULL){
        if(visitados[verticeVizinho->numeroDoVertice - 1] == 0){
            buscaProfundidadeAux(grafo, verticeVizinho->numeroDoVertice, visitados, arestas);
            (*arestas)[vertice - 1][verticeVizinho->numeroDoVertice - 1] = 2;
            (*arestas)[verticeVizinho->numeroDoVertice - 1][vertice - 1] = 2;
        }
        verticeVizinho = verticeVizinho->proximo;
    }
}

char* verificaCiclos(Grafo *grafo){
    int i, quantidadeVertices = getQuantidadeVertices(grafo);

    apontadorVerticeVizinho verticeVizinho;
    int **arestas;
    arestas = (int**)malloc(quantidadeVertices * sizeof(int*));
    for(i = 0; i < quantidadeVertices; i++){
        arestas[i] = (int*)malloc(quantidadeVertices * sizeof(int));
    }

    for(i = 0; i < quantidadeVertices; i++){
        verticeVizinho = grafo->vertice[i].primeiro;
        while(verticeVizinho != NULL){
            arestas[i][verticeVizinho->numeroDoVertice - 1] = 1;
            arestas[verticeVizinho->numeroDoVertice - 1][i] = 1;
            verticeVizinho = verticeVizinho->proximo;
        }
    }

    int vcaminho[quantidadeVertices];
    for( int i=0 ; i<quantidadeVertices ; i++)
        vcaminho[i] = -1;
    vcaminho[0] = 0;

    for (int i = 3; i < quantidadeVertices; i++){
        if(verificaCicloAux(i, quantidadeVertices, &arestas, vcaminho, 1)){
            return "Sim";
        }
    }

    return "Nao";
}

int podeIncluir(int limite, int i, int ***arestas, int vcaminho[], int pos){
    for(int j=0 ; j < limite ; j++){
        if( vcaminho[j] == i )
            return 0;
    }

    if( ! (*arestas)[ vcaminho[pos-1] ][ i ] )
        return 0;

    return 1;
}

int verificaCicloAux(int limite, int tam, int ***arestas, int vcaminho[], int pos){
    //Verifica se já conseguiu preencher o vetor de caminho, e então, se é válido.
    if(pos == limite){
        //verifica se há conexão entre o último e o primeiro para fechar o ciclo. (como estamos usando 1 e 0, é só retorna-los)
        return (*arestas)[ vcaminho[pos-1] ][ vcaminho[0] ];    
    }

    //caso o caminho ainda não tenha sido preenchido
    //vou "tentar ir à todos os outros vértices" para achar um caminho de sucesso
    for(int i=0 ; i<tam ; i++){
        if(podeIncluir(limite, i, arestas, vcaminho, pos)){
            vcaminho[pos] = i;
            
            if(verificaCicloAux(limite, tam, arestas, vcaminho, pos+1))
                return 1;
            
            //se não foi possível chegar a um caminho, retorna até aqui para tentar um novo (pois está num loop tentando todos os vértices)
            vcaminho[pos] = -1;            
        }
    }
    return 0;
}



char* coberturaMinimaVertices(Grafo *grafo){
    int i, indiceVerticesCoberturaMinima = 0, grauVertice, numeroVertice, quantidadeDeVertices;
    int numeroCobertura = 0;
    quantidadeDeVertices = getQuantidadeVertices(grafo);
    int *verticesCoberturaMinima = (int*)calloc(quantidadeDeVertices, sizeof(int));
    bool continuar = false;
    VerticeGrau *vertices = NULL;
    for(i = 0; i < quantidadeDeVertices; i++){
        numeroVertice = grafo->vertice[i].numeroDoVertice;
        grauVertice = verticeGrau(grafo, numeroVertice);
        inserirVerticeGrauDecrescente(&vertices, numeroVertice, grauVertice);
    }
    VerticeAresta *verticeAresta = (VerticeAresta*)malloc(quantidadeDeVertices * sizeof(VerticeAresta));
    apontadorProximo apontadorProximoAuxiliar;
    for(i = 0; i < quantidadeDeVertices; i++){
        numeroVertice = grafo->vertice[i].numeroDoVertice;
        inicializaVerticeAresta(&verticeAresta[i], numeroVertice);
    }
    apontadorVerticeVizinho verticeVizinho;
    for(i = 0; i < quantidadeDeVertices; i++){
        verticeVizinho = grafo->vertice[i].primeiro;
        while (verticeVizinho != NULL){
            numeroVertice = verticeVizinho->numeroDoVertice;
            inserirVerticeAresta(&verticeAresta[i], numeroVertice);
            verticeVizinho = verticeVizinho->proximo;
        }
    }

    do{
        continuar = false;
        numeroCobertura++;
        numeroVertice = vertices->numeroDoVertice;
        verticesCoberturaMinima[indiceVerticesCoberturaMinima] = numeroVertice;
        indiceVerticesCoberturaMinima++;
        vertices = vertices->proximo;
        for(i = 0; i < quantidadeDeVertices; i++){
            apontadorProximoAuxiliar = verticeAresta[i].primeiro;
            if(verticeAresta[i].verticeOrigem == numeroVertice){
                while (apontadorProximoAuxiliar != NULL){
                    apontadorProximoAuxiliar->statusAresta = false;
                    apontadorProximoAuxiliar = apontadorProximoAuxiliar->proximo;
                }
            }
            else{
                while (apontadorProximoAuxiliar != NULL){
                    if(apontadorProximoAuxiliar->numeroDoVertice == numeroVertice){
                        apontadorProximoAuxiliar->statusAresta = false;
                    }
                    apontadorProximoAuxiliar = apontadorProximoAuxiliar->proximo;
                }
            }
        }
        for(i = 0; i < quantidadeDeVertices; i++){
            apontadorProximoAuxiliar = verticeAresta[i].primeiro;
            while (apontadorProximoAuxiliar != NULL){
                if(apontadorProximoAuxiliar->statusAresta == true){
                    continuar = true;
                    break;
                }
                apontadorProximoAuxiliar = apontadorProximoAuxiliar->proximo;
            }
        }
    } while (continuar == true);

    char *conjuntoVertices = (char*)malloc(sizeof(char));
    char vertice[11];
    strcpy(conjuntoVertices, "");
    strcat(conjuntoVertices, "{");
    for(i = 0; i < quantidadeDeVertices; i++){
        sprintf(vertice, "%d", verticesCoberturaMinima[i]);
        strcat(conjuntoVertices, vertice);
        if(i + 1 == quantidadeDeVertices || (verticesCoberturaMinima[i + 1] == 0)){
            strcat(conjuntoVertices, "}");
            break;
        }
        else{
            strcat(conjuntoVertices, ", ");
        }
    }
    printf("\n");
    return conjuntoVertices;

}

void inserirVerticeGrauDecrescente(VerticeGrau **verticeGrau, int numeroDoVertice, int grau){
    apontadorProximo aux1, aux2;
    if((*verticeGrau) == NULL){
        (*verticeGrau) = (apontadorProximo)malloc(sizeof(VerticeGrau));
        (*verticeGrau)->proximo = NULL;
        aux1 = (*verticeGrau);
    }
    else if(grau >= (*verticeGrau)->grau){
        aux1 = (apontadorProximo)malloc(sizeof(VerticeGrau));
        aux1->proximo = (*verticeGrau);
        (*verticeGrau) = aux1;
    }
    else{
        aux2 = (*verticeGrau);
        while (grau < aux2->proximo->grau){
            if(aux2->proximo->proximo == NULL){
                aux2 = aux2->proximo;
                break;
            }
            aux2 = aux2->proximo;
        }
        if(aux2->proximo == NULL){
            aux1 = (apontadorProximo)malloc(sizeof(VerticeGrau));
            aux1->proximo = NULL;
            aux2->proximo = aux1;
        }
        else{
            aux1 = (apontadorProximo)malloc(sizeof(VerticeGrau));
            aux1->proximo = aux2->proximo;
            aux2->proximo = aux1;
        }
    }
    aux1->numeroDoVertice = numeroDoVertice;
    aux1->grau = grau;
}

void inicializaVerticeAresta(VerticeAresta *verticeAresta, int numeroVertive){
    verticeAresta->verticeOrigem = numeroVertive;
    verticeAresta->primeiro = NULL;
    verticeAresta->ultimo = NULL;
}

void inserirVerticeAresta(VerticeAresta *verticeAresta, int numeroVertice){
    if(verticeAresta->primeiro == NULL){
        verticeAresta->primeiro = (apontadorProximo)malloc(sizeof(VerticeGrau));
        verticeAresta->ultimo = verticeAresta->primeiro;
    }
    else{
        verticeAresta->ultimo->proximo = (apontadorProximo)malloc(sizeof(VerticeGrau));
        verticeAresta->ultimo = verticeAresta->ultimo->proximo;
    }
    verticeAresta->ultimo->proximo = NULL;
    verticeAresta->ultimo->numeroDoVertice = numeroVertice;
    verticeAresta->ultimo->statusAresta = true;
}

void kruskal(Grafo *grafo,int origem, int **pai){
    int i,j,destino,primeiro,numeroVertice,grauVertice;
    int numeroDeVertices = grafo->quantidadeDeVertices;
    int peso;
    double menorPeso;
    int *arvore = (int*) malloc(numeroDeVertices * sizeof(int));
    
    for (i = 0; i < numeroDeVertices; i++){
        arvore[i] = grafo->vertice[i].numeroDoVertice;
        (*pai)[i] = -1;

    }
    (*pai)[origem] = origem;
    apontadorVerticeVizinho apontador;
    while(true){
        for (i=0;i<numeroDeVertices;i++){
            printf("%d ",(*pai)[i]);
        }
        primeiro = 1;
        printf("\n");
        for(i = 0; i < numeroDeVertices; i++){
            numeroVertice = grafo->vertice[i].numeroDoVertice;
            grauVertice = verticeGrau(grafo, numeroVertice);
            apontador = grafo->vertice[i].primeiro;
            while (apontador != NULL){
                
                if(arvore[i] != arvore[apontador->numeroDoVertice]){
                    if(primeiro){
                        printf("Primeiro\n");
                        menorPeso = apontador->pesoAresta;
                        origem = numeroVertice;
                        destino = apontador->numeroDoVertice;
                        primeiro = 0;
                        
                    }
                    else{
                        printf("else \n");
                        if(menorPeso > apontador->pesoAresta){
                            printf("elseif \n");
                            menorPeso = apontador->pesoAresta;
                            origem = numeroVertice;
                            destino = apontador->numeroDoVertice;
                        }
                    }
                }
                apontador = apontador->proximo;
            }
        }
        if(primeiro == 1)break;
        if((*pai)[origem] == -1) (*pai)[origem] = destino;
        else (*pai)[destino] =  origem;

        for(i = 0; i < numeroDeVertices; i++){
            if(arvore[i] == arvore[destino]){
                arvore[i] = arvore[origem];
            }
        }
    }
    free(arvore);
}

void arvoreGeradoraMinima(Grafo *grafo,int origem){
    int *pai;
    int i;
    int quantidade = getQuantidadeVertices(grafo);
    pai = (int*) calloc(quantidade, sizeof(int));
    kruskal(grafo,origem,&pai);
    printf("Saiu\n");
    for(i=0; i<quantidade; i++){
        if (pai[i] == 0)break;
        printf("%d ",pai[i]);
    }
    printf("\n");
}
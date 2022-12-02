#include "grafo-lib/grafo.h"
#include "grafo-lib/matching/maximumMatching.h"

int main(){
    int i, j;
    int origem;
    Grafo grafo;
    Graph* emparelMaximo = (Graph*) malloc(sizeof(Graph));

    char nomeArquivo[100];
    bool leituraOK;
    int vizinhoDe,grauDe,profundidadeDe,exenDe,centralDe,distanciaDe,distanciaPara,caminhoDe,caminhoPara;
    printf("Digite o nome do arquivo a ser executado: ");
    scanf("%s",&nomeArquivo);
    printf("\n");

    leituraOK = leituraSequenciaGraus(&grafo, nomeArquivo);
    if(!leituraOK){
        return 0;
    }

    /*
    printf("---------------------------------------------------------\n");

    printf("Digite o vertice para descobrir seus vizinhos\n");
    scanf("%d",&vizinhoDe);
    printf("Digite o vertice para descobrir seu grau\n");
    scanf("%d",&grauDe);
    printf("Digite o vertice de inicio da busca de profundidade\n");
    scanf("%d",&profundidadeDe);
    printf("Digite o vertice para descobrir sua Exentricidade\n");
    scanf("%d",&exenDe);
    printf("Digite o vertice para descobrir a Centralidade de Proximidade\n");
    scanf("%d",&centralDe);
    printf("Digite os dois vertices para descobrir a distancia entre eles\n");
    scanf("%d",&distanciaDe);
    scanf("%d",&distanciaPara);
    printf("Digite os vertices para descobrir a distancia entre eles\n");
    scanf("%d",&caminhoDe);
    scanf("%d",&caminhoPara);
    printf("Digite a origem da Arvore Geradoda Minima: \n");
    scanf("%d",&origem);
    arvoreGeradoraMinima(&grafo,origem);

    printf("-------------------------- PARTE 1 -------------------------------\n");
    printf("Ordem grafo: %d\n", ordemGrafo(&grafo));

    printf("Tamanho grafo: %d\n", tamanhoGrafo(&grafo));

    printf("Vertices vizinhos do %d: %s\n",vizinhoDe,verticesVizinhos(&grafo,vizinhoDe));
    
    printf("Grau do vertice %d: %d\n",grauDe,verticeGrau(&grafo, grauDe));
    
    printf("Sequencia de graus: %s\n", sequenciaGrausGrafo(&grafo));
    
    printf("Busca de Profundidade a partir de %d: \n",profundidadeDe);
    buscaProfundidade(&grafo,profundidadeDe);

    printf("Excentricidade do vertice %d: %f\n",exenDe, excentricidadeVertice(&grafo,exenDe));

    printf("Raio grafo: %f\n", raioGrafo(&grafo));
    printf("Diametro grafo: %f\n", diametroGrafo(&grafo));
    printf("Centro grafo: %s\n", centroGrafo(&grafo));

    printf("Centralidade proximidade do vertice %d: %f\n",centralDe, centralidadeProximidade(&grafo,centralDe));

    printf("Distancia entre vertice %d e %d: %f\n",distanciaDe,distanciaPara,distanciaEntreVertice(&grafo,distanciaDe,distanciaPara));

    printf("Caminho de %d para %d: %s\n",caminhoDe,caminhoPara, caminhoMinimoEntreVertice(&grafo,caminhoDe,caminhoPara));
*/
    printf("-------------------------- PARTE 2 -------------------------------\n");
    
    printf("Digite a origem da Arvore Geradoda Minima: \n");
    scanf("%d",&origem);
    arvoreGeradoraMinima(&grafo,origem);
    
    printf("Possui ciclo: %s\n", verificaCiclos(&grafo));

    read_graph(nomeArquivo, emparelMaximo);
    printf("Emparelhamento Maximo: %s", maximal_matching(emparelMaximo));

    printf("Conjunto de vertices da cobertura minima de vertices: %s\n", coberturaMinimaVertices(&grafo));

    printf("------------------------------------------------------------------\n");

    return 0;
}

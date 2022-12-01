#include <stdio.h>
#include <stdlib.h>
#include "maximumMatching.h"
#include "quicksort.h"

void empty_graph(Graph* g) {
  g->vertex_count = 0;
  g->arcs = NULL;
}

void init_graph(Graph* g, int n) {
  int i;
  empty_graph(g);

  g->vertex_count = n;
  g->arcs = (int**) calloc(n, sizeof(int*));
  for (i = 0 ; i < g->vertex_count ; i++)
    g->arcs[i] = (int*) calloc(n, sizeof(int));
  g->vertex = (Vertex*) malloc(n * sizeof(Vertex));
  for (i = 0 ; i < g->vertex_count ; i++) {
    g->vertex[i].vertex = i;
    g->vertex[i].degree = 0;
    g->vertex[i].saturated = 0;
  }
}

int insert_arc(Graph* g, int a1, int a2, int weight) {
  if (a1 >= 0 && a1 < g->vertex_count && a2 >= 0 && a2 < g->vertex_count && g->arcs[a1][a2] == 0) {
    g->arcs[a1][a2] = weight;
    g->arcs[a2][a1] = weight;
    return 0;
  }
  return -1;
}

int remove_arc(Graph* g, int a1, int a2) {
  int weight = -1;
  if (a1 >= 0 && a1 < g->vertex_count && a2 >= 0 && a2 < g->vertex_count && g->arcs[a1][a2] > 0) {
    weight = g->arcs[a1][a2];
    g->arcs[a1][a2] = 0;
    g->arcs[a2][a1] = 0;
  }
  return weight;
}

int* get_adjacency(Graph* g, int v) {
  int degree;

  degree = get_vertex_degree(g, v);

  int* adjacency = (int*) malloc((degree + 1) * sizeof(int));

  adjacency[0] = degree; // Using the first position of the pointer to determine the size of the array
  
  int i;
  int j;
  for (i = 0, j = 1 ; j <= degree ; i++) {
    if (g->arcs[i][v] > 0) {
      adjacency[j++] = i;
    }
  }

  return adjacency;
}

int get_vertex_degree(Graph* g, int v) {
  int i;
  int degree = 0;

  for (i = 0 ; i < g->vertex_count ; i++)
    if (g->arcs[i][v] > 0)
      degree++;

  return degree;
}

void get_ordered_vertex(Graph* g, Vertex* v) {
  
  int i;

  for (i = 0 ; i < g->vertex_count ; i++) {
    v[i].vertex = i;
    v[i].degree = get_vertex_degree(g, i);
  }
  
  quicksort(v, 0, g->vertex_count - 1);
}

void insert_vertex(Graph* g, int v) {
  if (g->arcs == NULL) {
    init_graph(g, v); 
  }

  else {
    int i, j;
    g->vertex_count += v;
    g->arcs = (int**) realloc(g->arcs, g->vertex_count * sizeof(int*));
    
    for (i = 0 ; i < g->vertex_count - v ; i++)
      g->arcs[i] = (int*) realloc(g->arcs[i], g->vertex_count * sizeof(int)); // realloc the part of the matrix which were used before

    for ( ; i < g->vertex_count ; i++) 
      g->arcs[i] = (int*) calloc(g->vertex_count, sizeof(int)); // alloc the new part of the matrix

    for (i = 0 ; i < g->vertex_count - v ; i++) {
      for (j = g->vertex_count - v ; j < g->vertex_count ; j++) {
        g->arcs[i][j] = 0;
      }
    }
  }
}

int read_graph(char* filename, Graph* g) {

  char diretorio[50] = "routine/grafos-txt/";
  strcat(strcat(diretorio, filename), ".txt");
  FILE *file;
  file = fopen(diretorio, "r");
  if(file == NULL){
      printf("\nErro na abertura do arquivo de entrada !!!!!!!!\n\n");
      return -1;
  }else {
    empty_graph(g);
  
    char line[80];
    char str_aux[80];
    int i;
    int j;
    int k;
    int arc_1;
    int arc_2;
    int weight = 0;
    
    for (i = 0 ; fgets(line, 80, file) != NULL ; i++) {
      if (i == 0) {
        insert_vertex(g, atoi(line));
      }

      else {
        for (j = 0, k = 0 ; j < 80 && line[j] != 32 && line[j] != '\0' ; j++, k++) 
          str_aux[k] = line[j];

        str_aux[k] = '\0';
        arc_1 = atoi(str_aux);
        
        j = j + 1;
        str_aux[0] = '\0';

        for (k = 0 ; j < 80 && line[j] != 32 && line[j] != '\0' ; j++, k++)
          str_aux[k] = line[j];

        str_aux[k] = '\0';
        arc_2 = atoi(str_aux);
        
        j = j + 1;
        str_aux[0] = '\0';

        for (k = 0 ; j < 80 && line[j] != 32 && line[j] != '\0' ; j++, k++)
          str_aux[k] = line[j];

        str_aux[k] = '\0';
        weight = atoi(str_aux);

        if (weight == 0) weight = 1;

        insert_arc(g, arc_1, arc_2, weight);
      }
    }
  }
  return 0;
}

char* maximal_matching(Graph* g) {
  Graph* m = (Graph*) malloc(sizeof(Graph));
  Graph* matching = (Graph*) malloc(sizeof(Graph));

  init_graph(m, g->vertex_count);
  init_graph(matching, g->vertex_count); 

  int i;
  int j;

  // Make a copy of the graph ignoring loops
  for (i = 0 ; i < g->vertex_count ; i++)
    for (j = 0 ; j < g->vertex_count ; j++)
      if (i != j)
        m->arcs[i][j] = g->arcs[i][j];

  
  Vertex* v = (Vertex*) malloc(g->vertex_count * sizeof(Vertex));
  get_ordered_vertex(m, v);

  int saturated[m->vertex_count];
  for (i = 0 ; i < m->vertex_count ; i++)
    saturated[i] = 0;

  for (i = 0 ; i < m->vertex_count ; i++) {
    m->vertex[i].degree = get_vertex_degree(m, i);
  }

  int* adj;
  for (i = 0 ; i < m->vertex_count ; i++) {
    int v1 = v[i].vertex;
    int v2;

    if (saturated[v1] == 0) {
      adj = get_adjacency(m, v1);
      if (adj[0] > 0) {
        v2 = adj[1];
        
        for (j = 2 ; j <= adj[0] ; j++) {
          if (m->vertex[adj[j]].degree < m->vertex[v2].degree) 
            v2 = adj[j];
        }
        
        insert_arc(matching, v1, v2, m->arcs[v1][v2]);
        free(adj);
        saturated[v1] = 1;
        saturated[v2] = 1;
        
        for (j = 0 ; j < m->vertex_count ; j++) {
          remove_arc(m, v1, j);
          remove_arc(m, v2, j);
        }
      }
    }
  }
  
  int arc_count = 0;
  char vertice[80];
  char *resultado = (char*)malloc(sizeof(char));
  strcpy(vertice, "");
  strcpy(resultado, "");
  strcpy(resultado, "A = {");

  for (i = 0 ; i < matching->vertex_count ; i++) {
    for (j = i ; j < matching->vertex_count ; j++) {
      if (matching->arcs[i][j] > 0) {
        sprintf(vertice, "(%d, %d)", i, j);
        strcat(resultado, vertice);
        arc_count++;
      }
    }
  }

  sprintf(vertice, "} - %d", arc_count);
  strcat(resultado, vertice);

  return resultado;
}

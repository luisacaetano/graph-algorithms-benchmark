#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../estruturas/grafo.h"

// Versão ingênua de Kruskal (usa um vetor para identificar componentes conectados)
// g: ponteiro para o grafo
// agm: vetor onde serão armazenadas as arestas da AGM encontrada
double kruskal_ineficiente(Grafo* g, Aresta* agm);

// Versão eficiente de Kruskal usando Union-Find (usa a estrutura union-find para identificar componentes conectados de forma eficiente)
// g: ponteiro para o grafo
// agm: vetor onde serão armazenadas as arestas da AGM encontrada
double kruskal_union_find(Grafo* g, Aresta* agm);

#endif
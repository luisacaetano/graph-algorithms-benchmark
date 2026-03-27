#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../estruturas/grafo.h"

// Versão ingênua de Dijkstra (busca linear pelo menor valor a cada iteração)
// g: ponteiro para o grafo
// origem: vértice de origem
// dist: vetor de distâncias mínimas (resultado)
// pai: vetor de predecessores (resultado)
void dijkstra_ineficiente(Grafo* g, int origem, double* dist, int* pai);

// Versão eficiente de Dijkstra (usa heap mínimo para acelerar a busca do menor valor)
// g: ponteiro para o grafo
// origem: vértice de origem
// dist: vetor de distâncias mínimas (resultado)
// pai: vetor de predecessores (resultado)
void dijkstra_heap(Grafo* g, int origem, double* dist, int* pai);

#endif
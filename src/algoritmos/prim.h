#ifndef PRIM_H
#define PRIM_H

#include "../estruturas/grafo.h"

// Versão ingênua de Prim (busca linearmente o vértice de menor chave a cada iteração)
// g: ponteiro para o grafo
// pai: vetor onde será armazenada a árvore geradora mínima (predecessores)
double prim_ineficiente(Grafo* g, int* pai);

// Versão eficiente de Prim usando heap mínimo (usa um heap mínimo para acelerar a busca do vértice de menor chave)
// g: ponteiro para o grafo
// pai: vetor onde será armazenada a árvore geradora mínima (predecessores)
double prim_heap(Grafo* g, int* pai);

#endif
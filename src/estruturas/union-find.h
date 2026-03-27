#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura Union-Find 
typedef struct {
    int* pai;     // Vetor de pais: pai[i] é o pai do elemento i
    int* rank;    // Vetor de ranks: usado para balancear as uniões
    int tamanho;  
} UnionFind;

// Cria e inicializa a estrutura Union-Find para 'tamanho' elementos
UnionFind* criar_union_find(int tamanho);

// Encontra o representante do conjunto do elemento x
int encontrar(UnionFind* uf, int x);

// Une os conjuntos dos elementos x e y
int unir(UnionFind* uf, int x, int y);

// Libera toda a memória alocada para a estrutura Union-Find
void liberar_union_find(UnionFind* uf);

#endif

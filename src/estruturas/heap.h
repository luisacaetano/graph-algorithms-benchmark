#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura para um elemento do heap mínimo
typedef struct {
    int vertice;      
    double chave;     // Prioridade (usada para ordenação no heap)
} ElementoHeap;

// Estrutura do heap mínimo
typedef struct {
    ElementoHeap* elementos; 
    int* posicoes;           
    int tamanho;             
    int capacidade;          
} MinHeap;

// Cria e inicializa um heap mínimo com a capacidade informada
MinHeap* criar_heap(int capacidade);

// Insere um vértice com a chave informada no heap
void inserir_heap(MinHeap* heap, int vertice, double chave);

// Remove e retorna o elemento de menor chave do heap
ElementoHeap extrair_min(MinHeap* heap);

// Diminui a chave de um vértice já presente no heap
void diminuir_chave(MinHeap* heap, int vertice, double nova_chave);

// Retorna 1 se o heap está vazio, 0 caso contrário
int heap_vazio(MinHeap* heap);

// Libera toda a memória alocada para o heap
void liberar_heap(MinHeap* heap);

#endif
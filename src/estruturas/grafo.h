#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTICES 10000000
#define MAX_ARESTAS 20000000 
#define INF INT_MAX         


// Estrutura para representar uma aresta do grafo
typedef struct {
    int origem;      
    int destino;     
    double peso;     
} Aresta;

// Estrutura para um nó da lista de adjacência
typedef struct NoAdj {
    int vertice;             
    double peso;             
    struct NoAdj* proximo;   
} NoAdj;

// Estrutura principal do grafo
typedef struct {
    int num_vertices;    
    int num_arestas;    
    int direcionado;     // 0 para não direcionado, 1 para direcionado
    NoAdj** lista_adj;   
    Aresta* arestas;     // Kruskal
} Grafo;

// Função para criar um grafo com um número de vértices e se é direcionado
Grafo* criar_grafo(int num_vertices, int direcionado);

// Função para adicionar uma aresta ao grafo
void adicionar_aresta(Grafo* grafo, int origem, int destino, double peso);

// Função para imprimir o grafo
void imprimir_grafo(Grafo* grafo);

// Função para liberar toda a memória alocada para o grafo
void liberar_grafo(Grafo* grafo);

// Função para obter todas as arestas do grafo 
int obter_todas_arestas(Grafo* grafo, Aresta** arestas);

#endif


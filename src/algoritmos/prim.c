#include <stdlib.h>
#include <limits.h>
#include "prim.h"
#include "../estruturas/heap.h"

// Versão ingênua de Prim: busca linear pelo menor valor de chave
double prim_ineficiente(Grafo* g, int* pai) {
    int V = g->num_vertices;
    double* chave = malloc(V * sizeof(double));   // Vetor com o menor peso para cada vértice
    int* visitado = calloc(V, sizeof(int));       // Marca os vértices já incluídos na AGM

    // Inicializa as chaves e pais
    for (int i = 0; i < V; i++) {
        chave[i] = INF;   
        pai[i] = -1;     
    }
    chave[0] = 0.0;       // Começa pelo vértice 0
    double total = 0.0;   // Peso total da AGM

    // Para cada vértice, encontra o vértice não visitado de menor chave
    for (int count = 0; count < V; count++) {
        int u = -1;
        double min = INF;
        // Busca linear pelo vértice não visitado de menor chave
        for (int v = 0; v < V; v++)
            if (!visitado[v] && chave[v] < min)
                min = chave[v], u = v;
        if (u == -1) break; // Todos visitados ou não alcançáveis
        visitado[u] = 1;
        total += chave[u];

        // Atualiza as chaves dos vizinhos de u
        for (NoAdj* adj = g->lista_adj[u]; adj != NULL; adj = adj->proximo) {
            int v = adj->vertice;
            if (!visitado[v] && adj->peso < chave[v]) {
                chave[v] = adj->peso;
                pai[v] = u;
            }
        }
    }
    free(chave);
    free(visitado);
    return total;
}

// Versão eficiente de Prim: usa heap mínimo para acelerar a busca do menor valor de chave
double prim_heap(Grafo* g, int* pai) {
    int V = g->num_vertices;
    double* chave = malloc(V * sizeof(double));   // Vetor com o menor peso para cada vértice
    int* visitado = calloc(V, sizeof(int));       // Marca os vértices já incluídos na AGM

    // Inicializa as chaves e pais
    for (int i = 0; i < V; i++) {
        chave[i] = INF;   
        pai[i] = -1;      
    }
    chave[0] = 0.0;       

    // Cria o heap mínimo e insere todos os vértices com suas chaves
    MinHeap* heap = criar_heap(V);
    for (int i = 0; i < V; i++)
        inserir_heap(heap, i, chave[i]);

    double total = 0.0;   // Peso total da AGM

    // Enquanto houver vértices no heap
    while (!heap_vazio(heap)) {
        // Extrai o vértice de menor chave do heap
        ElementoHeap min_elem = extrair_min(heap);
        int u = min_elem.vertice;
        visitado[u] = 1;
        total += chave[u];

        // Atualiza as chaves dos vizinhos de u
        for (NoAdj* adj = g->lista_adj[u]; adj != NULL; adj = adj->proximo) {
            int v = adj->vertice;
            if (!visitado[v] && adj->peso < chave[v]) {
                chave[v] = adj->peso;
                pai[v] = u;
                // Atualiza a prioridade do vértice v no heap
                diminuir_chave(heap, v, chave[v]);
            }
        }
    }
    liberar_heap(heap);
    free(chave);
    free(visitado);
    return total;
}
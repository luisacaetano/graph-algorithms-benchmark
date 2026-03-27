#include <stdlib.h>
#include <limits.h>
#include "dijkstra.h"
#include "../estruturas/heap.h"

// Versão ingênua de Dijkstra: busca linear pelo menor valor
void dijkstra_ineficiente(Grafo* g, int origem, double* dist, int* pai) {
    int V = g->num_vertices;
    int* visitado = calloc(V, sizeof(int)); 

    // Inicializa distâncias e pais
    for (int i = 0; i < V; i++) {
        dist[i] = INF;   
        pai[i] = -1;     
    }
    dist[origem] = 0.0;  // Distância da origem para ela mesma é 0

    // Para cada vértice, encontra o vértice não visitado de menor distância
    for (int count = 0; count < V; count++) {
        int u = -1;
        double min = INF;
        // Busca linear pelo vértice não visitado de menor distância
        for (int v = 0; v < V; v++)
            if (!visitado[v] && dist[v] < min)
                min = dist[v], u = v;
        if (u == -1) break; // Todos visitados ou não alcançáveis
        visitado[u] = 1;

        // Atualiza as distâncias dos vizinhos de u
        for (NoAdj* adj = g->lista_adj[u]; adj != NULL; adj = adj->proximo) {
            int v = adj->vertice;
            if (!visitado[v] && dist[u] + adj->peso < dist[v]) {
                dist[v] = dist[u] + adj->peso;
                pai[v] = u;
            }
        }
    }
    free(visitado);
}

// Versão eficiente de Dijkstra: usa heap mínimo para acelerar a busca do menor valor
void dijkstra_heap(Grafo* g, int origem, double* dist, int* pai) {
    int V = g->num_vertices;
    int* visitado = calloc(V, sizeof(int)); 

    for (int i = 0; i < V; i++) {
        dist[i] = INF;   
        pai[i] = -1;     
    }
    dist[origem] = 0.0;  // Distância da origem para ela mesma é 0

    // Cria o heap mínimo e insere todos os vértices com suas distâncias
    MinHeap* heap = criar_heap(V);
    for (int i = 0; i < V; i++)
        inserir_heap(heap, i, dist[i]);

    // Enquanto houver vértices no heap
    while (!heap_vazio(heap)) {
        // Extrai o vértice de menor distância
        ElementoHeap min_elem = extrair_min(heap);
        int u = min_elem.vertice;
        if (visitado[u]) continue; // Pula se já foi processado
        visitado[u] = 1;

        // Atualiza as distâncias dos vizinhos de u
        for (NoAdj* adj = g->lista_adj[u]; adj != NULL; adj = adj->proximo) {
            int v = adj->vertice;
            if (!visitado[v] && dist[u] + adj->peso < dist[v]) {
                dist[v] = dist[u] + adj->peso;
                pai[v] = u;
                // Atualiza a prioridade do vértice v no heap
                diminuir_chave(heap, v, dist[v]);
            }
        }
    }
    liberar_heap(heap);
    free(visitado);
}
#include <stdlib.h>
#include "kruskal.h"
#include "../estruturas/union-find.h"

// Função de comparação para qsort (usada para ordenar as arestas por peso crescente)
static int compara_arestas(const void* a, const void* b) {
    double diff = ((Aresta*)a)->peso - ((Aresta*)b)->peso;
    return (diff > 0) - (diff < 0);
}

// Versão Ingênua do Kruskal: usa vetor para identificar componentes conectados
double kruskal_ineficiente(Grafo* g, Aresta* agm) {
    // Vetor que indica a qual componente cada vértice pertence
    int* conjunto = malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) conjunto[i] = i;

    // Ordena as arestas por peso crescente
    qsort(g->arestas, g->num_arestas, sizeof(Aresta), compara_arestas);

    double total = 0.0;      
    int arestas_agm = 0;     

    // Percorre as arestas em ordem crescente de peso
    for (int i = 0; i < g->num_arestas && arestas_agm < g->num_vertices - 1; i++) {
        int u = g->arestas[i].origem;
        int v = g->arestas[i].destino;
        // Se u e v estão em componentes diferentes, pode adicionar a aresta
        if (conjunto[u] != conjunto[v]) {
            agm[arestas_agm++] = g->arestas[i];
            int antigo = conjunto[v];
            // Atualiza todos os vértices do componente antigo para o novo
            for (int j = 0; j < g->num_vertices; j++)
                if (conjunto[j] == antigo)
                    conjunto[j] = conjunto[u];
            total += g->arestas[i].peso;
        }
    }
    free(conjunto);
    return total;
}

// Versão Eficiente do Kruskal: usa Union-Find para identificar componentes conectados
double kruskal_union_find(Grafo* g, Aresta* agm) {
    // Cria a estrutura Union-Find para os vértices do grafo
    UnionFind* uf = criar_union_find(g->num_vertices);

    // Ordena as arestas por peso crescente
    qsort(g->arestas, g->num_arestas, sizeof(Aresta), compara_arestas);

    double total = 0.0;      
    int arestas_agm = 0;     

    // Percorre as arestas em ordem crescente de peso
    for (int i = 0; i < g->num_arestas && arestas_agm < g->num_vertices - 1; i++) {
        int u = g->arestas[i].origem;
        int v = g->arestas[i].destino;
        // Se u e v estão em componentes diferentes, pode adicionar a aresta
        if (encontrar(uf, u) != encontrar(uf, v)) {
            agm[arestas_agm++] = g->arestas[i];
            unir(uf, u, v); // Une os componentes de u e v
            total += g->arestas[i].peso;
        }
    }
    liberar_union_find(uf);
    return total;
}
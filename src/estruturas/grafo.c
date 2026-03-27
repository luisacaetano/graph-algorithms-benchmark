#include "grafo.h"

// Cria e inicializa um grafo com o número de vértices e se é direcionado ou não
Grafo* criar_grafo(int num_vertices, int direcionado) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if (!grafo) return NULL;
    
    grafo->num_vertices = num_vertices;
    grafo->num_arestas = 0;
    grafo->direcionado = direcionado;
    
    // Aloca o array de ponteiros para as listas de adjacência
    grafo->lista_adj = (NoAdj**)calloc(num_vertices, sizeof(NoAdj*));
    if (!grafo->lista_adj) {
        free(grafo);
        return NULL;
    }
    
    // Aloca o array de arestas (usado por Kruskal)
    grafo->arestas = (Aresta*)malloc(MAX_ARESTAS * sizeof(Aresta));
    if (!grafo->arestas) {
        free(grafo->lista_adj);
        free(grafo);
        return NULL;
    }
    
    return grafo;
}

// Adiciona uma aresta ao grafo (e à lista de adjacência)
// Se o grafo não for direcionado, adiciona também a aresta reversa
void adicionar_aresta(Grafo* grafo, int origem, int destino, double peso) {
    if (!grafo || origem >= grafo->num_vertices || destino >= grafo->num_vertices) 
        return;
    
    // Adiciona à lista de adjacência do vértice de origem
    NoAdj* novo_no = (NoAdj*)malloc(sizeof(NoAdj));
    novo_no->vertice = destino;
    novo_no->peso = peso;
    novo_no->proximo = grafo->lista_adj[origem];
    grafo->lista_adj[origem] = novo_no;
    
    // Se não é direcionado, adiciona a aresta reversa na lista de adjacência do destino
    if (!grafo->direcionado) {
        NoAdj* novo_no_rev = (NoAdj*)malloc(sizeof(NoAdj));
        novo_no_rev->vertice = origem;
        novo_no_rev->peso = peso;
        novo_no_rev->proximo = grafo->lista_adj[destino];
        grafo->lista_adj[destino] = novo_no_rev;
    }
    
    // Adiciona a aresta ao array de arestas (usado por Kruskal)
    if (grafo->num_arestas < MAX_ARESTAS) {
        grafo->arestas[grafo->num_arestas].origem = origem;
        grafo->arestas[grafo->num_arestas].destino = destino;
        grafo->arestas[grafo->num_arestas].peso = peso;
        grafo->num_arestas++;
    }
}

// Imprime o grafo no formato de lista de adjacência.
// Para cada vértice, mostra todos os seus vizinhos e os pesos das arestas.
void imprimir_grafo(Grafo* grafo) {
    if (!grafo) return;
    printf("Grafo %s com %d vértices e %d arestas:\n",
           grafo->direcionado ? "direcionado" : "não direcionado",
           grafo->num_vertices, grafo->num_arestas);

    // Percorre todos os vértices do grafo
    for (int i = 0; i < grafo->num_vertices; i++) {
        printf("%d:", i); 
        NoAdj* adj = grafo->lista_adj[i];
        // Percorre a lista de adjacência do vértice i
        while (adj) {
            // Imprime o vizinho e o peso da aresta
            printf(" -> %d(%.2lf)", adj->vertice, adj->peso);
            adj = adj->proximo;
        }
        printf("\n");
    }
}

// Libera toda a memória alocada para o grafo
void liberar_grafo(Grafo* grafo) {
    if (!grafo) return;
    
    // Libera cada lista de adjacência
    for (int i = 0; i < grafo->num_vertices; i++) {
        NoAdj* atual = grafo->lista_adj[i];
        while (atual) {
            NoAdj* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    
    free(grafo->lista_adj);   // Libera o array de ponteiros das listas
    free(grafo->arestas);     // Libera o array de arestas
    free(grafo);              // Libera a estrutura principal do grafo
}

// Copia todas as arestas do grafo para um vetor fornecido pelo usuário.
// Retorna o número de arestas copiadas.
// Útil para exportar ou analisar todas as arestas do grafo.
int obter_todas_arestas(Grafo* grafo, Aresta** arestas) {
    if (!grafo || !arestas) return 0;
    // Aloca memória para o vetor de arestas
    *arestas = (Aresta*)malloc(grafo->num_arestas * sizeof(Aresta));
    if (!*arestas) return 0;

    // Copia cada aresta do grafo para o vetor fornecido
    for (int i = 0; i < grafo->num_arestas; i++) {
        (*arestas)[i] = grafo->arestas[i];
    }
    return grafo->num_arestas;
}
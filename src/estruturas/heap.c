#include "heap.h"

// Cria e inicializa um heap mínimo com a capacidade informada
MinHeap* criar_heap(int capacidade) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    
    // Aloca espaço para os elementos do heap e para o vetor de posições
    heap->elementos = (ElementoHeap*)malloc(capacidade * sizeof(ElementoHeap));
    heap->posicoes = (int*)malloc(capacidade * sizeof(int));
    
    if (!heap->elementos || !heap->posicoes) {
        free(heap->elementos);
        free(heap->posicoes);
        free(heap);
        return NULL;
    }
    
    heap->tamanho = 0;
    heap->capacidade = capacidade;
    
    // Inicializa todas as posições como -1 (indicando que o vértice não está no heap)
    for (int i = 0; i < capacidade; i++) {
        heap->posicoes[i] = -1;
    }
    
    return heap;
}

// Troca dois elementos do heap e atualiza o vetor de posições
static void trocar_elementos(MinHeap* heap, int i, int j) {
    // Atualiza as posições dos vértices trocados
    heap->posicoes[heap->elementos[i].vertice] = j;
    heap->posicoes[heap->elementos[j].vertice] = i;
    
    // Troca os elementos propriamente ditos
    ElementoHeap temp = heap->elementos[i];
    heap->elementos[i] = heap->elementos[j];
    heap->elementos[j] = temp;
}

// Sobe o elemento na posição i até restaurar a propriedade do heap mínimo
static void heapify_up(MinHeap* heap, int i) {
    int pai = (i - 1) / 2;
    // Enquanto não for a raiz e a chave do pai for maior que a do filho
    if (i > 0 && heap->elementos[pai].chave > heap->elementos[i].chave) {
        trocar_elementos(heap, i, pai);
        heapify_up(heap, pai);
    }
}

// Desce o elemento na posição i até restaurar a propriedade do heap mínimo
static void heapify_down(MinHeap* heap, int i) {
    int menor = i;
    int esquerdo = 2 * i + 1;
    int direito = 2 * i + 2;
    
    // Encontra o menor entre o nó atual e seus filhos
    if (esquerdo < heap->tamanho && 
        heap->elementos[esquerdo].chave < heap->elementos[menor].chave) {
        menor = esquerdo;
    }
    if (direito < heap->tamanho && 
        heap->elementos[direito].chave < heap->elementos[menor].chave) {
        menor = direito;
    }
    // Se algum filho for menor, troca e continua descendo
    if (menor != i) {
        trocar_elementos(heap, i, menor);
        heapify_down(heap, menor);
    }
}

// Insere um novo vértice com a chave informada no heap
void inserir_heap(MinHeap* heap, int vertice, double chave) {
    if (heap->tamanho >= heap->capacidade) return;
    
    int i = heap->tamanho;
    heap->elementos[i].vertice = vertice;
    heap->elementos[i].chave = chave;
    heap->posicoes[vertice] = i;
    heap->tamanho++;
    
    heapify_up(heap, i); // Restaura a propriedade do heap
}

// Remove e retorna o elemento de menor chave do heap
ElementoHeap extrair_min(MinHeap* heap) {
    ElementoHeap min_elem = {-1, -1};
    if (heap->tamanho <= 0) return min_elem;
    
    min_elem = heap->elementos[0];
    heap->posicoes[min_elem.vertice] = -1;
    
    if (heap->tamanho == 1) {
        heap->tamanho--;
        return min_elem;
    }
    
    // Move o último elemento para o topo e restaura o heap
    heap->elementos[0] = heap->elementos[heap->tamanho - 1];
    heap->posicoes[heap->elementos[0].vertice] = 0;
    heap->tamanho--;
    
    heapify_down(heap, 0);
    
    return min_elem;
}

// Diminui a chave de um vértice já presente no heap e restaura o heap
void diminuir_chave(MinHeap* heap, int vertice, double nova_chave) {
    int pos = heap->posicoes[vertice];
    if (pos == -1) return;  // Vértice não está no heap
    heap->elementos[pos].chave = nova_chave;
    heapify_up(heap, pos);
}

// Retorna 1 se o heap está vazio, 0 caso contrário
int heap_vazio(MinHeap* heap) {
    return heap->tamanho == 0;
}

// Libera toda a memória alocada para o heap
void liberar_heap(MinHeap* heap) {
    if (!heap) return;
    free(heap->elementos);
    free(heap->posicoes);
    free(heap);
}
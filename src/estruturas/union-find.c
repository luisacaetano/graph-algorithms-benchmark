#include "union-find.h"

// Cria e inicializa a estrutura Union-Find para 'tamanho' elementos
UnionFind* criar_union_find(int tamanho) {
    UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
    if (!uf) return NULL;
    
    // Aloca os vetores de pais e ranks
    uf->pai = (int*)malloc(tamanho * sizeof(int));
    uf->rank = (int*)malloc(tamanho * sizeof(int));
    
    if (!uf->pai || !uf->rank) {
        free(uf->pai);
        free(uf->rank);
        free(uf);
        return NULL;
    }
    
    uf->tamanho = tamanho;
    
    // Inicializa cada elemento como seu próprio pai (cada um em seu conjunto)
    for (int i = 0; i < tamanho; i++) {
        uf->pai[i] = i;
        uf->rank[i] = 0;
    }
    
    return uf;
}

// Encontra o representante do conjunto do elemento x
// Usa compressão de caminho para acelerar buscas futuras
int encontrar(UnionFind* uf, int x) {
    if (uf->pai[x] != x) {
        uf->pai[x] = encontrar(uf, uf->pai[x]);  
    }
    return uf->pai[x];
}

// Une os conjuntos dos elementos x e y
// Usa união por rank para manter a árvore balanceada
int unir(UnionFind* uf, int x, int y) {
    int raiz_x = encontrar(uf, x);
    int raiz_y = encontrar(uf, y);
    
    if (raiz_x == raiz_y) {
        return 0;  
    }
    
    // O conjunto com menor rank aponta para o de maior rank
    if (uf->rank[raiz_x] < uf->rank[raiz_y]) {
        uf->pai[raiz_x] = raiz_y;
    } else if (uf->rank[raiz_x] > uf->rank[raiz_y]) {
        uf->pai[raiz_y] = raiz_x;
    } else {
        uf->pai[raiz_y] = raiz_x;
        uf->rank[raiz_x]++;
    }
    
    return 1;  
}

// Libera toda a memória alocada para a estrutura Union-Find
void liberar_union_find(UnionFind* uf) {
    if (!uf) return;
    free(uf->pai);
    free(uf->rank);
    free(uf);
}
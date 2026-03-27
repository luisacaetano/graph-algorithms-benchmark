#include "leitor-arquivos.h"

// Analisa o formato do arquivo
void analisar_formato_arquivo(const char* caminho_arquivo) {
    FILE* arquivo = fopen(caminho_arquivo, "r");
    if (!arquivo) {
        printf("Erro: Não foi possível abrir o arquivo %s\n", caminho_arquivo);
        return;
    }
    
    printf("=== Análise do arquivo: %s ===\n", caminho_arquivo);
    
    char linha[256];
    int num_linha = 1;
    
    // Lê e imprime as primeiras 5 linhas do arquivo
    while (fgets(linha, sizeof(linha), arquivo) && num_linha <= 5) {
        linha[strcspn(linha, "\n")] = 0; // Remove a quebra de linha
        printf("Linha %d: '%s'\n", num_linha, linha);
        num_linha++;
    }
    
    // Conta o total de linhas do arquivo
    int total_linhas = num_linha - 1;
    while (fgets(linha, sizeof(linha), arquivo)) {
        total_linhas++;
    }
    
    printf("Total de linhas: %d\n", total_linhas);
    printf("=====================================\n\n");
    
    fclose(arquivo);
}

// Lê um grafo não direcionado (para AGM) de um arquivo
Grafo* ler_grafo_agm(const char* caminho_arquivo) {
    FILE* arquivo = fopen(caminho_arquivo, "r");
    if (!arquivo) {
        printf("Erro: Não foi possível abrir o arquivo %s\n", caminho_arquivo);
        return NULL;
    }
    
    int num_vertices, num_arestas;
    
    // Tenta ler o número de vértices e arestas da primeira linha
    if (fscanf(arquivo, "%d %d", &num_vertices, &num_arestas) != 2) {
        // Se não conseguir, tenta ler só o número de vértices
        rewind(arquivo);
        if (fscanf(arquivo, "%d", &num_vertices) != 1) {
            printf("Erro: Formato inválido na primeira linha\n");
            fclose(arquivo);
            return NULL;
        }
        num_arestas = -1; // Desconhecido
    }
    
    printf("Lendo grafo AGM (%s): %d vértices", caminho_arquivo, num_vertices);
    if (num_arestas > 0) {
        printf(", %d arestas\n", num_arestas);
    } else {
        printf("\n");
    }
    
    Grafo* grafo = criar_grafo(num_vertices, 0); // Não direcionado
    if (!grafo) {
        printf("Erro: Não foi possível criar o grafo\n");
        fclose(arquivo);
        return NULL;
    }
    
    // Lê as arestas do arquivo (origem, destino, peso)
    int origem, destino;
    double peso;
    int arestas_lidas = 0;
    while (fscanf(arquivo, "%d %d %lf", &origem, &destino, &peso) == 3) {
        adicionar_aresta(grafo, origem, destino, peso);
        arestas_lidas++;
    }
    
    printf("Arestas lidas: %d\n", arestas_lidas);
    
    fclose(arquivo);
    return grafo;
}

// Lê um grafo direcionado (para Dijkstra) de um arquivo
Grafo* ler_grafo_dijkstra(const char* caminho_arquivo) {
    FILE* arquivo = fopen(caminho_arquivo, "r");
    if (!arquivo) {
        printf("Erro: Não foi possível abrir o arquivo %s\n", caminho_arquivo);
        return NULL;
    }
    
    int num_vertices, num_arestas;
    
    // Tenta ler o número de vértices e arestas da primeira linha
    if (fscanf(arquivo, "%d %d", &num_vertices, &num_arestas) != 2) {
        // Se não conseguir, tenta ler só o número de vértices
        rewind(arquivo);
        if (fscanf(arquivo, "%d", &num_vertices) != 1) {
            printf("Erro: Formato inválido na primeira linha\n");
            fclose(arquivo);
            return NULL;
        }
        num_arestas = -1;
    }
    
    printf("Lendo grafo Dijkstra (%s): %d vértices", caminho_arquivo, num_vertices);
    if (num_arestas > 0) {
        printf(", %d arestas\n", num_arestas);
    } else {
        printf("\n");
    }
    
    Grafo* grafo = criar_grafo(num_vertices, 1); // Direcionado
    if (!grafo) {
        printf("Erro: Não foi possível criar o grafo\n");
        fclose(arquivo);
        return NULL;
    }
    
    // Lê as arestas do arquivo (origem, destino, peso)
    int origem, destino;
    double peso;
    int arestas_lidas = 0;
    while (fscanf(arquivo, "%d %d %lf", &origem, &destino, &peso) == 3) {
        adicionar_aresta(grafo, origem, destino, peso);
        arestas_lidas++;
    }
    
    printf("Arestas lidas: %d\n", arestas_lidas);
    
    fclose(arquivo);
    return grafo;
}

// Função wrapper para decidir qual leitor usar com base no caminho do arquivo
Grafo* ler_grafo_do_arquivo(const char* caminho_arquivo) {
    // Se o caminho contém "agm", usa o leitor de AGM; se contém "caminho-minimo", usa o de Dijkstra
    if (strstr(caminho_arquivo, "agm")) {
        return ler_grafo_agm(caminho_arquivo);
    } else if (strstr(caminho_arquivo, "caminho-minimo")) {
        return ler_grafo_dijkstra(caminho_arquivo);
    } else {
        printf("Erro: Não foi possível identificar o tipo de grafo para o arquivo %s\n", caminho_arquivo);
        return NULL;
    }
}
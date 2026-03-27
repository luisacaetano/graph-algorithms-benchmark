#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <float.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

#include "benchmark.h"
#include "../algoritmos/kruskal.h"
#include "../algoritmos/prim.h"
#include "../algoritmos/dijkstra.h"
#include "leitor-arquivos.h"

#define TIMEOUT_SEGUNDOS 60 // Tempo máximo de execução para alguns benchmarks

static jmp_buf timeout_env;

// Usado para medir o tempo de execução dos algoritmos
double obter_tempo_atual() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1e6;
}

// Manipulador de sinal para timeout
void timeout_handler(int sig) {
    longjmp(timeout_env, 1);
}

// Função auxiliar para decidir se deve aplicar timeout para um arquivo específico
int deve_aplicar_timeout(const char* caminho) {
    return
        strcmp(caminho, "benchmark/agm/grafo-grande.txt") == 0 ||        // Grafo grande AGM
        strcmp(caminho, "benchmark/caminho-minimo/largeEWD.txt") == 0 || // Grafo grande caminho mínimo
        strcmp(caminho, "benchmark/caminho-minimo/10000EWD.txt") == 0;   // Grafo médio-grande caminho mínimo
}

// Função que executa o benchmark dos algoritmos de AGM (Kruskal e Prim)
void executar_benchmark_agm(const char* nome_arquivo) {
    const char* arquivos[] = {
        "benchmark/agm/grafo-pequeno.txt",
        "benchmark/agm/grafo-medio1.txt",
        "benchmark/agm/grafo-medio2.txt",
        "benchmark/agm/grafo-medio3.txt",
        "benchmark/agm/grafo-grande.txt"
    };
    int num_arquivos = sizeof(arquivos) / sizeof(arquivos[0]);
    ResultadoBenchmark resultados[100]; 
    int idx = 0;

    for (int i = 0; i < num_arquivos; i++) {
        // Verifica se o arquivo atual é um dos grandes e precisa de timeout
        if (deve_aplicar_timeout(arquivos[i])) {
            // Configura o handler de sinal para timeout
            signal(SIGALRM, timeout_handler);
            // Salva o contexto de execução; se retornar diferente de 0, houve timeout
            if (setjmp(timeout_env) != 0) {
                printf("Timeout atingido para %s\n", arquivos[i]);
                continue;
            }
            alarm(TIMEOUT_SEGUNDOS);
        }

        // 1. Lê o grafo do arquivo e executa os benchmarks normalmente
        Grafo* g = ler_grafo_do_arquivo(arquivos[i]);

        // 2. Executa Kruskal Ingênuo e mede o tempo
        double inicio = obter_tempo_atual();
        Aresta* agm = malloc(g->num_vertices * sizeof(Aresta));
        double peso = kruskal_ineficiente(g, agm);
        double fim = obter_tempo_atual();
        resultados[idx++] = (ResultadoBenchmark){
            .nome_arquivo = "",
            .algoritmo = "kruskal",
            .versao = "ingenua",
            .tempo_execucao = fim - inicio,
            .peso_agm_acm = peso,
            .num_vertices = g->num_vertices,
            .num_arestas = g->num_arestas
        };
        strcpy(resultados[idx-1].nome_arquivo, arquivos[i]);
        free(agm);

        // 3. Executa Kruskal Eficiente e mede o tempo
        inicio = obter_tempo_atual();
        agm = malloc(g->num_vertices * sizeof(Aresta));
        peso = kruskal_union_find(g, agm);
        fim = obter_tempo_atual();
        resultados[idx++] = (ResultadoBenchmark){
            .nome_arquivo = "",
            .algoritmo = "kruskal",
            .versao = "eficiente",
            .tempo_execucao = fim - inicio,
            .peso_agm_acm = peso,
            .num_vertices = g->num_vertices,
            .num_arestas = g->num_arestas
        };
        strcpy(resultados[idx-1].nome_arquivo, arquivos[i]);
        free(agm);

        // 4. Executa Prim Ingênuo e mede o tempo
        int* pai = malloc(g->num_vertices * sizeof(int));
        inicio = obter_tempo_atual();
        peso = prim_ineficiente(g, pai);
        fim = obter_tempo_atual();
        resultados[idx++] = (ResultadoBenchmark){
            .nome_arquivo = "",
            .algoritmo = "prim",
            .versao = "ingenua",
            .tempo_execucao = fim - inicio,
            .peso_agm_acm = peso,
            .num_vertices = g->num_vertices,
            .num_arestas = g->num_arestas
        };
        strcpy(resultados[idx-1].nome_arquivo, arquivos[i]);
        free(pai);

        // 5. Executa Prim Eficiente e mede o tempo
        pai = malloc(g->num_vertices * sizeof(int));
        inicio = obter_tempo_atual();
        peso = prim_heap(g, pai);
        fim = obter_tempo_atual();
        resultados[idx++] = (ResultadoBenchmark){
            .nome_arquivo = "",
            .algoritmo = "prim",
            .versao = "eficiente",
            .tempo_execucao = fim - inicio,
            .peso_agm_acm = peso,
            .num_vertices = g->num_vertices,
            .num_arestas = g->num_arestas
        };
        strcpy(resultados[idx-1].nome_arquivo, arquivos[i]);
        free(pai);

        liberar_grafo(g); 

        // Cancela o alarme se terminou antes do timeout
        if (deve_aplicar_timeout(arquivos[i])) {
            alarm(0);
        }
    }

    salvar_resultados(resultados, idx, nome_arquivo);
}

// Função que executa o benchmark dos algoritmos de Dijkstra
void executar_benchmark_dijkstra(const char* nome_arquivo) {
    const char* arquivos[] = {
        "benchmark/caminho-minimo/tinyEWD.txt",
        "benchmark/caminho-minimo/mediumEWD.txt",
        "benchmark/caminho-minimo/largeEWD.txt",
        "benchmark/caminho-minimo/1000EWD.txt",
        "benchmark/caminho-minimo/10000EWD.txt"
    };
    int num_arquivos = sizeof(arquivos) / sizeof(arquivos[0]);
    ResultadoBenchmark resultados[100];
    int idx = 0;

    for (int i = 0; i < num_arquivos; i++) {
        // Verifica se o arquivo atual é um dos grandes e precisa de timeout
        if (deve_aplicar_timeout(arquivos[i])) {
            // Configura o handler de sinal para timeout
            signal(SIGALRM, timeout_handler);
            // Salva o contexto de execução; se retornar diferente de 0, houve timeout
            if (setjmp(timeout_env) != 0) {
                printf("Timeout atingido para %s\n", arquivos[i]);
                continue;
            }
            alarm(TIMEOUT_SEGUNDOS);
        }

        // Lê o grafo do arquivo e executa os benchmarks normalmente
        Grafo* g = ler_grafo_do_arquivo(arquivos[i]);
        double* dist = malloc(g->num_vertices * sizeof(double));
        int* pai = malloc(g->num_vertices * sizeof(int));

        // Dijkstra Ingênuo
        double inicio = obter_tempo_atual();
        dijkstra_ineficiente(g, 0, dist, pai);
        double fim = obter_tempo_atual();
        // Calcule a soma dos menores caminhos
        double soma_pesos = 0.0;
        for (int j = 0; j < g->num_vertices; j++) {
            if (dist[j] < INF) 
                soma_pesos += dist[j];
        }
        resultados[idx++] = (ResultadoBenchmark){
            .nome_arquivo = "",
            .algoritmo = "dijkstra",
            .versao = "ingenua",
            .tempo_execucao = fim - inicio,
            .peso_agm_acm = soma_pesos,
            .num_vertices = g->num_vertices,
            .num_arestas = g->num_arestas
        };
        strcpy(resultados[idx-1].nome_arquivo, arquivos[i]);

        // Dijkstra Heap (eficiente)
        inicio = obter_tempo_atual();
        dijkstra_heap(g, 0, dist, pai);
        fim = obter_tempo_atual();
        // Calcule a soma dos menores caminhos novamente
        soma_pesos = 0.0;
        for (int j = 0; j < g->num_vertices; j++) {
            if (dist[j] < INF)
                soma_pesos += dist[j];
        }
        resultados[idx++] = (ResultadoBenchmark){
            .nome_arquivo = "",
            .algoritmo = "dijkstra",
            .versao = "eficiente",
            .tempo_execucao = fim - inicio,
            .peso_agm_acm = soma_pesos,
            .num_vertices = g->num_vertices,
            .num_arestas = g->num_arestas
        };
        strcpy(resultados[idx-1].nome_arquivo, arquivos[i]);

        free(dist);
        free(pai);
        liberar_grafo(g);

        // Cancela o alarme se terminou antes do timeout
        if (deve_aplicar_timeout(arquivos[i])) {
            alarm(0);
        }
    }

    salvar_resultados(resultados, idx, nome_arquivo);
}

// Salva os resultados dos benchmarks em um arquivo CSV
void salvar_resultados(ResultadoBenchmark* resultados, int num_resultados, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "w");
    if (!f) {
        printf("Erro ao abrir arquivo de resultados!\n");
        return;
    }
    // Cabeçalho do CSV
    fprintf(f, "arquivo,algoritmo,versao,tempo_execucao,peso_agm_acm,num_vertices,num_arestas\n");
    for (int i = 0; i < num_resultados; i++) {
        fprintf(f, "%s,%s,%s,%.6f,%.2f,%d,%d\n",
            resultados[i].nome_arquivo,
            resultados[i].algoritmo,
            resultados[i].versao,
            resultados[i].tempo_execucao,
            resultados[i].peso_agm_acm,
            resultados[i].num_vertices,
            resultados[i].num_arestas
        );
    }
    fclose(f);
}

// Lê o arquivo CSV e imprime estatísticas de tempo para cada algoritmo/versão
void analisar_resultados(const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");
    if (!f) {
        printf("Erro ao abrir resultados_benchmark.csv\n");
        return;
    }

    char linha[512];
    fgets(linha, sizeof(linha), f); 

    // Variáveis para estatísticas
    double tempo_total = 0, tempo_min = DBL_MAX, tempo_max = 0;
    int num = 0;

    printf("\n%-40s %-12s %-10s %-15s %-15s\n", "Arquivo", "Algoritmo", "Versão", "Tempo (s)", "Peso");
    printf("%-40s %-12s %-10s %-15s %-15s\n", "----------------------------------------", "----------", "----------", "---------------", "---------------");

    while (fgets(linha, sizeof(linha), f)) {
        char arquivo[256], algoritmo[64], versao[32];
        double tempo, peso;
        int v, a;
        sscanf(linha, "%255[^,],%63[^,],%31[^,],%lf,%lf,%d,%d",
               arquivo, algoritmo, versao, &tempo, &peso, &v, &a);

        printf("%-40s %-12s %-10s %-15.6f %-15.2f\n",
               arquivo, algoritmo, versao, tempo, peso);

        tempo_total += tempo;
        if (tempo < tempo_min) tempo_min = tempo;
        if (tempo > tempo_max) tempo_max = tempo;
        num++;
    }
    fclose(f);

    if (num > 0) {
        printf("\nTempo médio: %.6fs\nTempo mínimo: %.6fs\nTempo máximo: %.6fs\n",
               tempo_total/num, tempo_min, tempo_max);
    }
}

// Compara o tempo das versões ingênua e eficiente para cada algoritmo/arquivo
void comparar_versoes(const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");
    if (!f) {
        printf("Erro ao abrir resultados_benchmark.csv\n");
        return;
    }

    char linha[512];
    fgets(linha, sizeof(linha), f); 

    typedef struct {
        char arquivo[256];
        char algoritmo[64];
        double tempo_ingenua;
        double tempo_eficiente;
    } Comparacao;

    Comparacao comparacoes[100];
    int idx = 0;

    // Lê todos os resultados e armazena para comparação
    while (fgets(linha, sizeof(linha), f)) {
        char arquivo[256], algoritmo[64], versao[32];
        double tempo, peso;
        int v, a;
        sscanf(linha, "%255[^,],%63[^,],%31[^,],%lf,%lf,%d,%d",
               arquivo, algoritmo, versao, &tempo, &peso, &v, &a);

        // Procura se já existe uma entrada para esse arquivo/algoritmo
        int found = 0;
        for (int i = 0; i < idx; i++) {
            if (strcmp(comparacoes[i].arquivo, arquivo) == 0 &&
                strcmp(comparacoes[i].algoritmo, algoritmo) == 0) {
                if (strcmp(versao, "ingenua") == 0)
                    comparacoes[i].tempo_ingenua = tempo;
                else
                    comparacoes[i].tempo_eficiente = tempo;
                found = 1;
                break;
            }
        }
        // Se não existe, cria uma nova entrada
        if (!found) {
            strcpy(comparacoes[idx].arquivo, arquivo);
            strcpy(comparacoes[idx].algoritmo, algoritmo);
            comparacoes[idx].tempo_ingenua = (strcmp(versao, "ingenua") == 0) ? tempo : -1;
            comparacoes[idx].tempo_eficiente = (strcmp(versao, "eficiente") == 0) ? tempo : -1;
            idx++;
        }
    }
    fclose(f);

    printf("\n%-40s %-12s %-15s %-15s %-10s\n", "Arquivo", "Algoritmo", "Ingênua (s)", "Eficiente (s)", "Ganho");
    printf("%-40s %-12s %-15s %-15s %-10s\n", "----------------------------------------", "----------", "---------------", "---------------", "----------");

    // Imprime cada linha da tabela com os tempos e o ganho de desempenho
    for (int i = 0; i < idx; i++) {
        double ganho = (comparacoes[i].tempo_ingenua > 0 && comparacoes[i].tempo_eficiente > 0)
            ? comparacoes[i].tempo_ingenua / comparacoes[i].tempo_eficiente
            : 0.0;
        printf("%-40s %-12s %-15.6f %-15.6f %-10.2fx\n",
               comparacoes[i].arquivo,
               comparacoes[i].algoritmo,
               comparacoes[i].tempo_ingenua,
               comparacoes[i].tempo_eficiente,
               ganho);
    }
}


#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <time.h>
#include <sys/time.h>
#include "../estruturas/grafo.h"

// Estrutura para armazenar os resultados de cada execução de benchmark
typedef struct {
    char nome_arquivo[256];   
    char algoritmo[64];       
    char versao[32];          
    double tempo_execucao;    
    double peso_agm_acm;      
    int num_vertices;         
    int num_arestas;          
} ResultadoBenchmark;

// Estrutura para armazenar estatísticas de tempo de execução
typedef struct {
    double tempo_total;   
    double tempo_medio;   
    double tempo_min;     
    double tempo_max;     
    int num_execucoes;    
} EstatisticasTempo;

// Função para obter o tempo atual em segundos
double obter_tempo_atual();

// Executa os benchmarks dos algoritmos de AGM (Kruskal e Prim)
void executar_benchmark_agm(const char* nome_arquivo);

// Executa os benchmarks dos algoritmos de Dijkstra (caminho mínimo)
void executar_benchmark_dijkstra(const char* nome_arquivo);

// Salva os resultados dos benchmarks em um arquivo CSV
void salvar_resultados(ResultadoBenchmark* resultados, int num_resultados, const char* nome_arquivo);

// Função para analisar os resultados (opcional, para gerar estatísticas)
void analisar_resultados(const char* nome_arquivo);

// Função para comparar as versões dos algoritmos (opcional, para análise)
void comparar_versoes(const char* nome_arquivo);

#endif
#include <stdio.h>
#include <stdlib.h>
#include "utils/benchmark.h"
#include "utils/leitor-arquivos.h"

int main(void) {
    printf("==== Trabalho EDII - Benchmark de Algoritmos de Grafos ====\n\n");

    // Executa benchmarks de AGM (Kruskal e Prim)
    printf("Executando benchmarks de AGM (Kruskal e Prim)...\n");
    executar_benchmark_agm("resultados_agm.csv");

    // Executa benchmarks de Dijkstra (caminho mínimo)
    printf("\nExecutando benchmarks de Dijkstra...\n");
    executar_benchmark_dijkstra("resultados_dijkstra.csv");

    // Analisa e compara os resultados
    printf("\nResultados AGM:\n");
    analisar_resultados("resultados_agm.csv");
    comparar_versoes("resultados_agm.csv");

    printf("\nResultados Dijkstra:\n");
    analisar_resultados("resultados_dijkstra.csv");
    comparar_versoes("resultados_dijkstra.csv");

    printf("\nBenchmark finalizado!\n");
    return 0;
}
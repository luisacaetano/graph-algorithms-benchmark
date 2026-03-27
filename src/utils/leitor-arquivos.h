#ifndef LEITOR_ARQUIVOS_H
#define LEITOR_ARQUIVOS_H

#include "../estruturas/grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para analisar o formato de um arquivo de grafo
void analisar_formato_arquivo(const char* caminho_arquivo);

// Lê um grafo não direcionado (para AGM) de um arquivo
Grafo* ler_grafo_agm(const char* caminho_arquivo);

// Lê um grafo direcionado (para Dijkstra) de um arquivo
Grafo* ler_grafo_dijkstra(const char* caminho_arquivo);

// Função wrapper que decide automaticamente qual função de leitura usar com base no nome/caminho do arquivo (agm ou caminho-minimo).
Grafo* ler_grafo_do_arquivo(const char* caminho_arquivo);

#endif
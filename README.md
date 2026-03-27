# Benchmark de Algoritmos de Grafos

Benchmark comparando implementações ingênuas vs. otimizadas de algoritmos clássicos de grafos: Árvore Geradora Mínima (Kruskal, Prim) e Caminho Mínimo (Dijkstra).

## Algoritmos Implementados

### Árvore Geradora Mínima (AGM)

| Algoritmo | Versão Ingênua | Versão Otimizada |
|-----------|----------------|------------------|
| **Kruskal** | Vetor de componentes O(V²) | Union-Find O(E log V) |
| **Prim** | Busca linear O(V²) | Min-Heap O(E log V) |

### Caminho Mínimo

| Algoritmo | Versão Ingênua | Versão Otimizada |
|-----------|----------------|------------------|
| **Dijkstra** | Busca linear O(V²) | Min-Heap O(E log V) |

## Resultados do Benchmark

### AGM - Kruskal (Ingênuo vs Union-Find)

| Grafo | Vértices | Arestas | Ingênuo (s) | Otimizado (s) | Speedup |
|-------|----------|---------|-------------|---------------|---------|
| Pequeno | 8 | 16 | 0.000014 | 0.000001 | 14x |
| Médio | 1.000 | 8.433 | 0.001993 | 0.000221 | 9x |
| Grande | 10.000 | 61.731 | 0.025018 | 0.001405 | **18x** |

### Caminho Mínimo - Dijkstra (Ingênuo vs Heap)

| Grafo | Vértices | Arestas | Ingênuo (s) | Otimizado (s) | Speedup |
|-------|----------|---------|-------------|---------------|---------|
| Pequeno | 8 | 15 | 0.000002 | 0.000007 | - |
| Médio | 1.000 | 16.866 | 0.000746 | 0.000153 | 5x |
| Grande | 10.000 | 123.462 | 0.069518 | 0.001660 | **42x** |

## Estrutura do Projeto

```
TrabalhoEDII/
├── src/
│   ├── main.c                      # Ponto de entrada
│   ├── algoritmos/
│   │   ├── kruskal.c/h             # Algoritmo de Kruskal
│   │   ├── prim.c/h                # Algoritmo de Prim
│   │   └── dijkstra.c/h            # Algoritmo de Dijkstra
│   ├── estruturas/
│   │   ├── grafo.c/h               # Representação do grafo
│   │   ├── heap.c/h                # Implementação de Min-Heap
│   │   └── union-find.c/h          # Union-Find (Conjunto Disjunto)
│   └── utils/
│       ├── benchmark.c/h           # Utilitários de benchmark
│       └── leitor-arquivos.c/h     # Leitor de arquivos
├── benchmark/
│   ├── agm/                        # Grafos de teste para AGM
│   └── caminho-minimo/             # Grafos de teste para caminho mínimo
├── Makefile
└── README.md
```

## Como Compilar e Executar

```bash
# Compilar
make

# Executar benchmarks
./trabalho-edii

# Limpar arquivos de compilação
make clean
```

## Saída

O programa gera arquivos CSV com os resultados do benchmark:
- `resultados_agm.csv` - Resultados dos algoritmos de AGM
- `resultados_dijkstra.csv` - Resultados do algoritmo de Dijkstra

## Estruturas de Dados

- **Grafo**: Representação por lista de adjacências
- **Min-Heap**: Fila de prioridade para extração eficiente do mínimo
- **Union-Find**: Conjunto disjunto com compressão de caminho e união por rank

## Requisitos

- Compilador GCC
- Make

## Licença

Uso acadêmico.

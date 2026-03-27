# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -g

SRC = src/main.c \
      src/algoritmos/kruskal.c \
      src/algoritmos/prim.c \
      src/algoritmos/dijkstra.c \
      src/estruturas/grafo.c \
      src/estruturas/heap.c \
      src/estruturas/union-find.c \
      src/utils/benchmark.c \
      src/utils/leitor-arquivos.c

OBJ = $(SRC:.c=.o)
EXEC = trabalho-edii

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC) resultados_benchmark.csv

.PHONY: all clean
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -pedantic -std=c99

MAIN = main
AUXILIAR = cost
AUXILIAR2 = dijkstra
AUXILIAR3 = graph
LABEL = set

all: main.c cost.c dijkstra.c graph.c set.o
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN).c $(AUXILIAR).c $(AUXILIAR2).c $(AUXILIAR3).c $(LABEL).o 
	
clean:
	$(RM) $(MAIN) $(AUXILIAR) $(AUXILIAR2) $(AUXILIAR3) $(LABEL) 

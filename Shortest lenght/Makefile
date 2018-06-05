all: Shortest_Path

Shortest_Path: main.o  Dijkstra_tools.o Floyd_warshall.o Helping_functions.o
	gcc main.o Dijkstra_tools.o Floyd_warshall.o Helping_functions.o -o Shortest_Path

main.o: main.c
	gcc -c main.c

Dijkstra_tools.o: Dijkstra_tools.c
	gcc -c Dijkstra_tools.c

Floyd_warshall.o: Floyd_Warshall.c
	gcc -c Floyd_Warshall.c

Helping_functions.o: Helping_functions.c
	gcc -c Helping_functions.c

clean:
	rm *o Shortest_Path

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dijkstra.h"
#include "Helping_functions.h"
#include "Floyd_warshall.h"
#define INF 100

int main() {
    struct a_graph *graph;
    int start;
    int dest;

    graph = calloc(1, sizeof(struct a_graph));
    init_graph(graph);

    printf("\nStarting point:");
    scanf("%d", &start);
    printf("\nDestination point:");
    scanf("%d", &dest);

    print_adj_matrix(graph);

  //  dijkstra(graph, start, dest);

    floyd_marshall(graph, start, dest);

    delete_graph(graph);

    return 0;
}

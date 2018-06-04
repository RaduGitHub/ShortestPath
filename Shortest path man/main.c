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
    int variable;

    graph = calloc(1, sizeof(struct a_graph));
    init_graph(graph);

    printf("\nStarting point:");
    scanf("%d", &start);
    printf("\nDestination point:");
    scanf("%d", &dest);
    assert ( start >= 0 );
    assert ( start < graph->no_nodes );
    assert ( dest >= 0 );
    assert ( dest < graph->no_nodes );
    print_adj_matrix(graph);

    printf ("varialbe=");
    scanf ("%d", &variable);
    assert(variable > 0);
    assert(variable < 3);
    if (variable == 1){
        dijkstra(graph, start, dest);
    } else {
        floyd_marshall(graph, start, dest);
    }
    delete_graph(graph);

    return 0;
}

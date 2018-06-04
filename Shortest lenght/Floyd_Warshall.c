#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dijkstra.h"
#include "Helping_functions.h"
#include "Floyd_warshall.h"

#define INF 100

void floyd_marshall (struct a_graph *graph,int start,int dest){
    int i;
    int j;
    int k;
    int l;
    int aux;

    int init_distance[graph->no_nodes][graph->no_nodes];

    for (i = 0; i < graph->no_nodes; i++){
        for (j = 0; j < graph->no_nodes; j++){
            init_distance[i][j] = get_adj_matrix_value(graph, i, j);
        }
    }

    int distance_k[graph->no_nodes][graph->no_nodes];

    for (i = 0; i < graph->no_nodes; i++){
        for(j = 0; j < graph->no_nodes; j++){
            if (i == j){
                distance_k[i][j] = INF;
            } else {
                distance_k[i][j] = 0;
            }
        }
    }
    for (k = 0; k < graph->no_nodes; k++){
        for (l = 0; l < graph->no_nodes; l++){
            distance_k[k][l] = init_distance[k][l];
            distance_k[l][k] = init_distance[l][k];
        }
        for (i = 0; i < graph->no_nodes; i++){
            if (i == k){
                continue;
            }
            for (j = 0; j < graph->no_nodes; j++){
                if (j == k){
                    continue;
                }
                if (i == j){
                    continue;
                }
                if (init_distance[i][j] > init_distance[i][k] + init_distance[k][j] && graph_bfs(graph, i, j)){
                    distance_k[i][j] = init_distance[i][k] + init_distance[k][j];
                    set_adj_matrix_value(graph, i, j, distance_k[i][j]);
                } else {
                    distance_k[i][j] = init_distance[i][j];
                    set_adj_matrix_value(graph, i, j, init_distance[i][j]);
                }
            }
        }
        for (i = 0; i < graph->no_nodes; i++){
            for (j = 0; j < graph->no_nodes; j++){
                init_distance[i][j] = distance_k[i][j];
            }
        }
    }
    printf("Lenght of the path between %d and %d using Floyd-Warshall: %d\n", start, dest, init_distance[start][dest]);
}

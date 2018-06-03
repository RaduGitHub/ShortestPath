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
    int init_sequence[graph->no_nodes][graph->no_nodes];

    for (i = 0; i < graph->no_nodes; i++){
        for (j = 0; j < graph->no_nodes; j++){
            init_distance[i][j] = get_adj_matrix_value(graph, i, j);
        }
    }
    for (i = 0; i < graph->no_nodes; i++){
        for (j = 0; j < graph->no_nodes; j++){
            if (i < j){
                init_sequence[i][j] = i;
            } else if (i > j){
                init_sequence[i][j] = j;
            } else {
                init_sequence[i][j] = INF;
            }
        }
    }

    int distance_k[graph->no_nodes][graph->no_nodes];
    int sequence_k[graph->no_nodes][graph->no_nodes];

    for (i = 0; i < graph->no_nodes; i++){
        for(j = 0; j < graph->no_nodes; j++){
            if (i == j){
                distance_k[i][j] = INF;
                sequence_k[i][j] = INF;
            } else {
                distance_k[i][j] = 0;
                sequence_k[i][j] = 0;
            }
        }
    }
    for (k = 0; k < graph->no_nodes; k++){
        for (l = 0; l < graph->no_nodes; l++){
            distance_k[k][l] = init_distance[k][l];
            sequence_k[k][l] = init_sequence[k][l];
            distance_k[l][k] = init_distance[l][k];
            sequence_k[l][k] = init_sequence[l][k];
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
                if (init_distance[i][j] > init_distance[i][k] + init_distance[k][j] && graph_bfs(graph, start, dest)){
                    distance_k[i][j] = init_distance[i][k] + init_distance[k][j];
                    set_adj_matrix_value(graph, i, j, distance_k[i][j]);
                    sequence_k[i][j] = k + 1;
                } else {
                    distance_k[i][j] = init_distance[i][j];
                    set_adj_matrix_value(graph, i, j, init_distance[i][j]);
                    sequence_k[i][j] = init_sequence[i][j];
                }
            }
        }
        for (i = 0; i < graph->no_nodes; i++){
            for (j = 0; j < graph->no_nodes; j++){
                init_distance[i][j] = distance_k[i][j];
                init_sequence[i][j] = distance_k[i][j];
            }
        }
    }

    int vector[graph->no_nodes];
    vector[0] = start;
    vector[1] = dest;
    k = 2;
    i = start;
    j = dest;
    while(dest != init_sequence[i][j]){
        aux = vector[k-1];
        vector[k-1] = init_sequence[i][j];
        vector[k] = aux;
        i = vector[k-1];
        k++;
    }
    for (i = 0; i < graph->no_nodes; i++)
        printf("%d -->", vector[i]);
    printf("\n Shortest path:%d", init_distance[start][dest]);
}

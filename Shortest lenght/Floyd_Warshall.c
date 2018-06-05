///@file Floyd_Warshall.c
///@brief C library implementation for basic mathematic functions.
///
/// Created by Caragea Radu-Mihai
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dijkstra.h"
#include "Helping_functions.h"
#include "Floyd_warshall.h"

#define INF 100
///\def #define INF 100
///\brief Define the number that represents that there is no connection

void floyd_warshall (struct a_graph *graph, int start, int dest){
	///\fn void floyd_warshall(struct a_graph *graph, int start, int dest)
	///\brief Returns the shortest path from a starting vertices to a destination
	///\param *graph The graph we go through
	///\param start Starting vertex
	///\param dest Ending vertex
	///
	///Uses the Floyd Warshall algorithm to find the shortest path

	///\var i It is one of the iterators used for this function, mostly representing the rows
    int i;

	///\var j It is one of the iterators used for this function, mostly representing the columns
    int j;

	///\var k It is one of the iterators used for this function, representing the step that this algortihm is at
    int k;

	///\var l Is is one of the iterators used for this function, used for changing values of rows and columns in a matrix
    int l;

	///\var vector A variable that will contain the shortest path from start to dest
	int vector[graph->no_nodes];

	///\var aux A variable that will help adding the vertices of the path in the vector
    int aux;

	///\var init_distance A matrix that first contains the initial matrix, following to change once we start making steps
    int init_distance[graph->no_nodes][graph->no_nodes];

	///\var init_sequence A matrix that will help us find the path once all the steps have been made
    int init_sequence[graph->no_nodes][graph->no_nodes];

	///Initialising init_distance with adj_matrix to get the distance between vertices in it
    for (i = 0; i < graph->no_nodes; i++){
        for (j = 0; j < graph->no_nodes; j++){
            init_distance[i][j] = get_adj_matrix_value(graph, i, j);

        }
    }

	///Initialising init sequence with the conection between nodes
    for (i = 0; i < graph->no_nodes; i++){
        for (j = 0; j < graph->no_nodes; j++){
            if (i == j){
                init_sequence[i][j] = INF;
            } else {
                init_sequence[i][j] = j;
            }
        }
    }

	///\var distance_k A matrix that will contain the distance between vertices at step k
    int distance_k[graph->no_nodes][graph->no_nodes];

	///\var sequence_k A matrix that will contain the connection between shortest distance from a vertex to another at step k
    int sequence_k[graph->no_nodes][graph->no_nodes];

	///We initialise both matrices that represents values at step k with 0
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
	///We start doing steps on solving the problem
    for (k = 0; k < graph->no_nodes; k++){

		///For each iteration we copy the kth row and kth column to the current array
        for (l = 0; l < graph->no_nodes; l++){
			///Copy row
            distance_k[k][l] = init_distance[k][l];
            sequence_k[k][l] = init_sequence[k][l];

			///Copy column
            distance_k[l][k] = init_distance[l][k];
            sequence_k[l][k] = init_sequence[l][k];
        }

		///Compute the distance and sequence value for current iteration
        for (i = 0; i < graph->no_nodes; i++){
			///We skip the kth iteration for the kth row
            if (i == k){
                continue;
            }
            for (j = 0; j < graph->no_nodes; j++){
				///For the kth iteration we skip the kth column
                if (j == k){
                    continue;
                }
				///If i and j are the same, meaning the are the same vertex, we skip it
                if (i == j){
                    continue;
                }
				///Checking if the distance is the shortest or not at step k for each vertex
                if (init_distance[i][j] > init_distance[i][k] + init_distance[k][j] && graph_bfs(graph, i, j)){
                    distance_k[i][j] = init_distance[i][k] + init_distance[k][j];
                    set_adj_matrix_value(graph, i, j, distance_k[i][j]);
                    sequence_k[i][j] = k;
                } else {
                    distance_k[i][j] = init_distance[i][j];
                    set_adj_matrix_value(graph, i, j, init_distance[i][j]);
                    sequence_k[i][j] = init_sequence[i][j];
                }
            }
        }
		///We copy the content of both matrices refering to step k to the initial matrices, init_distance and init_sequence, for each step
        for (i = 0; i < graph->no_nodes; i++){
            for (j = 0; j < graph->no_nodes; j++){
                init_distance[i][j] = distance_k[i][j];
                init_sequence[i][j] = sequence_k[i][j];
            }
        }
    }
    ///We are starting to find the shortest path
	///We begin thinking that the shortest path is from start to dest, meaning we give the 1st and last element of the vector so far those values in order
    vector[0] = start;
    vector[1] = dest;
	///We use a variable to contain the number of vertices the path has
	///In this case the variable we use is k
    k = 2;
	///We use iterators i and j to keep the vertices so far
    i = start;
    j = dest;
	///We check in matrix init_sequence if the destination is equal to the value at the two lasting points in the vector
    while(dest != init_sequence[i][j]){
		///If the destination is different from the vertex in matrix, we make the vertex in matrix second to last
        aux = vector[k-1];
        vector[k-1] = init_sequence[i][j];
        vector[k] = aux;
        i = vector[k-1];
		///We increase k, which represent the number of nodes so far
        k++;
    }
	///Once we found all the nodes, we print them from the vector, starting with 0 , ending with k-1
    for (i = 0; i < k - 1; i++){
        printf("%d --> ", vector[i]);
    }
	///Only to print the destination point last
    printf("%d", dest);
	///We also print the lenght of the path we found
    printf("\nLenght of the path between %d and %d using Floyd-Warshall: %d\n", start, dest, init_distance[start][dest]);
}

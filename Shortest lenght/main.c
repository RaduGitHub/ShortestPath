///@file main.c
///@brief Main function of our project
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

int main() {
	///\fn int main()
	///\brief Main function
	/// Function calls of functions for graph, matrix and solving algorithms. Asks for starting and destination point and which algorithm to use.
	///\var *graph It is the graph that represents the map that it crosses
    struct a_graph *graph;
	///\var start The starting point from which we search for shortest path
    int start;
	///\var dest The point that we need to reach
    int dest;
	///\var variable A variable that makes you choose which algorithm to apply
    int variable;
	///Alocate memory to the graph
    graph = calloc(1, sizeof(struct a_graph));
	///Initialises graph
    init_graph(graph);
	///Scaning the starting and destination point
    printf("\nStarting point:");
    scanf("%d", &start);
    printf("\nDestination point:");
    scanf("%d", &dest);
	///Makes sure that the nodes are in the graph
    assert ( start >= 0 );
    assert ( start < graph->no_nodes );
    assert ( dest >= 0 );
    assert ( dest < graph->no_nodes );
	///Scanning variable for the purpose of choosing the solving algorithm
    printf ("Press 1 for Dijkstra and 2 for Floyd Warshall:");
    scanf ("%d", &variable);
	///Making sure the variable is accepted by the program
    assert(variable > 0);
    assert(variable < 3);
	///Choosing the path based on the variable we just introduced
    if (variable == 1){
		///Calls function which uses Dijkstra algorithm
        dijkstra(graph, start, dest);
    } else {
		///Calls function which uses Floyd Warshall algorithm
        floyd_warshall(graph, start, dest);
    }
	///Calls function that deletes the graph to free the memory
    delete_graph(graph);
	///Returns that there were no errors
    return 0;
}

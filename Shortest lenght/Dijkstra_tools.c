///@file Dijkstra_tools.c
///@brief Functions used only in Dijkstra algorithm
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

int find_min(int x, int y) {
	///\fn int find_min(int x, int y)
    ///\brief Returns the smaller value between two given values
    ///\param x First number
    ///\param y Second number
    ///
	///Implements a function that returns the minimum value between two given numbers
	///We check which number is lower and return it
	if (x < y) {
		return x;
	}
	return y;
}

int is_marked(int v, int marked_vertices[], int marked_vertices_idx) {
	///\fn int is_marked(int v, int marked_vertices[], int marked_vertices_idx)
    ///\brief Checks if the vertex is marked
    ///\param v It is the vertex
    ///\param marked_vertices[] Is an array that contains vertices that are marked
	///\param marked_vertices_idx The vertex at which we stop searching
    ///
	///Implements a function that return values depending on if the vertex is marked or not

	///\var i Iterator going from the starting vertex to the marked_verices_idx
	int i = 0;
	///We start looking if the vertex was marked or not
	for (i = 0; i < marked_vertices_idx; i++) {
		///If the vertex was marked we return 1
		if (v == marked_vertices[i]) {
			return 1;
		}
	}
	///If the vertex was not marked we return 0
	return 0;
}

void dijkstra(struct a_graph *graph, int start, int dest) {
	///\fn void dijkstra(struct a_graph *graph, int start, int dest)
    ///\brief Returns the shortest path from a starting vertex to a destination
    ///\param *graph The graph we go through
    ///\param start Starting vertex
	///\param dest Ending vertex
    ///
	///Uses the Dijkstra algorithm to find the shortest path between two given vertices

	///\var v A variable that will be given the number of vertices from the graph
    int v;

	///\var i Iterator
	int i;

	///\var r Iterator
    int r;

	///\var c Iterator
    int c;

	///\var tmp_c Variable representing new vertex found for marking
    int tmp_c;

	///\var min Variable representing the minimum lenght of the path
    int min;

	///\var curr_vertex Variable representing the current vertex
    int curr_vertex;

	///\var edge_lgth Variable representing the lenght of the edge
    int edge_lgth;

	///\var dest_value Variable used to find a minimum between a path and the one from before
    int dest_value;

	///\var marked_value Variable used to find a minimum between a path and the next one
    int marked_value;

	///\var lgth_table_r Iterator used for vertex
    int lgth_table_r;

	///\var marked_vertices_idx Iterator used for vertices that have been markes
    int marked_vertices_idx;

	///We initialise the variables, expect i, r, c, min and curr_vertex
    edge_lgth = 0;
    dest_value = 0;
    marked_value = 0;
    lgth_table_r = 0;
	tmp_c = start;
    marked_vertices_idx = 0;
    v = graph->no_nodes;

	///\var shortest_path_vertices Array containing vertices in the shortest path
	int shortest_path_vertices[v] ;

	///We initialise the array with 0 in all of his components
	memset(shortest_path_vertices, 0, v*sizeof(int) );

	///\var shortest_path_vertices_idx Iterator which will increase the moment we add more vertices to it, meaning it is the iterator defining the number of vertices in the shortest path
	int shortest_path_vertices_idx = 0;

	///\var lgth_table This matrix will hold the length
	int lgth_table[v][v];

	///We initialise it with the highest value which is defines as INF
	for (r = 0; r < v; r++) {
		for (c = 0; c < v; c++) {
			lgth_table[r][c] = INF;
		}
	}
	///We initialise the first element with 0
	lgth_table[lgth_table_r++][start] = 0;

	///\var marked_vertices Represents vertices that are marked
	int marked_vertices[v] ;

	///We initialise it with 0
	memset( marked_vertices, 0, v*sizeof(int) );

	///We give it the value of the vertex we start searching from
	marked_vertices[marked_vertices_idx++] = start;

	///We give curr_vertex value of the starting vertex
	curr_vertex = start;

	///We start finding the path, entering a loop while destination has not been found
	while(curr_vertex != dest) {

		///We copy the marked values to the next row of lgth_table
		for (i = 0; i < marked_vertices_idx; i++) {
			c = marked_vertices[i];
			lgth_table[lgth_table_r][c] = lgth_table[lgth_table_r - 1][c];
		}

		///We find the length from the current vertex tu all the other vertices that are directly connected and not yet marked
		for (c = 0; c < v; c++) {

			if (c != curr_vertex && !( is_marked(c, marked_vertices, marked_vertices_idx) ) ) {
				edge_lgth = get_adj_matrix_value(graph, curr_vertex, c);
				dest_value = lgth_table[lgth_table_r - 1][c];
				marked_value = lgth_table[lgth_table_r][curr_vertex];

				min = find_min(dest_value, marked_value + edge_lgth);
				lgth_table[lgth_table_r][c] = min;
			}

		}
		///We find the minimum unmarked vertices in current row
		min = INF;
		for (c = 0; c < v; c++) {

			if (!is_marked(c, marked_vertices, marked_vertices_idx) ) {
				if (lgth_table[lgth_table_r][c] < min && graph_bfs(graph, start, dest) ) {
					min = lgth_table[lgth_table_r][c];
					tmp_c = c;
				}
			}
		}
		///Found a new vertex for marking
		marked_vertices[marked_vertices_idx++] = tmp_c;
		curr_vertex = tmp_c;
		///We update the lgth_table_r
		lgth_table_r++;

	}
	///Compute shortest path vertices
	c = dest;
	shortest_path_vertices[shortest_path_vertices_idx++] = c;
	marked_value = lgth_table[lgth_table_r - 1][dest];
	for (r = lgth_table_r - 2; r >= 0; r--) {

		if (lgth_table[r][c] != marked_value) {
			c = marked_vertices[r];
			marked_value = lgth_table[r][c];
			shortest_path_vertices[shortest_path_vertices_idx++] = c;
		}

	}

	///Displaying the shortest path and length
	printf("Shortest Path between %d and %d\n", start, dest);
	for (i = v-1; i >= 0; i--) {
		printf("%d", shortest_path_vertices[i]);
		if (i > 0) {
			printf(" --> ");
		}
	}
	printf("\n");
	printf("Lenght of the path between %d and %d using Dijkstra: %d\n", start, dest, lgth_table[lgth_table_r-1][dest]);

}

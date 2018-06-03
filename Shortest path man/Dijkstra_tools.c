#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dijkstra.h"
#include "Helping_functions.h"
#include "Floyd_warshall.h"

#define INF 100

int find_min(int x, int y) {
	if (x < y) {
		return x;
	}
	return y;
}

int is_marked(int v, int marked_vertices[], int marked_vertices_idx) {

	int i = 0;
	for (i = 0; i < marked_vertices_idx; i++) {
		if (v == marked_vertices[i]) {
			return 1;
		}
	}

	return 0;
}

void dijkstra(struct a_graph *graph, int start, int dest) {

    int v;
	int i;
    int r;
    int c;
    int tmp_c=start;
    int min;
    int curr_vertex;
    int edge_wt;
    int dest_value;
    int marked_value;
    int wt_table_r;
    int marked_vertices_idx;

    edge_wt = 0;
    dest_value = 0;
    marked_value = 0;
    wt_table_r = 0;
    marked_vertices_idx = 0;
    v = graph->no_nodes;

	int shortest_path_vertices[v] ;
	memset(shortest_path_vertices, 0, v*sizeof(int) );
	int shortest_path_vertices_idx = 0;

	int weight_table[v][v];
	for (r = 0; r < v; r++) {
		for (c = 0; c < v; c++) {
			weight_table[r][c] = INF;
		}
	}
	weight_table[wt_table_r++][start] = 0;


	int marked_vertices[v] ;
	memset( marked_vertices, 0, v*sizeof(int) );
	marked_vertices[marked_vertices_idx++] = start;
	curr_vertex = start;

	while(curr_vertex != dest) {


		for (i = 0; i < marked_vertices_idx; i++) {
			c = marked_vertices[i];
			weight_table[wt_table_r][c] = weight_table[wt_table_r - 1][c];
		}
		for (c = 0; c < v; c++) {

			if (c != curr_vertex && !( is_marked(c, marked_vertices, marked_vertices_idx) ) ) {
				edge_wt = get_adj_matrix_value(graph, curr_vertex, c);
				dest_value = weight_table[wt_table_r - 1][c];
				marked_value = weight_table[wt_table_r][curr_vertex];

				min = find_min(dest_value, marked_value + edge_wt);

				weight_table[wt_table_r][c] = min;
			}

		}
		min = INF;
		for (c = 0; c < v; c++) {

			if (!is_marked(c, marked_vertices, marked_vertices_idx) ) {
				if (weight_table[wt_table_r][c] < min && graph_bfs(graph, start, dest) ) {
					min = weight_table[wt_table_r][c];
					tmp_c = c;
				}
			}

		}
		marked_vertices[marked_vertices_idx++] = tmp_c;
		curr_vertex = tmp_c;
		wt_table_r++;

	}
	c = dest;
	shortest_path_vertices[shortest_path_vertices_idx++] = c;
	marked_value = weight_table[wt_table_r - 1][dest];
	for (r = wt_table_r - 2; r >= 0; r--) {

		if (weight_table[r][c] != marked_value) {
			c = marked_vertices[r];
			marked_value = weight_table[r][c];
			shortest_path_vertices[shortest_path_vertices_idx++] = c;
		}

	}

	printf("Shortest Path between %d and %d\n", start, dest);
	for (i = shortest_path_vertices_idx-1; i >= 0; i--) {
		printf("%d", shortest_path_vertices[i]);
		if (i > 0) {
			printf(" --> ");
		}
	}
	printf("\n");
	printf("Weight of the path: %d\n", weight_table[wt_table_r-1][dest]);

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INF 9999
struct a_graph {
    int no_nodes;
    int init;
    int *adj_matrix;
};

struct a_list_node{
    int info;
    struct a_list_node *next;
};

int get_adj_matrix_value(struct a_graph *graph, int row_index, int column_index) {
    int position;

    assert(row_index < graph->no_nodes);
    assert(column_index < graph->no_nodes);
    if (graph->init == 1){
        position = row_index * graph->no_nodes + column_index;
        return *(graph->adj_matrix + position);
    }else{
        printf("Please read the graph first");
        return -1;
    }
}

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

void dijkstra(struct a_graph *graph, int src, int dest) {

    printf("asd");
    int v;
	int i;
    int r;
    int c;
    int tmp_c;
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
    v=graph->no_nodes;

	int shortest_path_vertices[v] ;
	memset(shortest_path_vertices, 0, v*sizeof(int) );
	int shortest_path_vertices_idx = 0;


	int weight_table[v][v];
	for (r = 0; r < v; r++) {
		for (c = 0; c < v; c++) {
			weight_table[r][c] = INF;
		}
	}
	weight_table[wt_table_r++][src] = 0;


	int marked_vertices[v] ;
	memset( marked_vertices, 0, v*sizeof(int) );
	marked_vertices[marked_vertices_idx++] = src;
	curr_vertex = src;

    printf("asd");
	while(curr_vertex != dest) {


		for (i = 0; i < marked_vertices_idx; i++) {
			c = marked_vertices[i];
			weight_table[wt_table_r][c] = weight_table[wt_table_r - 1][c];
		}
		for (c = 0; c < v; c++) {

			if (c != curr_vertex && !is_marked(c, marked_vertices, marked_vertices_idx)) {

				edge_wt = get_adj_matrix_value(graph, curr_vertex, c);
				dest_value = weight_table[wt_table_r - 1][c];
				marked_value = weight_table[wt_table_r][curr_vertex];

				min = find_min(dest_value, marked_value + edge_wt);

				weight_table[wt_table_r][c] = min;
                printf("asd");
			}

		}
		min = INF;
		for (c = 0; c < v; c++) {

			if (!is_marked(c, marked_vertices, marked_vertices_idx)) {
				if (weight_table[wt_table_r][c] < min) {
					min = weight_table[wt_table_r][c];
					tmp_c = c;
					printf("\nasd");
				}
			}

		}
		marked_vertices[marked_vertices_idx++] = tmp_c;
		curr_vertex = tmp_c;
		wt_table_r++;
		printf("\nmarked vertices idx  %d", marked_vertices_idx);

	}
	printf("asd");
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

    printf("asd");
	printf("Shortest Path between %d and %d\n", src, dest);
	for (i = shortest_path_vertices_idx-1; i >= 0; i--) {
		printf("%d", shortest_path_vertices[i]);
		if (i > 0) {
			printf(" --> ");
		}
	}
	printf("\n");
	printf("Weight of the path: %d\n", weight_table[wt_table_r-1][dest]);

}

void set_adj_matrix_value(struct a_graph *graph, int row_index, int column_index, int element_value){
    int position;

    assert(row_index < graph->no_nodes);
    assert(column_index < graph->no_nodes);
    position = row_index * graph->no_nodes + column_index;
    *(graph->adj_matrix + position) = element_value;
}

void init_graph(struct a_graph *graph){
    int iterator_rows;
    int iterator_columns;
    int aux;

    printf("\nGive no nodes = ");
    scanf("%d", &graph->no_nodes);
    graph->init = 1;
    graph->adj_matrix = calloc(graph->no_nodes * graph->no_nodes,sizeof(int));

    assert((graph->no_nodes * graph->no_nodes) > 0);

    for (iterator_rows = 0; iterator_rows < graph->no_nodes; iterator_rows++ ){
        for (iterator_columns = 0; iterator_columns < graph->no_nodes; iterator_columns++ ){
            printf(" graph[%d][%d]= ",iterator_rows, iterator_columns);
            scanf("%d", &aux);
            set_adj_matrix_value(graph, iterator_rows, iterator_columns, aux);
        }
    }
}

void print_adj_matrix(struct a_graph *graph){
    int iterator_rows;
    int iterator_columns;
    int aux;

    if (graph->init == 1){
        printf("=== Printing adj_matrix ===\n");
        for (iterator_rows = 0; iterator_rows < graph->no_nodes; iterator_rows++ ){
            for (iterator_columns = 0; iterator_columns < graph->no_nodes; iterator_columns++ ){
                aux = get_adj_matrix_value(graph, iterator_rows, iterator_columns);
                printf(" %d ", aux);
            }
            printf("\n");
        }
    }else{
        printf("\nPlease read the adj_matrix first");
    }
}

void delete_graph(struct a_graph *graph){
    free(graph->adj_matrix);
    free(graph);
}
int main() {
    struct a_graph *graph;
    int start;
    int dest;

    graph = calloc(1, sizeof(struct a_graph));
    init_graph(graph);
    printf("\nStarting point:");
    scanf("%d", &start);
    printf("\nDestination point:");
    scanf("%d", &start);
    print_adj_matrix(graph);
    dijkstra(graph, start, dest);

    delete_graph(graph);

    return 0;
}

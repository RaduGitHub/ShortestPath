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

void push_begining_list(struct a_list_node *head, int new_element_value){
    struct a_list_node *next_element;
    struct a_list_node *new_element;

    next_element = head->next;
    new_element = malloc(sizeof(struct a_list_node));
    new_element->info = new_element_value;
    new_element->next = head->next;
    head->next = new_element;
}

int pop_end_list(struct a_list_node *head) {
    struct a_list_node *deleted_element;
    struct a_list_node *iterator;
    int aux;

    if (head->next != NULL) {
        for (iterator = head; iterator->next->next != NULL; iterator = iterator->next);
        deleted_element = iterator->next;
        aux = deleted_element->info;
        iterator->next = deleted_element->next;
        free(deleted_element);
        return aux;
    } else {
        printf("\n The list is empty");
        return -1; //the list is empty
    }
}

int graph_bfs(struct a_graph *graph, int start_node, int dest_node){
    struct a_list_node *head_queue;
    int *visited;
    int aux;
    int current_node;
    int connect;
    int i;
    int j;

    connect = get_adj_matrix_value(graph, start_node, dest_node);

    set_adj_matrix_value(graph, start_node, dest_node, 0);
    set_adj_matrix_value(graph, dest_node, start_node, 0);

    head_queue = calloc(1, sizeof(struct a_list_node));
    head_queue->next = NULL;
    head_queue->info = 0; //no of elements in the queue
    visited = calloc((graph->no_nodes), sizeof(int));
    push_begining_list(head_queue, start_node);
    visited[start_node] = 1;

    while (head_queue->next != NULL){
        current_node = pop_end_list(head_queue);
        for(i = 0; i < graph->no_nodes; i++){
            aux = get_adj_matrix_value(graph, current_node, i);
            if ( (aux != 0) && ( (visited[i]) == 0 )){
                push_begining_list(head_queue, i);
                visited[i] = 1;
            }
        }
    }
    if( visited[dest_node] == 0 && visited[start_node] == 0 ){
        set_adj_matrix_value(graph, start_node, dest_node, connect);
        set_adj_matrix_value(graph, dest_node, start_node, connect);
        free(head_queue);
        free(visited);
        return 0;
    }
    set_adj_matrix_value(graph, start_node, dest_node, connect);
    set_adj_matrix_value(graph, dest_node, start_node, connect);
    free(head_queue);
    free(visited);
    return 1;
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
    int aux;
    int i;

    graph = calloc(1, sizeof(struct a_graph));
    init_graph(graph);
    printf("\nStarting point:");
    scanf("%d", &start);
    printf("\nDestination point:");
    scanf("%d", &dest);
    print_adj_matrix(graph);
    dijkstra(graph, start, dest);
/*    for(i = 0; i < graph->no_nodes; i++){
        aux=graph_bfs(graph, i, dest);
        printf("\n aux=%d", aux);
    }
    */
    delete_graph(graph);

    return 0;
}

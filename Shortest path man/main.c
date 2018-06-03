#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

    graph = calloc(1, sizeof(struct a_graph));
    init_graph(graph);
    print_adj_matrix(graph);

    delete_graph(graph);
}

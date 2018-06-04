#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dijkstra.h"
#include "Helping_functions.h"
#include "Floyd_warshall.h"

#define INF 100

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

    printf("\nPlease use numbers lower than 100, and use 100 to make it so there is no connection between nodes");
    for (iterator_rows = 0; iterator_rows < graph->no_nodes; iterator_rows++ ){
        for (iterator_columns = 0; iterator_columns < graph->no_nodes; iterator_columns++ ){
            printf("\n graph[%d][%d]= ",iterator_rows, iterator_columns);
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

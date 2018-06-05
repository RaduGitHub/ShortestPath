///@file Helping_functions.c
///@brief Functions for different uses such as printing the adj_matrix, initialising the graph, etc
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

int get_adj_matrix_value(struct a_graph *graph, int row_index, int column_index) {
	///\fn int get_adj_matrix_value(struct a_graph *graph, int row_index, int column_index)
	///\brief Gets the value at a given point in the matrix
	///\param *graph The graph we go through
	///\param row_index The row in which we get the value from
	///\param column_index The column in which we get the value from
	///
	///Implements a function that gets the value of a specific point and returns it

	///\var position An integer that helps us returning the value
    int position;

	///Using assert to make sure the given values for either row_index and column_index can be searched for
    assert(row_index < graph->no_nodes);
    assert(column_index < graph->no_nodes);
	///We need to see if the graph was initialised or not
    if (graph->init == 1){
		///If the graph was initialised, we put the value in variable position
        position = row_index * graph->no_nodes + column_index;
		///We return that value
        return *(graph->adj_matrix + position);
    }else{
		///If the graph was not initialised we print the fact that it need to be initialised first
        printf("Please read the graph first");
		///We return -1 meaning there was an error
        return -1;
    }
}

void push_begining_list(struct a_list_node *head, int new_element_value){
	///\fn void push_begining_list(struct a_list_node *head, int new_element_value)
	///\brief Pushes an element at the beggining of a list
	///\param *head The head of the list
	///\param new_element_value The value which we push at the beggining of a list
	///
	///Implements a function pushes a value into the list

	///\var *new_elemnt The element we want to add to the beggining of the list
    struct a_list_node *new_element;

	///We allocate memory for the new element that we will add to the list
    new_element = malloc(sizeof(struct a_list_node));
	///We give that element the value which shall be added
    new_element->info = new_element_value;
	///We connect the element we add to the first element
    new_element->next = head->next;
	///We connect the head with the new element that we add, which becomes the first one
    head->next = new_element;
}

int pop_end_list(struct a_list_node *head) {
	///\fn int pop_end_list(struct a_list_node *head)
	///\brief Deletes the last element of the list
	///\param head The head of the list
	///
	///Implements a function pushes a value into the list

	///\var *deleted_element The element which shall be deleted
    struct a_list_node *deleted_element;

	///\var *iterator The element that will count untill the last element
    struct a_list_node *iterator;

	///\var aux The value of the element which shall be deleted
    int aux;

	///Checks if the list is empty
    if (head->next != NULL) {
		///Cycles through the list until we reach the second last element
        for (iterator = head; iterator->next->next != NULL; iterator = iterator->next);
		///We store the last element in deleted_element
        deleted_element = iterator->next;
		///We give the aux variable the value of the element
        aux = deleted_element->info;
		///we connect the second last element to NULL
        iterator->next = deleted_element->next;
		///We free the memory allocated to the element we delete
        free(deleted_element);
		///We return the value we deleted
        return aux;
    } else {
		///If the list is empyt, we print the fact that the list should be initialised
        printf("\n The list is empty");
		///We return the value -1 to show that there was an error
        return -1;
    }
}

int graph_bfs(struct a_graph *graph, int start_node, int dest_node){
	///\fn int graph_bfs(struct a_graph *graph, int start_node, int dest_node)
	///\brief Searches for a path
	///\param *graph The graph we go through
	///\param start_node The node from which we start
	///\param dest_node The node we want to reach
	///
	///Implements a function that searches if there is a path between two vertices withouth a path, which we will mark
	///

	///\var *head_queue It is a list that represents a queue which will be used to see if we passed through all the elements
    struct a_list_node *head_queue;

	///\var *visited An array that will mark the vertices we passed through
    int *visited;

	///\var aux Will check if the value of the element in the adj_matrix is one that means there is no connection
    int aux;

	///\var current_node It is the node we currently are, the one we search all connection of
    int current_node;

	///\var connect It is a variable that will contain a value in the adj_matrix, for the purpose of destroting the path between two vertices
    int connect;

	///\var i Iterator used for going through adj_matrix
    int i;

	///We give the connect the value of the value in the adj_matrix
    connect = get_adj_matrix_value(graph, start_node, dest_node);

	///We seth both values in the adj_matrix to 0, making it look like there is no path between the two vertices
    set_adj_matrix_value(graph, start_node, dest_node, 0);
    set_adj_matrix_value(graph, dest_node, start_node, 0);

	///We allocate memory to the queue
    head_queue = calloc(1, sizeof(struct a_list_node));
    head_queue->next = NULL;
	///We make it so there is no element in the queue
    head_queue->info = 0;
	///We allocate memory to the array representing visited vertices
    visited = calloc((graph->no_nodes), sizeof(int));
	///We use a function to add a node to the queue
    push_begining_list(head_queue, start_node);
	///We mark the node from which we start so that we will  not pass through it again
    visited[start_node] = 1;

	///We go through the graph as long as the queue is not empty
    while (head_queue->next != NULL){
		///We take the last vertex and look for vertices connected to this one
        current_node = pop_end_list(head_queue);
        for(i = 0; i < graph->no_nodes; i++){
			///We give aux the value in the adj_matrix
            aux = get_adj_matrix_value(graph, current_node, i);
			///We check if it is different than 0, meaning there is a path between those vertices and also if the vertex was visited
            if ( (aux != 0) && ( (visited[i]) == 0 )){
				///If the node was not visited and the value is different than 0 we push the element in the list and mark the vertex as visited
                push_begining_list(head_queue, i);
                visited[i] = 1;
            }
        }
    }
	///We check if the vertices that we needed to go through were not visited
    if( visited[dest_node] == 0 && visited[start_node] == 0 ){
		///If those were not visited, we put the adj_matrix back as it was in the beggining
        set_adj_matrix_value(graph, start_node, dest_node, connect);
        set_adj_matrix_value(graph, dest_node, start_node, connect);
		///We free the variables for the queue and visited vertices
        free(head_queue);
        free(visited);
		///We return 0 to represent that we dont have 2 paths between those two vertices
        return 0;
    }
	///If the vertices were visited we dont go through the if, and we do the first two steps
    set_adj_matrix_value(graph, start_node, dest_node, connect);
    set_adj_matrix_value(graph, dest_node, start_node, connect);
    free(head_queue);
    free(visited);
	///We return 1 meaning there are two paths between those two vertices
    return 1;
}

void set_adj_matrix_value(struct a_graph *graph, int row_index, int column_index, int element_value){
	///\fn void set_adj_matrix_value(struct a_graph *graph, int row_index, int column_index, int element_value)
	///\brief Puts element in a given position
	///\param *graph The graph we go through
	///\param row_index The row in which we will put the value
	///\param column_index The column in which we will put the value
	///\param element_value The value we put in the given position
	///
	///Implements a function that puts a given value in a given position
	///
	///\var position The position in which we will put the value
    int position;

	///We verify if the position exists in the graph or not
    assert(row_index < graph->no_nodes);
    assert(column_index < graph->no_nodes);
	///If the position exists, we transform the given indexes into the position
    position = row_index * graph->no_nodes + column_index;
	///We put the value of the element_value in the adj_matrix
    *(graph->adj_matrix + position) = element_value;
}

void init_graph(struct a_graph *graph){
	///\fn void init_graph(struct a_graph *graph)
	///\brief Initialises the graph
	///\param *graph The graph we go through
	///
	///Implements a function that implements the adj_matrix of the given graph to show connection between vertices
	///
	///\var iterator_rows Iterator representing rows in matrix
    int iterator_rows;

	///\var iterator_columns Iterator representing columns in matrix
    int iterator_columns;

	///\var change The variable we will use to add values to the matrix
    int change;

	///We give the graph the number of vertices
    printf("\nGive no nodes = ");
    scanf("%d", &graph->no_nodes);

	///After we give the number of nodes we show that the graph was initialised with the graph->init element getting the value 1
    graph->init = 1;

	///We allocate memory for the adj_matrix that we will initialise
    graph->adj_matrix = calloc(graph->no_nodes * graph->no_nodes,sizeof(int));

	///We verify if the value given to the number of vertices is higher than 0
    assert((graph->no_nodes * graph->no_nodes) > 0);

    printf("\nPlease use numbers lower than 100, and use 100 to make it so there is no connection between nodes");
	///We start going through the rows and columns of the matrix and give values to the elements as we go
    for (iterator_rows = 0; iterator_rows < graph->no_nodes; iterator_rows++ ){
        for (iterator_columns = 0; iterator_columns < graph->no_nodes; iterator_columns++ ){
            printf("\n graph[%d][%d]= ",iterator_rows, iterator_columns);
            scanf("%d", &change);
            set_adj_matrix_value(graph, iterator_rows, iterator_columns, change);
        }
    }
}

void print_adj_matrix(struct a_graph *graph){
	///\fn void print_adj_matrix(struct a_graph *graph)
	///\brief Prints the adj_matrix
	///\param *graph The graph we go through
	///
	///Implements a function prints the adj_matrix of the graph
	///
	///\var iterator_rows Iterator representing the row
    int iterator_rows;

	///\var iterator_columns Iterator representing the column
    int iterator_columns;

	///\var change2 The variable we will use to get the value from the adj_matrix and print it out
    int change2;

	///We verify if the graph was initialised
    if (graph->init == 1){
		///If the graph was initialised, we start going through the rows and columns of the adj_matrix and printing them
        printf("=== Printing adj_matrix ===\n");
        for (iterator_rows = 0; iterator_rows < graph->no_nodes; iterator_rows++ ){
            for (iterator_columns = 0; iterator_columns < graph->no_nodes; iterator_columns++ ){
                change2 = get_adj_matrix_value(graph, iterator_rows, iterator_columns);
                printf(" %d ", change2);
            }
            printf("\n");
        }
    }else{
		///If the graph was not initialised we are asked to initialise it
        printf("\nPlease read the adj_matrix first");
    }
}

void delete_graph(struct a_graph *graph){
	///\fn void delete_graph(struct a_graph *graph)
	///\brief Deletes the graph
	///\param *graph The graph we go through
	///
	///Implements a function that frees the memory allocated to the graph
	///
	///We first free the adj_matrix so we dont lose it and be stuck with memory we cant free
    free(graph->adj_matrix);
	///We then free the graph
    free(graph);
}

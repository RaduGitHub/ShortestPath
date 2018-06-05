///@file Helping_functions.h
///@brief Different functions used throughtout the program.
///
///Created by Caragea Radu-Mihai

#ifndef DOXY_FUNCTIONS_H
#define DOXY_FUNCTIONS_H

int get_adj_matrix_value(struct a_graph *graph, int row_index, int column_index);
void push_begining_list(struct a_list_node *head, int new_element_value);
int pop_end_list(struct a_list_node *head);
int graph_bfs(struct a_graph *graph, int start_node, int dest_node);
void set_adj_matrix_value(struct a_graph *graph, int row_index, int column_index, int element_value);
void init_graph(struct a_graph *graph);
void print_adj_matrix(struct a_graph *graph);
void delete_graph(struct a_graph *graph);
#endif // DOXY_FUNCTIONS_H

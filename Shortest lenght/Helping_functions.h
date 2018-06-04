int get_adj_matrix_value(struct a_graph *graph, int row_index, int column_index);
void push_begining_list(struct a_list_node *head, int new_element_value);
int pop_end_list(struct a_list_node *head);
int graph_bfs(struct a_graph *graph, int start_node, int dest_node);
void set_adj_matrix_value(struct a_graph *graph, int row_index, int column_index, int element_value);
void init_graph(struct a_graph *graph);
void init_graph(struct a_graph *graph);
void delete_graph(struct a_graph *graph);

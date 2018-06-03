struct a_graph {
    int no_nodes;
    int init;
    int *adj_matrix;
};

struct a_list_node{
    int info;
    struct a_list_node *next;
};

int find_min(int x, int y);
int is_marked(int v, int marked_vertices[], int marked_vertices_idx);
void dijkstra(struct a_graph *graph, int start, int dest);

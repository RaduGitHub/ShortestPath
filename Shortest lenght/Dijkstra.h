///@file Dijkstra.h
///@brief Headers only for Dijkstra functions.
///
///Created by Caragea Radu-Mihai

#ifndef DOXY_DIJKSTRA_H
#define DOXY_DIJKSTRA_H

struct a_graph {
    ///\ Struct that defines a graph
    ///\var no_nodes Stores number of nodes in the graph
    int no_nodes;
    ///\var init Sees if the graph is initialised or not
    int init;
    ///\var *adj_matrix Pointer to the adj matrix
    int *adj_matrix;
};

struct a_list_node{
    int info;
    struct a_list_node *next;
};


int find_min(int x, int y);
int is_marked(int v, int marked_vertices[], int marked_vertices_idx);
void dijkstra(struct a_graph *graph, int start, int dest);
#endif //DOXY_DIJKSTRA_H

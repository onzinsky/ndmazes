#ifndef UTIL_H
#define UTIL_H
#include "graph.hpp"

class Generator {
    
public:
    
    int init_graph(Graph *g, int n, int d, bool verGeneracion, bool genPasoPaso, int tParada);

    void print_maze(Graph *g, int n, int d);

private:

    void _watch(Graph *g, int n, int d, int node, int other_node, bool watch, bool stepByStep, chrono::milliseconds dura);

    bool add_edge(int node, int other_node, int d, int n);

    int **init_nodes(Graph *g, int *coords, int ind_x, int ind_y, int dimensiones_x, int dimensiones_y, int n, int d);

    bool is_even(int i, int n);

    int *retrieve_nodes(Graph *g, int **nodes, int d, int *coords_node_1, int *coords_node_2 );

    bool is_open(Graph *g, int **nodes, int *coords, int par, int n, int d);

    int one_is_even_not_limit(int *coords, int n, int d);

    void update_coords(int *coords, int n, int d, int coord, int dims_eje);

    bool all_are_odd(int *ctdrs, int d);
    
};
#endif
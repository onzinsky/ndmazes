#ifndef GRAPH_H
#define GRAPH_H

#include "ipair.hpp"

using namespace std;

class Graph
{
public:
    int V, E;
    vector<pair<int, iPair>> edges;
    vector<iPair> open_edges;
    
    Graph(int V);
    Graph(int V, int E);

    void add_edge(int u, int v, int rnk);
    bool contains(iPair edge);
    
};
#endif
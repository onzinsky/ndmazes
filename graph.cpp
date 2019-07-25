// Source: https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/
// Altered by onz
#include "graph.hpp"
#include "union_find.hpp"

using namespace std;

// Constructor 
Graph::Graph(int V, int E) 
{ 
	this->V = V; 
	this->E = E; 
}

// Constructor 
Graph::Graph(int V) 
{
	this->V = V;
}

// Utility function to add an edge 
void Graph::add_edge(int u, int v, int rnk) 
{ 
	edges.push_back({rnk, {u, v}});
}

// Bad way of doing this. Slow. But does the trick for now.
bool Graph::contains(iPair edge){
	vector<iPair>::iterator it;
	
	it = find (open_edges.begin(), open_edges.end(), edge);
	if (it != open_edges.end())
		return true;
	it = find (open_edges.begin(), open_edges.end(), make_pair(edge.second, edge.first));
	if (it != open_edges.end())
		return true;
	return false;
}

#ifndef DSETS_h
#define DSETS_h

class UnionFind 
{ 

public:
	int *parent;
	int n, *rnk;

	// Constructor. 
	UnionFind(int n);
	
	// Find the padre of a node 'u' 
	// Path Compression 
	int find(int u);

	// Union
	void merge(int x, int y);
}; 
#endif
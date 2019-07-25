// Source: https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/
// Altered by onz
#include "union_find.hpp"

// Constructor. 
UnionFind::UnionFind(int n) 
{ 
    // Allocate memory 
    this->n = n; 
    parent = new int[n];
    rnk = new int[n];

    // Initially, all vertices are in 
    // different sets and have rank 0. 
    for (int i = 0; i < n; i++) 
    { 
        rnk[i] = 0;
        //every element is parent of itself 
        parent[i] = i; 
    } 
} 

// Find the parent of a node 'u' 
// Path Compression 
int UnionFind::find(int u) 
{ 
    /* Make the parent of the nodes in the path 
    from u--> parent[u] point to parent[u] */
    if (u != parent[u]) 
        parent[u] = find(parent[u]); 
    return parent[u]; 
} 

// Union
void UnionFind::merge(int x, int y) 
{ 
    x = find(x), y = find(y); 

    /* Make tree with smaller height 
    a subtree of the other tree  */
    if (rnk[x] > rnk[y]) 
        parent[y] = x; 
    else // If rnk[x] <= rnk[y] 
        parent[x] = y; 

    if (rnk[x] == rnk[y]) 
        rnk[y]++;
} 

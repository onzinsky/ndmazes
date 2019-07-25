// Source: https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/
// Altered by onz
#include<bits/stdc++.h>
#include <cmath>
#include <chrono>

#include "kruskal.hpp"
#include "graph.hpp"
#include "union_find.hpp"
#include "generator.hpp"
#include "clear_screen.hpp"

using namespace std;
using namespace std::chrono;

// Generates the maze. 
// It works by joining nodes so when it ends, the 'g' has its 'open_edges' filled.
//
void Kruskal::kruskalMST(Graph *g, int n, int d, bool watch, bool stepByStep, int stopTime) 
{ 
	Generator generator;
	chrono::milliseconds dura(stopTime);
	random_device rd;
	mt19937 random(rd());
	
	int mst_wt = 0; // Initialize result 

	// To check if nodes were joined. If false, dont print the maze (even if watch) is true, 
	// cause no changes were made.
	//
	bool print = false; 

	shuffle(g->edges.begin(), g->edges.end(), random); 

	// Create disjoint sets 
	UnionFind uf(g->V);
 
	// Iterate through all sorted edges 
	vector<pair<int, iPair>>::iterator it; 
	
	for ( it=g->edges.begin(); it!=g->edges.end(); it++ ) 
	{ 
		int u = it->second.first; 
		int v = it->second.second; 

		int set_u = uf.find(u); 
		int set_v = uf.find(v); 

		// Check if the selected edge is creating 
		// a cycle or not (Cycle is created if u 
		// and v belong to same set) 
		if (set_u != set_v) 
		{ 
			print = true;

			g->open_edges.push_back({u, v});
			
			// Update MST weight 
            mst_wt += it->first; 

			// Merge two sets 
			uf.merge(set_u, set_v); 
		} else { print = false; }


		// Print the maze if watch is true.
		if(it == --g->edges.end())
			print = watch;
		if( watch && print ){
			generator.print_maze(g, n, d);
			if( stepByStep ){
				getchar();
				if(it != --g->edges.end())
					ClearScreen();
			} else {	
				this_thread::sleep_for( dura );
				if(it != --g->edges.end())
					ClearScreen();
			}
		}
	}
}

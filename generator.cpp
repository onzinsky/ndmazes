#include <stdio.h>
#include <cmath>

#include "generator.hpp"
#include "graph.hpp"
#include "clear_screen.hpp"

using namespace std;


// Initializes a graph to create the maze.
//
//  - n: number of nodes in each side of the squares.
//  - d: number of dimensions.
//  - watch: if true, the program will stop each time it creates an edge.
//
// Next two only apply if watch is true. And are mutually exclusive.
//
//	- stepByStep: if true, program stops until the user presses any key.
//  - stopTime: time (in millis) the program stops each time it adds an edge.
//
int Generator::init_graph(Graph *g, int n, int D, bool watch, bool stepByStep, int stopTime)
{
	chrono::milliseconds dura(stopTime);
	
	// For each node, and dimension
	for(int node=0; node<g->V; node++){
	  for(int d=0; d<D; d++){
		  
		  // Get what the next node would be
		  int other_node = node+pow(n,d);
		  
		  // If current node (i) needs an edge with other_node
		  if( other_node<g->V && add_edge(node, other_node, d, n) ){

			g->add_edge(node, other_node, 0);			
			_watch(g, n, d, node, other_node, watch, stepByStep, dura); // Watch the creation
		  }
	  }
	}
	g->open_edges.clear(); // Clear the open_edges only used for printing (for now)
	g->E = g->edges.size();
	return g->E;
}

// TODO: this is not working properly
//
// If watch is true, the program stops and prints the maze.
// If stepByStep is true, stop with getchar().
// Else, the program stops for the 'duration' given in millis.
//
void Generator::_watch(Graph *g, int n, int d, int node, int other_node, bool watch, bool stepByStep, chrono::milliseconds dura){
	
	if( watch ){
		// Add to open_edges just to print
		g->open_edges.push_back({node, other_node});
		print_maze(g, n, d);
		if( stepByStep ){
			getchar();
			ClearScreen();
		} else {	
			this_thread::sleep_for( dura );
			ClearScreen();
		}
	}
}


// Returns true if an edge has to be added from 'node' to 'other_node'.
// Not hard to understand, but hard to explain the logic of this here. 
// Will do in post.
//
bool Generator::add_edge(int node, int other_node, int d, int n){
	return ((int)(node / pow(n,d+1))) == ((int)(other_node / pow(n,d+1)));
}


// True if 'i' is divisible by 2 and not 'n' or 0
//
bool Generator::is_even(int i, int n){
	return i%2==0 && i!=0 && i!=n;
}


// Prints the maze to console. 
//
void Generator::print_maze(Graph *g, int n, int d)
{
	// Will hold coordinates in the 'd' dimension space
	int *coords = new (nothrow) int[d];

	// Total num of * needed going down and to the right
	int ind_x = 1, ind_y = 1;

	// Num of dimensions in each axis
	int dimensions_x = 0, dimensions_y = 0;

	for(int i=0; i<d; i++){
		if(i%2!=0){
			dimensions_x++;
			ind_x *= (n * 2 +1);
		} else {
			dimensions_y++;
			ind_y *= (n * 2 +1);
		}
		coords[i] = 0;
	}

	// The 'nodes' variable contains a list.
	// Each element of the list is another list containing:
	// 		- Node's value.
	//		- Coordinates of the node ('d' numbers).
	//
	int **nodes = init_nodes(g, coords, ind_x, ind_y, dimensions_x, dimensions_y, n, d);


	for(int y=0; y<ind_y; y++){

		for(int x=0; x<ind_x; x++){

			// This will hold the index of the even coordinate.
			int even = one_is_even_not_limit(coords,n*2,d);

			if( all_are_odd(coords, d) ){ // Is node
				
				printf("  ");
			
			} else if( even!=-1 ) { // Is wall

				if( is_open(g, nodes, coords, even, n, d) ){
					
					printf("  ");
				} else {
					
					printf(" *");
				}
			} else printf(" *"); // Neither node nor wall
			
			if(coords[d-2]==n*2){
				printf(" ");
			}

			update_coords(coords, n, d, d-2, dimensions_x);
		}

		printf("\n");

		if(coords[d-1]==n*2){
			printf("\n");
		}

		update_coords(coords, n, d, d-1, dimensions_y);

	}
}

// Returns a list of lists. Each list element has:
// - the node
// - the 'd' coordinates of the node
//
int **Generator::init_nodes(Graph *g, int *coords, int ind_x, int ind_y, int dimensions_x, int dimensions_y, int n, int d){

	int **nodes = new int*[g->V];
	for(int i = 0; i < g->V; ++i) {
		nodes[i] = new int[d+1];
	}
	int ctr_node = 0;
	for(int y=0; y<ind_y; y++){
		for(int x=0; x<ind_x; x++){

			if(all_are_odd(coords, d)){ // Is node
			
				int j;
				for(j=0; j<d; j++)
					nodes[ctr_node][j] = coords[j];
			
				nodes[ctr_node][j] = ctr_node;
				ctr_node++;
			}
			update_coords(coords, n, d, d-2, dimensions_x);
		}
		update_coords(coords, n, d, d-1, dimensions_y);
	}
	return nodes;
}


// Checks if a wall is open. Which means: 
//
// Given a wall with coordinates 'coords'. 
// Which nodes is the wall joining?
// Does that pair of nodes exist in 'g->open_edges'?
//
// Return true if it does. False if it doesn't.
//
bool Generator::is_open(Graph *g, int **nodes, int *coords, int even, int n, int d){
	
	int *coords_node_1 = new (nothrow) int[d+1], 
		*coords_node_2 = new (nothrow) int[d+1];
	
	// Get the coordinates of the two nodes the wall divides.
	for(int i=0; i<d; i++){
		if(i==even){
			coords_node_1[i] = coords[i]-1;
			coords_node_2[i] = coords[i]+1;
		} else {
			coords_node_1[i] = coords[i];
			coords_node_2[i] = coords[i];
		}
	}

	// The two values of the nodes
	int *vals_nodes = retrieve_nodes(g, nodes, d, coords_node_1, coords_node_2 );
	return g->contains({vals_nodes[0], vals_nodes[1]});
}

// Gets the values of two nodes given their coordinates.
int *Generator::retrieve_nodes(Graph *g, int **nodes, int d, int *coords_node_1, int *coords_node_2 ){
	
	int node_1 = -1, node_2 = -1;
	
	for(int i=0; i<g->V; i++){
		
		int coordenadas_iguales_1 = 0;
		int coordenadas_iguales_2 = 0;
		int j;

		for(j=0; j<d; j++){

			if(nodes[i][j]==coords_node_1[j]){ coordenadas_iguales_1++; }
			if(nodes[i][j]==coords_node_2[j]){ coordenadas_iguales_2++; }
		}

		bool is_same_node_1 = coordenadas_iguales_1==d;
		bool is_same_node_2 = coordenadas_iguales_2==d;
		
		// If both coordinates are the same, save the values.
		if( is_same_node_1 ){ node_1 = nodes[i][j]; }
		if( is_same_node_2 ){ node_2 = nodes[i][j]; }

	}
	return new int[2]{node_1, node_2};
}


// True if one of the ints in 'coords' is even, and not 0 nor n.
int Generator::one_is_even_not_limit(int *coords, int n, int d){

	int one_even = -1, i;

	for( i=0; i<d; i++ ){
		if( coords[i]==0||coords[i]==n )
			return one_even;
	}
	for( i=0; i<d; i++ ){
		if( is_even(coords[i],n) ){
			if( one_even==-1 ){
				one_even = i;
			} else return -1;
		}
	}
	return one_even;
}


// Updates the coordinates. The user only has to update the last 2 coordinates.
// The rest update themselves.
//
void Generator::update_coords(int *coords, int n, int d, int coord, int dims_eje){
	if( coords[coord]==n*2 ) {
		coords[coord] = 0;
		if( coord-2>-1 ){
			update_coords(coords, n, d, coord-2, dims_eje);
		}
	}
	else coords[coord] = coords[coord]+1;
}


// True if all numbers of coords are odd.
//
bool Generator::all_are_odd(int *coords, int d){
	for(int i=0; i<d; i++)
		if(coords[i]%2==0) return false;
	return true;
}


#include<bits/stdc++.h>
#include <cmath>
#include <chrono>

#include "graph.hpp"
#include "generator.hpp"
#include "kruskal.hpp"

using namespace std;
using namespace std::chrono;

int 	n 				= 3, 
		d 				= 2, 
		stop_time 		= 250,
		test_start, test_finish, test_interval;

bool	cre_steps		= false, // Graph creation step by step
		gen_steps		= false, // MST generation step by step
		cre_watch  		= false, // Watch graph creation
		gen_watch 		= false, // Watch MST generation
		no_print 		= false, // Don't print the maze at the end
		print_k_time 	= false, // Watch graph creation
		print_oe 		= false, // Print open edges
		print_g_init_t	= false, // Print graph init time
		print_oe_sort_t = false, // Print open edges sort time
		print_nums 		= false, // Print num of nodes and edges
		testing 		= false; // Testing. Explained in README

Generator generator;

int main(int argc, char *argv[]) 
{

	for(int i=0; i<argc; i++){
		if(string(argv[i])=="-n"){
			if(i+1<argc) n = atoi(argv[i+1]);
		}
		if(string(argv[i])=="-d"){
			if(i+1<argc) d = atoi(argv[i+1]);
		}
		if(string(argv[i])=="-n-p"){
			no_print = true;
		}
		if(string(argv[i])=="-p-k-t"){
			print_k_time = true;
		}
		if(string(argv[i])=="-p-o-e"){
			print_oe = true;
		}
		if(string(argv[i])=="-p-g-i-t"){
			print_g_init_t = true;
		}
		if(string(argv[i])=="-p-n"){
			print_nums = true;
		}
		if(string(argv[i])=="-w-g"){
			gen_watch = true;
			if(i+1<argc){
				if(string(argv[i+1])=="-s")
					gen_steps = true;
				else if(string(argv[i+1])=="-s-t")
					if(i+2<argc) stop_time = atoi(argv[i+2]);
			}
		}
		if(string(argv[i])=="-w-c"){ // Not working properly
			/*cre_watch = true;
			if(i+1<argc){
				if(string(argv[i+1])=="-steps")
					cre_steps = true;
				else if(string(argv[i+1])=="-stop-time"){
					if(i+2<argc) stop_time = atoi(argv[i+2]);
				}
			}*/
		}
		
		if(string(argv[i])=="-testing"){
			if(i+3<argc){
				testing = true;
				test_start = atoi(argv[i+1]);
				test_finish = atoi(argv[i+2]);
				test_interval = atoi(argv[i+3]);
			}
		}
	}


	// Testing loop. If -testing is not specified, will execute 1 time
	for(int i=(testing?test_start:0); i<(testing?test_finish+1:1); i+=(testing?test_interval:1)){
		

		if(testing) n = i;
		int V = pow(n, d);
		int E = 0;
		Graph g(V);


		// Init graph
		ti1 = high_resolution_clock::now();
		E = generator.init_graph(&g, n, d, cre_watch, gen_steps, stop_time);
		ti2 = high_resolution_clock::now();
		auto dur_ini = duration_cast<milliseconds>( ti2 - ti1 ).count(); // t.inicializacion
		

		// Create MST
		high_resolution_clock::time_point tk1 = high_resolution_clock::now();
		Kruskal k;
		k.kruskalMST(&g, n, d, gen_watch, cre_steps, stop_time);
		high_resolution_clock::time_point tk2 = high_resolution_clock::now();
		auto dur_k = duration_cast<milliseconds>( ti2 - ti1 ).count(); // t.pr
		

		// Order open_edges
		ti1 = high_resolution_clock::now();
		sort(g.open_edges.begin(), g.open_edges.end());
		ti2 = high_resolution_clock::now();
		auto dur_s = duration_cast<milliseconds>( ti2 - ti1 ).count(); // t.sorting open_edges


		// Print the maze
		if(!no_print){
			generator.print_maze(&g, n, d);
		}
		if(print_nums){
			printf("Num. Nodes: %d\n", V);
			printf("Num. Edges: %d\n", E);
		}
		if(print_oe){
			printf("Open edges:\n");
			for(int i=0; i<g.open_edges.size(); i++)
				printf("(%d, %d)%c", g.open_edges[i].first, g.open_edges[i].second, i<g.open_edges.size()-1 ? ',':' '); 
			printf("\n\n");
		}
		if(print_g_init_t){
			printf("Graph init time: %lld\n", dur_ini);
		}
		if(print_oe_sort_t){
			if(!testing) printf("Open edges sort time: %lld\n", dur_s);
		}
		if(print_k_time){
			printf("Kruskal time: %lld\n", dur_k);
		}
		if(testing){ // Just print a new line to separate iterations
			printf("\n");
		}
	}
	printf("Finished!\n\n");

	return 0; 
}

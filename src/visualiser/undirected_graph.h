#ifndef UNDIRECTED_GRAPH
#define UNDIRECTED_GRAPH

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "util.h"

// A struct to represent an adjacenct list node in the graph
typedef struct adj_list_node {
    int node;
    struct adj_list_node *next;
} adj_list_node;

// A struct to represent an adjacency list
typedef struct adj_list {
    int size;
    struct adj_list_node *head;
} adj_list;

// A struct to represent an undirected graph using an array of adjacency lists
typedef struct undirected_graph {
    // The number of nodes in the graph.
    int size; 
    struct adj_list *adj_list;
} undirected_graph;


// Creates a new adjacency list node
adj_list_node *create_adj_list_node(int node);

// Creates a graph with the given number of nodes and no arcs
undirected_graph *create_undirected_graph(int size);

// Adds an arc between the two nodes
void add_arc(undirected_graph *graph, int source, int target);

// Returns the number of arcs in the graph
int get_num_arcs(undirected_graph *graph);

// Returns the number of nodes in the graph
int get_num_nodes(undirected_graph *graph);

// Returns 1 if arc between the two nodes exists, 0 otherwise
bool has_arc(undirected_graph *graph, int source, int target);

// Frees all memory allocated for the graph
void free_undirected_graph(undirected_graph *graph);

// Returns the degree of a node 
int get_degree(undirected_graph *graph, int vertex);

#endif

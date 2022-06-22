#ifndef UNDIRECTED_GRAPH
#define UNDIRECTED_GRAPH

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

// A struct to represent an adjacenct list node in the graph
typedef struct undirected_node {
    int index;
    // struct adj_list_node *next;
} undirected_node;

typedef struct undirected_arc {
    undirected_node source;
    undirected_node target;
    undirected_arc *next_in_list;
} undirected_arc;

/*
// A struct to represent an adjacency list
typedef struct adj_list {
    int size;
    struct adj_list_node *head;
} adj_list;
*/

// A struct to represent an undirected graph using an array of adjacency lists
typedef struct undirected_graph_t {
    int num_nodes;
    undirected_node current_node;
    undirected_arc *visited_arcs;
    int num_visited_arcs;
    int **adj_matrix;
    bool *visited;
    undirected_node *node_arr;
} undirected_graph_t;


// Creates a new adjacency list node
undirected_node *create_adj_list_node(int node);

// Creates a graph with the given number of nodes and no arcs
undirected_graph_t *create_undirected_graph(int size);

// Adds an arc between the two nodes
void add_arc(undirected_graph_t *graph, int source, int target);

// Returns the number of arcs in the graph
int get_num_arcs(undirected_graph_t *graph);

// Returns the number of nodes in the graph
int get_num_nodes(undirected_graph_t *graph);

// Returns 1 if arc between the two nodes exists, 0 otherwise
bool has_arc(undirected_graph_t *graph, int source, int target);

// Frees all memory allocated for the graph
void free_undirected_graph(undirected_graph_t *graph);

// Returns the degree of a node 
int get_degree(undirected_graph_t *graph, int vertex);

// Prints the adjacency list of the graph
void print_undirected_graph_adj_list(undirected_graph_t *graph);

#endif

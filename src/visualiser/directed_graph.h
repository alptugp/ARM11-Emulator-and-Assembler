#ifndef DIRECTED_GRAPH
#define DIRECTED_GRAPH

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "util.h"

//A struct to represent an adjecency list node in the directed graph
typedef struct directed_node {
    int index;
    directed_node next_node;
} directed_node;

typedef struct directed_arc {
    directed_node source;
    directed_node target;
    directed_arc *next_in_list;
} directed_arc;

// A struct to represent a directed graph using an array of adjacency lists
typedef struct directed_graph_t {
    int num_nodes;
    directed_node current_node;
    directed_node next_node;
    directed_arc *visited_arcs;
    int num_visited_arcs;
    int **adj_matrix;
    bool *visited;
    directed_node *node_arr;
} directed_graph_t

#endif
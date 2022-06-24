#ifndef UNDIRECTED_GRAPH
#define UNDIRECTED_GRAPH

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_PARENT -1

// A struct to represent an adjacenct list node in the graph
typedef struct undirected_node {
    int index;
    // struct adj_list_node *next;
} undirected_node;

typedef struct undirected_arc {
    undirected_node source;
    undirected_node target;
    struct undirected_arc *next_in_list;
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
    undirected_node *parent_arr;
    undirected_node start_node;
} undirected_graph_t;


undirected_graph_t undirected_initialise_helper(bool open_from_file, char filename[]);

void free_undirected_graph(undirected_graph_t *undirected_graph);

#endif

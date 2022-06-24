#ifndef UTILS
#define UTILS

#include <stdbool.h>
#include <assert.h>
#include "undirected_graph.h"

#define USER_IN_MAX_LENGTH 500
#define MAX_SIZE 0
#define MAX_MATRIX_SIZE 0
#define NUM_VISITED_ARCS 0

typedef union graph_union_t {
    // PUT GRAPH REPRESENTATION STRUCTS HERE
    undirected_graph_t undirected_graph;
} graph_union_t;

// Pointer to a function that initialises an algorithm-specific graph
// and returns it as part of a graph_repr union
typedef graph_union_t (*initialise_t)(void);

// Pointer to a function that executes one step of a specific algorithm
// on a graph.
// Function modifies the contents of its graph_repr param appropriately,
// and returns an integer exit code.
typedef int (*one_step_t)(graph_union_t*);


// Pointer to a function that visualises an algorithm-specific graph,
// which is passed as a member of the graph_repr union.
// Returns true iff we should terminate immediately.
typedef bool (*visualise_t)(graph_union_t);

void strip_trailing_newline(char *str);

void str_stdin(char **buffer_ptr);

void str_file_in(char **buffer_ptr, FILE *fp);

graph_union_t undirected_initialise(void);

#endif

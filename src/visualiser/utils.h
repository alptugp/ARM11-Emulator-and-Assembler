#ifndef UTILS
#define UTILS

#define ALGO_NAME_MAX_LENGTH 0

typedef union graph_union_t {
    // PUT GRAPH REPRESENTATION STRUCTS HERE
} graph_union_t;

// Pointer to a function that initialises an algorithm-specific graph
// and returns it as part of a graph_repr union
typedef graph_union_t (*initialise_t)();

// Pointer to a function that executes one step of a specific algorithm
// on a graph.
// Function modifies the contents of its graph_repr param appropriately,
// and returns an integer exit code.
typedef int (*one_step_t)(graph_union_t*);


// Pointer to a function that visualises an algorithm-specific graph,
// which is passed as a member of the graph_repr union.
typedef void (*visualise_t)(graph_union_t);

#endif

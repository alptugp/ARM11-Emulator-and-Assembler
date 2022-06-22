#include "utils.h"
#include <string.h>
#include <stdio.h>


static void initialise_algorithm(initialise_t *initialise, one_step_t *one_step, visualise_t *visualise) {
    printf("Enter an algorithm you wish to explore.\n");
    printf("The currently supported algorithms are: '%s'\n", "DFS");
    char algo_name[ALGO_NAME_MAX_LENGTH];
    fgets(algo_name, sizeof(algo_name), stdin);
    strip_trailing_newline(algo_name);
    if(strcmp(algo_name, "DFS") == 0) {
        initialise = &initialise_undirected;
    }
    else {
        printf("Not a valid algorithm name.\n");
        initialise_algorithm(initialise, one_step, visualise);
    }
}

int dfs_one_step(graph_union_t *graph_union) {
    undirected_graph_t graph = graph_union->undirected_graph;
    (graph.visited)[graph.current_node.index] = true;
    graph.num_visited_arcs++;
    undirected_arc *curr = graph.visited_arcs;

    while (curr) {
        curr = curr->next_in_list;
    }

    curr->source = graph.current_node;
    curr->next_in_list = NULL; 

    for (int i = 0; i < graph.num_nodes; i++) {
        if (!graph.visited[i] && graph.adj_matrix[graph.current_node.index][i] != 0) {
            curr->target = graph.node_arr[i];
            graph.current_node = graph.node_arr[i];
            break;
         }
    }

    if (graph.num_visited_arcs == graph.num_nodes) {
        return 1;
    } 

    return 0;
}

int main() {
    initialise_t initialise;
    one_step_t one_step;
    visualise_t visualise;

    initialise_algorithm(&initialise, &one_step, &visualise);

    graph_union_t graph_union = (*initialise)();

    int terminate = 0;
    while (!terminate) {
        terminate = (*one_step)(&graph_union);
        terminate |= (*visualise)(graph_union);
    }
    
    printf("Exiting.\n");

    return 0;
}

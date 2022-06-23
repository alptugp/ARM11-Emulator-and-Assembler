#include "dfs_one_step.h"

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

    if (graph.num_visited_arcs == graph.num_nodes - 1) {
        return 1;
    } 

    for (int i = 0; i < graph.num_nodes; i++) {
        if (!graph.visited[i] && graph.adj_matrix[graph.current_node.index][i] != 0) {
            curr->target = graph.node_arr[i];
            graph.parent_arr[i] = graph.current_node;
            graph.current_node = graph.node_arr[i];
            return 0;
         }
    }

    // Backtraks to the parent node since there are no unvisited adjacent nodes to current node
    graph.current_node = graph.parent_arr[graph.current_node.index];
    return 0;
}

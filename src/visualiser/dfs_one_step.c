#include "dfs_one_step.h"

int dfs_one_step(graph_union_t *graph_union) {
    undirected_graph_t *graph = &(graph_union->undirected_graph);
    (graph->visited)[graph->current_node.index] = true;

    bool found_unvisited_adjacent = false;
    for (int i = 0; i < graph->num_nodes; i++) {
        if (!graph->visited[i] && graph->adj_matrix[graph->current_node.index][i]) {
            undirected_arc *new_arc = malloc(sizeof(undirected_arc));
            new_arc->source = graph->current_node;
            new_arc->target = graph->node_arr[i];
            new_arc->next_in_list = NULL;
            if(!graph->visited_arcs) {
                graph->visited_arcs = new_arc;
            }
            else {
                undirected_arc *curr = graph->visited_arcs;
                while (curr->next_in_list) {
                    curr = curr->next_in_list;
                }
                curr->next_in_list = new_arc;
            }
            graph->parent_arr[i] = graph->current_node;
            graph->current_node = (undirected_node) {graph->node_arr[i].index};
            found_unvisited_adjacent = true;
            graph->num_visited_arcs++;
            break;
         }
    }

    if(found_unvisited_adjacent) {
       return 0;
    }

    // There are no unvisited adjacent nodes to current node
    // Backtrack
    graph->current_node = graph->parent_arr[graph->current_node.index];
    if(graph->current_node.index == 0) {
        return 1;
    }
    return 0;
}

#include "dfs_one_step.h"
#include "utils.h"
#include <assert.h>

static void test_initializer(undirected_graph_t *undirected_graph, int num_nodes, int adj_matrix[num_nodes][num_nodes]) {
    undirected_graph->num_nodes = num_nodes;

    undirected_node node_arr[num_nodes];

    for (int i = 0; i < num_nodes; i++) { 
        undirected_node new_node = {i};
        node_arr[i] = new_node;
    }

    undirected_graph->node_arr = node_arr;
    undirected_graph->current_node = undirected_graph->node_arr[0];

    bool visited[num_nodes];

    for (int i = 0; i < num_nodes; i++) {
        visited[i] = false;
    }

    undirected_graph->visited = visited;
    undirected_graph->visited_arcs = NULL;
    undirected_graph->num_visited_arcs = 0;

    for (int row = 0; row < num_nodes; row++) {
        for (int col = 0; col < num_nodes; col++) {
            adj_matrix[row][col] = 0;
        }
    }
}

static void copy_adj_matrix(undirected_graph_t *undirected_graph, int num_nodes, int adj_matrix[num_nodes][num_nodes]) {
    for (int row = 0; row < num_nodes; row++) {
        for (int col = 0; col < num_nodes; col++) {
            undirected_graph->adj_matrix[row][col] = adj_matrix[row][col];
        }
    }    
}

void normal_graph_1_dfs_test() {
    undirected_graph_t *undirected_graph = malloc(sizeof(undirected_graph_t));
    int num_nodes = 5;

    int adj_matrix[num_nodes][num_nodes];

    test_initializer(undirected_graph, num_nodes, adj_matrix);

    adj_matrix[0][1] = 1;
    adj_matrix[1][0] = 1;

    adj_matrix[1][4] = 1;
    adj_matrix[4][1] = 1;

    adj_matrix[1][3] = 1;
    adj_matrix[3][1] = 1;

    adj_matrix[3][4] = 1;
    adj_matrix[4][3] = 1;

    adj_matrix[0][4] = 1;
    adj_matrix[4][0] = 1;

    adj_matrix[1][2] = 1;
    adj_matrix[2][1] = 1;

    adj_matrix[2][3] = 1;
    adj_matrix[3][2] = 1;

    copy_adj_matrix(undirected_graph, num_nodes, adj_matrix);

    graph_union_t *undirected_graph_union = malloc(sizeof(graph_union_t));
    undirected_graph_union->undirected_graph = *undirected_graph;

    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);

    undirected_graph_t graph_after_dfs = undirected_graph_union->undirected_graph;
    int current_node_index_after_dfs = 4;

    assert(graph_after_dfs.current_node.index == current_node_index_after_dfs);
    assert(graph_after_dfs.num_nodes == num_nodes);

    for (int i = 0; i < num_nodes; i++) {
        if (&graph_after_dfs.parent_arr[i] != NULL) {
            // is not an unconnected node 
            assert(graph_after_dfs.visited[i]);
        }
    }

    undirected_arc *curr = graph_after_dfs.visited_arcs; 
    assert(curr->source.index == 0);
    assert(curr->target.index == 1);
    curr = curr->next_in_list;
    assert(curr->source.index == 1);
    assert(curr->target.index == 2);
    curr = curr->next_in_list;
    assert(curr->source.index == 2);
    assert(curr->target.index == 3);
    curr = curr->next_in_list;
    assert(curr->source.index == 3);
    assert(curr->target.index == 4);
}

void unconnected_graph_dfs_test() {
    undirected_graph_t *undirected_graph = malloc(sizeof(undirected_graph_t));
    int num_nodes = 6;

    int adj_matrix[num_nodes][num_nodes];

    test_initializer(undirected_graph, num_nodes, adj_matrix);

    adj_matrix[0][1] = 1;
    adj_matrix[1][0] = 1;

    adj_matrix[0][3] = 1;
    adj_matrix[3][0] = 1;

    adj_matrix[1][3] = 1;
    adj_matrix[3][1] = 1;

    adj_matrix[1][2] = 1;
    adj_matrix[2][1] = 1;

    adj_matrix[3][4] = 1;
    adj_matrix[4][3] = 1;

    copy_adj_matrix(undirected_graph, num_nodes, adj_matrix);

    graph_union_t *undirected_graph_union = malloc(sizeof(graph_union_t));
    undirected_graph_union->undirected_graph = *undirected_graph;

    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);

    undirected_graph_t graph_after_dfs = undirected_graph_union->undirected_graph;
    int current_node_index_after_dfs = 4;

    assert(graph_after_dfs.current_node.index == current_node_index_after_dfs);
    assert(graph_after_dfs.num_nodes == num_nodes);

    for (int i = 0; i < num_nodes; i++) {
        if (&graph_after_dfs.parent_arr[i] != NULL) {
            // is not an unconnected node 
            assert(graph_after_dfs.visited[i]);
        }
    }

    undirected_arc *curr = graph_after_dfs.visited_arcs; 
    assert(curr->source.index == 0);
    assert(curr->target.index == 1);
    curr = curr->next_in_list;
    assert(curr->source.index == 1);
    assert(curr->target.index == 2);
    curr = curr->next_in_list;
    assert(curr->source.index == 1);
    assert(curr->target.index == 3);
    curr = curr->next_in_list;
    assert(curr->source.index == 3);
    assert(curr->target.index == 4);
}

void complete_graph_dfs_test() {
     undirected_graph_t *undirected_graph = malloc(sizeof(undirected_graph_t));
    int num_nodes = 4;

    int adj_matrix[num_nodes][num_nodes];

    test_initializer(undirected_graph, num_nodes, adj_matrix);

    adj_matrix[0][1] = 1;
    adj_matrix[1][0] = 1;

    adj_matrix[0][2] = 1;
    adj_matrix[2][0] = 1;

    adj_matrix[0][3] = 1;
    adj_matrix[3][0] = 1;

    adj_matrix[2][3] = 1;
    adj_matrix[3][2] = 1;

    adj_matrix[1][3] = 1;
    adj_matrix[3][1] = 1;

    adj_matrix[1][2] = 1;
    adj_matrix[2][1] = 1;

    copy_adj_matrix(undirected_graph, num_nodes, adj_matrix);

    graph_union_t *undirected_graph_union = malloc(sizeof(graph_union_t));
    undirected_graph_union->undirected_graph = *undirected_graph;

    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);

    undirected_graph_t graph_after_dfs = undirected_graph_union->undirected_graph;
    int current_node_index_after_dfs = 3;

    assert(graph_after_dfs.current_node.index == current_node_index_after_dfs);
    assert(graph_after_dfs.num_nodes == num_nodes);

    for (int i = 0; i < num_nodes; i++) {
        if (&graph_after_dfs.parent_arr[i] != NULL) {
            // is not an unconnected node 
            assert(graph_after_dfs.visited[i]);
        }
    }

    undirected_arc *curr = graph_after_dfs.visited_arcs; 
    assert(curr->source.index == 0);
    assert(curr->target.index == 1);
    curr = curr->next_in_list;
    assert(curr->source.index == 1);
    assert(curr->target.index == 2);
    curr = curr->next_in_list;
    assert(curr->source.index == 2);
    assert(curr->target.index == 3);
}

void normal_graph_2_dfs_test() {
    undirected_graph_t *undirected_graph = malloc(sizeof(undirected_graph_t));
    int num_nodes = 8;

    int adj_matrix[num_nodes][num_nodes];

    test_initializer(undirected_graph, num_nodes, adj_matrix);

    adj_matrix[0][1] = 1;
    adj_matrix[1][0] = 1;

    adj_matrix[1][2] = 1;
    adj_matrix[2][1] = 1;

    adj_matrix[1][3] = 1;
    adj_matrix[3][1] = 1;

    adj_matrix[3][4] = 1;
    adj_matrix[4][3] = 1;

    adj_matrix[3][5] = 1;
    adj_matrix[5][3] = 1;

    adj_matrix[5][6] = 1;
    adj_matrix[6][5] = 1;

    adj_matrix[6][7] = 1;
    adj_matrix[7][6] = 1;

    adj_matrix[0][7] = 1;
    adj_matrix[7][0] = 1;

    adj_matrix[3][7] = 1;
    adj_matrix[7][3] = 1;

    copy_adj_matrix(undirected_graph, num_nodes, adj_matrix);

    graph_union_t *undirected_graph_union = malloc(sizeof(graph_union_t));
    undirected_graph_union->undirected_graph = *undirected_graph;

    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);

    undirected_graph_t graph_after_dfs = undirected_graph_union->undirected_graph;
    int current_node_index_after_dfs = 7;

    assert(graph_after_dfs.current_node.index == current_node_index_after_dfs);
    assert(graph_after_dfs.num_nodes == num_nodes);

    for (int i = 0; i < num_nodes; i++) {
        if (&graph_after_dfs.parent_arr[i] != NULL) {
            // is not an unconnected node 
            assert(graph_after_dfs.visited[i]);
        }
    }

    undirected_arc *curr = graph_after_dfs.visited_arcs; 
    assert(curr->source.index == 0);
    assert(curr->target.index == 1);
    curr = curr->next_in_list;
    assert(curr->source.index == 1);
    assert(curr->target.index == 2);
    curr = curr->next_in_list;
    assert(curr->source.index == 1);
    assert(curr->target.index == 3);
    curr = curr->next_in_list;
    assert(curr->source.index == 3);
    assert(curr->target.index == 4);
    curr = curr->next_in_list;
    assert(curr->source.index == 3);
    assert(curr->target.index == 5);
    curr = curr->next_in_list;
    assert(curr->source.index == 5);
    assert(curr->target.index == 6);
    curr = curr->next_in_list;
    assert(curr->source.index == 6);
    assert(curr->target.index == 7);
}

void singleton_graph_dfs_test() {
    undirected_graph_t *undirected_graph = malloc(sizeof(undirected_graph_t));
    int num_nodes = 1;
    undirected_graph->num_nodes = num_nodes;

    undirected_node node_arr[num_nodes];

    undirected_node new_node = {0};
    node_arr[0] = new_node;

    undirected_graph->node_arr = node_arr;
    undirected_graph->current_node = undirected_graph->node_arr[0];

    int adj_matrix[num_nodes][num_nodes];

    for (int row = 0; row < num_nodes; row++) {
        for (int col = 0; col < num_nodes; col++) {
            adj_matrix[row][col] = 0;
        }
    }

    for (int row = 0; row < num_nodes; row++) {
        for (int col = 0; col < num_nodes; col++) {
            undirected_graph->adj_matrix[row][col] = adj_matrix[row][col];
        }
    }

    bool visited[num_nodes];

    for (int i = 0; i < num_nodes; i++) {
        visited[i] = false;
    }

    undirected_graph->visited = visited;
    undirected_graph->visited_arcs = NULL;
    undirected_graph->num_visited_arcs = 0;

    graph_union_t *undirected_graph_union = malloc(sizeof(graph_union_t));
    undirected_graph_union->undirected_graph = *undirected_graph;

    dfs_one_step(undirected_graph_union);

    undirected_graph_t graph_after_dfs = undirected_graph_union->undirected_graph;
    int current_node_index_after_dfs = 0;

    assert(graph_after_dfs.current_node.index == current_node_index_after_dfs);
    assert(graph_after_dfs.num_nodes == num_nodes);

    for (int i = 0; i < num_nodes; i++) {
        if (&graph_after_dfs.parent_arr[i] != NULL) {
            // is not an unconnected node 
            assert(graph_after_dfs.visited[i]);
        }
    }
    
    assert(graph_after_dfs.visited_arcs == NULL);
}

int main() {
    normal_graph_1_dfs_test();
    normal_graph_2_dfs_test();
    singleton_graph_dfs_test();
    unconnected_graph_dfs_test();
    complete_graph_dfs_test();
}

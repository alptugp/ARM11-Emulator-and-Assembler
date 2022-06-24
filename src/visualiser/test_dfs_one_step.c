#include "dfs_one_step.h"
#include "utils.h"
#include <assert.h>

static void initialise_test(undirected_graph_t *undirected_graph, int num_nodes, int adj_matrix[num_nodes][num_nodes]) {
    undirected_graph->num_nodes = num_nodes;

    undirected_graph->node_arr = malloc(num_nodes * sizeof(undirected_node));
    for (int i = 0; i < num_nodes; i++) { 
        undirected_node new_node = {i};
        undirected_graph->node_arr[i] = new_node;
    }

    undirected_graph->current_node = undirected_graph->node_arr[0];

    undirected_graph->visited = malloc(sizeof(bool) * num_nodes);
    for (int i = 0; i < num_nodes; i++) {
        undirected_graph->visited[i] = false;
    }

    undirected_graph->visited_arcs = NULL;
    undirected_graph->num_visited_arcs = 0;
    undirected_graph->parent_arr = malloc(sizeof(undirected_node) * num_nodes);
    for(int i = 0; i < num_nodes; i++) {
        undirected_graph->parent_arr[i] = (undirected_node) {INITIAL_PARENT};
    }
    undirected_graph->start_node = (undirected_node) {0};

    for (int row = 0; row < num_nodes; row++) {
        for (int col = 0; col < num_nodes; col++) {
            adj_matrix[row][col] = 0;
        }
    }
}

static void copy_adj_matrix(undirected_graph_t *undirected_graph, int num_nodes, int adj_matrix[num_nodes][num_nodes]) {
    assert(undirected_graph->adj_matrix = malloc(sizeof(int *) * num_nodes));
    for (int row = 0; row < num_nodes; row++) {
        assert(undirected_graph->adj_matrix[row] = malloc(sizeof(int) * num_nodes));
        for (int col = 0; col < num_nodes; col++) {
            undirected_graph->adj_matrix[row][col] = adj_matrix[row][col];
        }
    }    
}

static void test_visited(int num_nodes, undirected_graph_t graph_after_dfs) {
    for (int i = 0; i < num_nodes; i++) {
        if (graph_after_dfs.parent_arr[i].index != INITIAL_PARENT) {
            if(!graph_after_dfs.visited[i]) {
                printf("Failed at %d\n", i);
                assert(0);
            }
        }
    }
}

void normal_graph_1_dfs_test() {
    undirected_graph_t *undirected_graph = malloc(sizeof(undirected_graph_t));
    int num_nodes = 5;

    int adj_matrix[num_nodes][num_nodes];

    initialise_test(undirected_graph, num_nodes, adj_matrix);

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

    while(!dfs_one_step(undirected_graph_union)) {}
    /*
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    dfs_one_step(undirected_graph_union);
    */

    assert(undirected_graph_union->undirected_graph.num_nodes == num_nodes);

    test_visited(num_nodes, undirected_graph_union->undirected_graph);

    undirected_arc *curr = undirected_graph_union->undirected_graph.visited_arcs;
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

    printf("Normal graph 1 - OK\n");
}

void unconnected_graph_dfs_test() {
    undirected_graph_t *undirected_graph = malloc(sizeof(undirected_graph_t));
    int num_nodes = 6;

    int adj_matrix[num_nodes][num_nodes];

    initialise_test(undirected_graph, num_nodes, adj_matrix);

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

    while(!dfs_one_step(undirected_graph_union)) {}


    undirected_graph_t graph_after_dfs = undirected_graph_union->undirected_graph;

    // assert(graph_after_dfs.current_node.index == current_node_index_after_dfs);
    assert(graph_after_dfs.num_nodes == num_nodes);

    test_visited(num_nodes, undirected_graph_union->undirected_graph);

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

    printf("Unconnected graph - OK\n");
}

void complete_graph_dfs_test() {
     undirected_graph_t *undirected_graph = malloc(sizeof(undirected_graph_t));
    int num_nodes = 4;

    int adj_matrix[num_nodes][num_nodes];

    initialise_test(undirected_graph, num_nodes, adj_matrix);

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

    while(!dfs_one_step(undirected_graph_union)) {}

    undirected_graph_t graph_after_dfs = undirected_graph_union->undirected_graph;

    // assert(graph_after_dfs.current_node.index == current_node_index_after_dfs);
    assert(graph_after_dfs.num_nodes == num_nodes);

    test_visited(num_nodes, undirected_graph_union->undirected_graph);

    undirected_arc *curr = graph_after_dfs.visited_arcs; 
    assert(curr->source.index == 0);
    assert(curr->target.index == 1);
    curr = curr->next_in_list;
    assert(curr->source.index == 1);
    assert(curr->target.index == 2);
    curr = curr->next_in_list;
    assert(curr->source.index == 2);
    assert(curr->target.index == 3);

    printf("Complete graph - OK\n");
}

void normal_graph_2_dfs_test() {
    undirected_graph_t *undirected_graph = malloc(sizeof(undirected_graph_t));
    int num_nodes = 8;

    int adj_matrix[num_nodes][num_nodes];

    initialise_test(undirected_graph, num_nodes, adj_matrix);

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

    while(!dfs_one_step(undirected_graph_union)) {}

    undirected_graph_t graph_after_dfs = undirected_graph_union->undirected_graph;

    // assert(graph_after_dfs.current_node.index == current_node_index_after_dfs);
    assert(graph_after_dfs.num_nodes == num_nodes);

    test_visited(num_nodes, undirected_graph_union->undirected_graph);

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

    printf("Normal graph 2 - OK\n");
}

void singleton_graph_dfs_test() {
    undirected_graph_t *undirected_graph = malloc(sizeof(undirected_graph_t));
    int num_nodes = 1;

    int adj_matrix[num_nodes][num_nodes];

    initialise_test(undirected_graph, num_nodes, adj_matrix);

    copy_adj_matrix(undirected_graph, num_nodes, adj_matrix);

    graph_union_t *undirected_graph_union = malloc(sizeof(graph_union_t));
    undirected_graph_union->undirected_graph = *undirected_graph;

    while(!dfs_one_step(undirected_graph_union)) {}

    undirected_graph_t graph_after_dfs = undirected_graph_union->undirected_graph;

    // assert(graph_after_dfs.current_node.index == current_node_index_after_dfs);
    assert(graph_after_dfs.num_nodes == num_nodes);

    test_visited(num_nodes, undirected_graph_union->undirected_graph);
    
    assert(graph_after_dfs.visited_arcs == NULL);

    printf("Singleton graph - OK\n");
}

int main() {
    normal_graph_1_dfs_test();
    normal_graph_2_dfs_test();
    singleton_graph_dfs_test();
    unconnected_graph_dfs_test();
    complete_graph_dfs_test();
    printf("ALL TESTS PASS.\n");
}

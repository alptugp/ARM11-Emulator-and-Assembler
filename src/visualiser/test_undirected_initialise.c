#include "undirected_graph.h"
#include <assert.h>

static void test_normal1() {
    // undirected_graph_t undirected_graph = undirected_initialise_helper(true, "test_in_normal1.txt");
    undirected_graph_t undirected_graph = undirected_initialise();
    assert(undirected_graph.num_nodes == 5);
    assert(undirected_graph.current_node.index == 0);
    assert(undirected_graph.visited_arcs == NULL);
    assert(undirected_graph.num_visited_arcs == 0);
    assert(undirected_graph.adj_matrix[0][1] == 1);
    assert(undirected_graph.adj_matrix[1][0] == 1);
    assert(undirected_graph.adj_matrix[1][4] == 1);
    assert(undirected_graph.adj_matrix[4][1] == 1);
    assert(undirected_graph.adj_matrix[1][3] == 1);
    assert(undirected_graph.adj_matrix[3][1] == 1);
    assert(undirected_graph.adj_matrix[3][4] == 1);
    assert(undirected_graph.adj_matrix[4][3] == 1);
    assert(undirected_graph.adj_matrix[0][4] == 1);
    assert(undirected_graph.adj_matrix[4][0] == 1);
    assert(undirected_graph.adj_matrix[1][2] == 1);
    assert(undirected_graph.adj_matrix[2][1] == 1);
    assert(undirected_graph.adj_matrix[2][3] == 1);
    assert(undirected_graph.adj_matrix[3][2] == 1);
    assert(undirected_graph.adj_matrix[0][2] == 0);
    assert(undirected_graph.adj_matrix[1][1] == 0);
    assert(undirected_graph.adj_matrix[2][4] == 0);
    assert(undirected_graph.adj_matrix[3][0] == 0);
    assert(undirected_graph.adj_matrix[4][2] == 0);
    free_undirected_graph(&undirected_graph);
    printf("NORMAL 1 - OK\n");
}

static void test_normal2() {
    undirected_graph_t undirected_graph = undirected_initialise_helper(true, "test_in_normal2.txt");
    assert(undirected_graph.num_nodes == 8);
    assert(undirected_graph.current_node.index == 3);
    assert(undirected_graph.visited_arcs == NULL);
    assert(undirected_graph.num_visited_arcs == 0);
    assert(undirected_graph.adj_matrix[0][1] == 1);
	assert(undirected_graph.adj_matrix[1][0]==1);
	assert(undirected_graph.adj_matrix[1][2]==1);
	assert(undirected_graph.adj_matrix[2][1]==1);
	assert(undirected_graph.adj_matrix[1][3]==1);
    assert(undirected_graph.adj_matrix[3][1]==1);
	assert(undirected_graph.adj_matrix[3][4]==1);
	assert(undirected_graph.adj_matrix[4][3]==1);
	assert(undirected_graph.adj_matrix[3][5]==1);
	assert(undirected_graph.adj_matrix[5][3]==1);
	assert(undirected_graph.adj_matrix[5][6]==1);
	assert(undirected_graph.adj_matrix[6][5]==1);
	assert(undirected_graph.adj_matrix[6][7]==1);
	assert(undirected_graph.adj_matrix[7][6]==1);
	assert(undirected_graph.adj_matrix[0][7]==1);
	assert(undirected_graph.adj_matrix[7][0]==1);
	assert(undirected_graph.adj_matrix[3][7]==1);
	assert(undirected_graph.adj_matrix[7][3]==1);
    free_undirected_graph(&undirected_graph);
    printf("NORMAL 2 - OK\n");
}

static void test_complete() {
    undirected_graph_t undirected_graph = undirected_initialise_helper(true, "test_in_complete.txt");
    assert(undirected_graph.num_nodes == 4);
    assert(undirected_graph.current_node.index == 2);
    assert(undirected_graph.visited_arcs == NULL);
    assert(undirected_graph.num_visited_arcs == 0);
	assert(undirected_graph.adj_matrix[0][1]==1);
	assert(undirected_graph.adj_matrix[1][0]==1);
	assert(undirected_graph.adj_matrix[0][2]==1);
	assert(undirected_graph.adj_matrix[2][0]==1);
	assert(undirected_graph.adj_matrix[0][3]==1);
	assert(undirected_graph.adj_matrix[3][0]==1);
	assert(undirected_graph.adj_matrix[2][3]==1);
	assert(undirected_graph.adj_matrix[3][2]==1);
	assert(undirected_graph.adj_matrix[1][3]==1);
	assert(undirected_graph.adj_matrix[3][1]==1);
	assert(undirected_graph.adj_matrix[1][2]==1);
	assert(undirected_graph.adj_matrix[2][1]==1);
    free_undirected_graph(&undirected_graph);
    printf("COMPLETE - OK\n");
}

static void test_unconnected() {
    undirected_graph_t undirected_graph = undirected_initialise_helper(true, "test_in_unconnected.txt");
    assert(undirected_graph.num_nodes == 6);
    assert(undirected_graph.current_node.index == 5);
    assert(undirected_graph.visited_arcs == NULL);
    assert(undirected_graph.num_visited_arcs == 0);
	assert(undirected_graph.adj_matrix[0][1]==1);
	assert(undirected_graph.adj_matrix[1][0]==1);
	assert(undirected_graph.adj_matrix[0][3]==1);
	assert(undirected_graph.adj_matrix[3][0]==1);
	assert(undirected_graph.adj_matrix[1][3]==1);
	assert(undirected_graph.adj_matrix[3][1]==1);
	assert(undirected_graph.adj_matrix[1][2]==1);
	assert(undirected_graph.adj_matrix[2][1]==1);
	assert(undirected_graph.adj_matrix[3][4]==1);
	assert(undirected_graph.adj_matrix[4][3]==1);
    assert(undirected_graph.adj_matrix[0][0]==0);
    assert(undirected_graph.adj_matrix[0][5]==0);
    assert(undirected_graph.adj_matrix[1][4]==0);
    assert(undirected_graph.adj_matrix[2][4]==0);
    assert(undirected_graph.adj_matrix[3][2]==0);
    assert(undirected_graph.adj_matrix[4][4]==0);
    assert(undirected_graph.adj_matrix[5][1]==0);
    printf("UNCONNECTED - OK\n");
}


int main() {
    test_normal1();
    test_normal2();
    test_complete();
    test_unconnected();
    printf("ALL TESTS PASS.\n");
}
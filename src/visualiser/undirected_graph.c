#include "undirected_graph.h"
#include "utils.h" 
#include <string.h>
#include <assert.h>
#include <stdio.h>

undirected_graph_t undirected_initialise_helper(bool open_from_file, char filename[]) {
    FILE *test_file;
    if(open_from_file) {
        test_file = fopen(filename, "r");
    }

    undirected_graph_t undirected_graph;

    printf("Enter the number of nodes of the undirected_graph.\n");
    char *num_nodes_str;
    if(open_from_file) {
        str_file_in(&num_nodes_str, test_file);
    }
    else {
        str_stdin(&num_nodes_str);
    }
    int num_nodes = atoi(num_nodes_str);
    undirected_graph.num_nodes = num_nodes;
    free(num_nodes_str);

    undirected_graph.node_arr = malloc(sizeof(undirected_node) * num_nodes);
    for (int i = 0; i < num_nodes; i++) {
        undirected_graph.node_arr[i] = (undirected_node) {i};
    }

    undirected_graph.adj_matrix = malloc(sizeof(int *) * num_nodes);
    for (int row = 0; row < num_nodes; row++) {
        undirected_graph.adj_matrix[row] = calloc(num_nodes, sizeof(int));
        for (int col = 0; col < num_nodes; col++) {
            if(col == row) {
                undirected_graph.adj_matrix[row][col] = 0;
            }
            else if (col < row) {
                undirected_graph.adj_matrix[row][col] = undirected_graph.adj_matrix[col][row];
            }
            else {
                bool inputted_successfully = false;
                while(!inputted_successfully) {
                    printf("Is there an arc between the nodes with indices %d and %d? (Y/N)\n", row, col);
                    char *answer;
                    if(open_from_file) {
                        str_file_in(&answer, test_file);
                    }
                    else {
                        str_stdin(&answer);
                    }
                    if (strcmp(answer, "Y") == 0) {
                        undirected_graph.adj_matrix[row][col] = 1;
                        inputted_successfully = true;
                    } else if (strcmp(answer, "N") == 0) {
                        undirected_graph.adj_matrix[row][col] = 0;
                        inputted_successfully = true;
                    } else {
                        printf("Please enter Y/N.\n");
                    }
                    free(answer);
                }
            }
        }
    }

    undirected_graph.visited = malloc(sizeof(bool) * num_nodes);
    for (int i = 0; i < num_nodes; i++) {
        undirected_graph.visited[i] = false;
    }

    undirected_graph.parent_arr = malloc(sizeof(bool) * num_nodes);
    for(int i = 0; i < num_nodes; i++) {
        undirected_graph.parent_arr[i] = (undirected_node) {INITIAL_PARENT};
    }

    undirected_graph.visited_arcs = NULL;
    undirected_graph.num_visited_arcs = 0;
    
    // Asks user the index of the current node nd sets it
    printf("Enter the index of the node which you want to be the current node.\n");
    char *current_node_index_str;
    if(open_from_file) {
        str_file_in(&current_node_index_str, test_file);
    }
    else {
        str_stdin(&current_node_index_str);
    }
    int current_node_index = atoi(current_node_index_str);
    free(current_node_index_str);
    undirected_node start_node = {current_node_index};
    undirected_graph.current_node = start_node;
    undirected_graph.start_node = start_node;

    if(open_from_file) {
        fclose(test_file);
    }

    return undirected_graph;
}

void free_undirected_graph(undirected_graph_t *undirected_graph) {
    for(int i = 0; i < undirected_graph->num_nodes; i++) {
        free(undirected_graph->adj_matrix[i]);
    }
    //free(undirected_graph->adj_matrix);
    //free(undirected_graph->visited);
    //free(undirected_graph->node_arr);
    //free(undirected_graph->parent_arr);  
}
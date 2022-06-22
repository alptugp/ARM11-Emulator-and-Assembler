#include "undirected_graph.h"
#include "utils.h"
#include <assert.h>

adj_list_node *create_adj_list_node(int node) {
    adj_list_node *new_node = malloc(sizeof(adj_list_node));
    new_node->node = node;
    new_node->next = NULL;
    return new_node;
}

undirected_graph *create_undirected_graph(int size) {
    // Allocate memory for the graph
    undirected_graph *new_graph = malloc(sizeof(undirected_graph));

    // Initialise the graph
    new_graph->size = size;
    new_graph->adj_list = malloc(sizeof(adj_list) * size);

    // Make all adjacency lists empty
    for (int i = 0; i < size; i++) {
        new_graph->adj_list[i].head = NULL;
        new_graph->adj_list[i].size = 0;
    }
    return new_graph;
}

void add_arc(undirected_graph *graph, int source, int target) {
    assert(source >= 0);
    assert(source < graph->size);
    assert(target >= 0);
    assert(target < graph->size);

    // Add the target node to the source node's adjacency list
    adj_list_node *new_node = create_adj_list_node(target);

    // If the source node's adjacency list is empty, set the head to the new node
    if (graph->adj_list[source].head == NULL) {
        graph->adj_list[source].head = new_node;
    } 
    else {
        // Otherwise, add the new node to the end of the list
        adj_list_node *current_node = graph->adj_list[source].head;
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = new_node;
    }

    // Add the source node to the target node's adjacency list (since graph is undirected)
    new_node = create_adj_list_node(source);

    // If the target node's adjacency list is empty, set the head to the new node
    if (graph->adj_list[target].head == NULL) {
        graph->adj_list[target].head = new_node;
    } 
    else 
    {
        // Otherwise, add the new node to the end of the list
        adj_list_node *current_node = graph->adj_list[target].head;
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = new_node;
    }

    // Increment the size of the adjacency list
    graph->adj_list[source].size++;
    graph->adj_list[target].size++;

}

int get_num_arcs(undirected_graph *graph) {
    int num_arcs = 0;
    for (int i = 0; i < graph->size; i++) {
        num_arcs += graph->adj_list[i].size;
    }
    // Divide by 2 to get the number of arcs since the graph is undirected so we count each arc twice in for loop
    return num_arcs / 2;
}

int get_num_nodes(undirected_graph *graph) {
    return graph->size;
}

bool has_arc(undirected_graph *graph, int source, int target) {
    assert(source >= 0);
    assert(source < graph->size);
    assert(target >= 0);
    
    bool source_has_target = false;
    bool target_has_source = false;

    // Check if the target node is in the source node's adjacency list
    adj_list_node *current_node = graph->adj_list[source].head;
    while (current_node != NULL) {
        if (current_node->node == target) {
            target_has_source = true;
            break;
        }
        current_node = current_node->next;
    }

    // Check if the source node is in the target node's adjacency list
    current_node = graph->adj_list[target].head;
    while (current_node != NULL) {
        if (current_node->node == source) {
            source_has_target = true;
            break;
        }
        current_node = current_node->next;
    }
    return source_has_target && target_has_source;
}

void free_undirected_graph(undirected_graph *graph) {
    for (int i = 0; i < graph->size; i++) {
        adj_list_node *current_node = graph->adj_list[i].head;
        while (current_node != NULL) {
            adj_list_node *next_node = current_node->next;
            free(current_node);
            current_node = next_node;
        }
    }
    free(graph->adj_list);
    free(graph);
}

int get_degree(undirected_graph *graph, int vertex) {
    assert(vertex >= 0);
    assert(vertex < graph->size);
    return graph->adj_list[vertex].size;
}

void print_undirected_graph_adj_list(undirected_graph *graph) {
    for (int i = 0; i < graph->size; i++) {
        adj_list_node *current_node = graph->adj_list[i].head;
        printf("%d: ", i);
        while (current_node != NULL) {
            printf("-> %d ", current_node->node);
            current_node = current_node->next;
        }
        printf("\n");
    }
}


undirected_graph_t initialise_undirected(void) {
    undirected_graph_t *graph = malloc(sizeof(undirected_graph_t));

    printf("Enter the number of nodes of the graph.\n");
    int num_nodes;
    fgets(num_nodes, sizeof(num_nodes), stdin);
    strip_trailing_newline(num_nodes);
    graph->num_nodes = num_nodes;

    //Sets the array for all the nodes
    undirected_node *node_arr[num_nodes];

    for (int i = 0; i < num_nodes; i++) {
        node_arr[i] = malloc(sizeof(undirected_node));
        node_arr[i]->index = i;
    }

    graph->node_arr = node_arr;

    // Sets the adjacency matrix for the graph
    int adj_matrix[num_nodes][num_nodes];

    for (int row = 0; row < num_nodes; row++) {
        for (int col = 0; col < num_nodes; col++) {
            char *answer;
            printf("Is there an arc between the nodes with indices %d and %d? y/n\n", row, col);
            fgets(answer, sizeof(char), stdin);
            strip_trailing_newline(answer);
            if (strcmp(answer, "y") == 0) {
                adj_matrix[row][col] = 1;
            } else if (strcmp(answer, "n") == 0) {
                adj_matrix[row][col] = 0;
            } else {
                printf("Please enter y/n.\n");
            }
        }
    }

    graph->adj_matrix = adj_matrix;

    // Sets the array for visited nodes
    bool *visited[num_nodes];

    for (int i = 0; i < num_nodes; i++) {
        visited[i] = false;
    }

    graph->visited = visited;

    // Sets the linked list for visited arcs
    undirected_arc *visited_arcs = NULL;
    graph->visited_arcs = visited_arcs;
    
    //num_visited_arcs is set to zero as we are initialising the graph.
    int num_visited_arcs = 0;
    

    // Asks user the index of the current node nd sets it
    int *current_node_index;
    printf("Enter the index of the node which you want to be the current node.\n");
    fgets(current_node_index, sizeof(int), stdin);
    strip_trailing_newline(current_node_index);   
    undirected_node *current_node = malloc(sizeof(undirected_node));
    current_node->index = current_node_index;

}


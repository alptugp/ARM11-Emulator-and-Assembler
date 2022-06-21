#include "undirected_graph.h"
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

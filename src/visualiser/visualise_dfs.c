#include "undirected_graph.h"
#include "visualise_dfs.h"
#include <string.h>
#include <stdbool.h>
#include <time.h>

static void print_node(undirected_node node) {
    printf("| -- |\n");
    printf("| %d |\n", node.index);
    printf("| -- |\n");
}

// Print the list of visited nodes, in order of visiting.
static void print_traversal(undirected_graph_t graph) {
    printf("Traversal of nodes so far, in order: ");
    undirected_arc *curr = graph.visited_arcs;
    while(curr) {
        printf("%d ", curr->source.index);
        curr = curr->next_in_list;
    }
    printf("\n");
}

static void draw_with_colour(undirected_graph_t graph, undirected_arc *arcs_to_colour, int num_arcs_to_colour) {
    
}

// Draw the graph and then animate the traversal, by colouring each visited arc in turn.
static void animate_traversal(undirected_graph_t graph, long animation_delay) {
    undirected_arc arcs_to_colour[graph.num_visited_arcs];
    int arcs_to_colour_index = 0;
    draw_with_colour(graph, arcs_to_colour, arcs_to_colour_index);
    undirected_arc *curr = graph.visited_arcs;
    while(curr) {
        system("clear");
        arcs_to_colour[arcs_to_colour_index] = *curr;
        draw_with_colour(graph, arcs_to_colour, arcs_to_colour_index);
        delay(animation_delay);
        arcs_to_colour_index++;
    }
}

bool dfs_visualise(graph_union_t graph_union) {
    undirected_graph_t graph = graph_union.undirected_graph;
    bool exit = false;
    while(!exit) {
        printf("SELECT AN OPTION TO ANIMATE.\n");
        printf("Options are: 'PRINT', 'ANIMATE', 'NEXT', and 'EXIT'\n");
        printf("'PRINT' prints a comma-separated ordered list of visited nodes.\n");
        printf("'ANIMATE' displays the graph in text-graphical form, and then colours each visited arc in turn.\n");
        printf("'NEXT' proceeds to the next step of the algorithm, or terminates if we are finished.\n");
        printf("'EXIT' quits immediately.\n");
        char user_choice[CHOICE_MAX_LENGTH];
        fgets(user_choice, sizeof(user_choice), stdin);
        strip_trailing_newline(user_choice);
        if(strcmp(user_choice, "PRINT") == 0) {
            print_traversal(graph);
        }
        else if(strcmp(user_choice, "ANIMATE") == 0) {
            char animation_delay[CHOICE_MAX_LENGTH];
            fgets(animation_delay, sizeof(animation_delay), stdin);
            strip_trailing_newline(animation_delay);
            char *dummy_ptr;
            animate_traversal(graph, strtol(animation_delay, &dummy_ptr, 10));
        }
        else if(strcmp(user_choice, "NEXT") == 0) {
            printf("Proceeding to next step of algorithm.\n");
            exit = true;
        }
        else if(strcmp(user_choice, "EXIT") == 0) {
            return true;
        }
        else {
            printf("Not a valid option!\n");
        }
    }
    return false;
}

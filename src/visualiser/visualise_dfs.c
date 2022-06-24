#include "undirected_graph.h"
#include "visualise_dfs.h"
#include <string.h>
#include <stdbool.h>
#include <time.h>

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

static void write_node_to_grid(grid_t *grid, int node_index, int row_index, int col_index) {
    assert(row_index >= 0 && row_index + NODE_CENTRE_TO_RIGHT < grid->height);
    assert(col_index >= 0 && col_index + NODE_CENTRE_TO_BTM < grid->width);
    /*
    strcpy(&grid->chars[row_index - 1][col_index - 1], "| ¯ |");
    char *second_line;
    sprintf(second_line, "| %d |\n", node_index);
    strcpy(&grid->chars[row_index][col_index - 1], second_line);
    strcpy(&grid->chars[row_index + 1][col_index - 1], "| _ |");
    */
   char *buf;
   sprintf(buf, "%d", node_index);
   strcpy(grid->chars[row_index][col_index], buf);
}

static void initialise_nodes(undirected_graph_t graph, grid_t *grid, location_t *node_locations) {
    bool occupied_squares[grid->height][grid->width];
    for(int row_index = 0; row_index < grid->height; row_index++) {
        for(int col_index = 0; col_index < grid->width; col_index++) {
            occupied_squares[row_index][col_index] = false;
        }
    }

    for(int node_index = 0; node_index < graph.num_nodes; node_index++) {
        int row_index, col_index;
        while(true) {
            row_index = rand() % (1 + grid->height - NODE_CENTRE_TO_BTM);
            col_index = rand() % (1 + grid->width - NODE_CENTRE_TO_RIGHT);
            if(!occupied_squares[row_index][col_index]) {
                break;
            }
        }

        location_t new_loc = {row_index, col_index};
        node_locations[node_index] = new_loc;
        write_node_to_grid(&grid, node_index, row_index, col_index);

        // Mark all squares MIN_NODE_GAP + 2 * a node width and MIN_NODE_GAP + 2 * a node height from (row_index, col_index),
        // so that two nodes will never touch each other, even on the boundary
        for(int row_offset = -2 * NODE_CENTRE_TO_BTM - MIN_NODE_GAP; row_index < 2 * NODE_CENTRE_TO_BTM + MIN_NODE_GAP; row_index++) {
            for(int col_offset = -2 * NODE_CENTRE_TO_RIGHT - MIN_NODE_GAP; col_index < 2 * NODE_CENTRE_TO_RIGHT + MIN_NODE_GAP; col_index++) {
                occupied_squares[row_index + row_offset][col_index + col_offset] = true;
            }
        }
        
    }
}

// Calculate arc segments to draw from given source location to given target location,
// returning the number of arc segments to draw
static int calc_arc_segs(location_t source_location, location_t target_location, arc_segment_t *arc_segments) {
    if(source_location.col == target_location.col || source_location.row == target_location.row) {
        assert(!((source_location.row != target_location.row) 
                && (source_location.col != target_location.col)));
        arc_segments[0] = (arc_segment_t) {source_location, target_location};
        return 1;
    }
    bool equalise_rows_first = rand() % 2;
    location_t midpt = equalise_rows_first ? (location_t) {target_location.row, source_location.col} : (location_t) {target_location.col, source_location.row};
    arc_segments[0] = (arc_segment_t) {source_location, midpt};
    return 1 + calc_arc_segs(midpt, target_location, arc_segments + 1);
}

static int calc_all_arc_segs(undirected_graph_t graph, location_t *node_locations, arc_segment_t *arc_segments) {
    int num_arc_segments = 0;
    for(int source_index = 0; source_index < graph.num_nodes; source_index++) {
        for(int target_index = source_index; target_index < graph.num_nodes; target_index++) {
            if(!graph.adj_matrix[source_index][target_index]) {
                continue;
            }
            arc_segment_t new_arc_segments[MAX_SEGMENTS_PER_ARC];
            int num_new_arc_segments = calc_arc_segs(node_locations[source_index], node_locations[target_index], new_arc_segments);
            memcpy(arc_segments + num_arc_segments, new_arc_segments, num_new_arc_segments);
            num_arc_segments += num_new_arc_segments;
        }
    }
}

static void draw_arcs(undirected_graph_t graph, grid_t *grid, arc_segment_t *arc_segments, int num_arc_segments, undirected_arc *arcs_to_colour, int num_arcs_to_colour) {
    //  TODO add colours
    for(int i = 0; i < num_arc_segments; i++) {
        arc_segment_t arc_segment = arc_segments[i];
        if(arc_segment.start_pt.row == arc_segment.end_pt.row) {
            int row_index = arc_segment.start_pt.row;
            for(int col_index = arc_segment.start_pt.col + 1; col_index < arc_segment.end_pt.col; col_index++) {
                grid->chars[row_index][col_index] = HORIZONTAL_ARC_CHAR;
            }
        }
        else {
            assert(arc_segment.start_pt.col = arc_segment.end_pt.col);
            int col_index = arc_segment.start_pt.col;
            for(int row_index = arc_segment.start_pt.row + 1; row_index < arc_segment.end_pt.row; row_index++) {
                grid->chars[row_index][col_index] = VERTICAL_ARC_CHAR;
            }
        }
    }
}

static void print_grid(grid_t grid) {
    for(int row = 0; row < grid.height; row++) {
        printf("%s\n", grid.chars[row]);
    }
}

// Draw the graph and then animate the traversal, by colouring each visited arc in turn.
static void animate_traversal(undirected_graph_t graph, long animation_delay) {
    // Initialise grid
    char **chars;
    grid_t grid = {chars, graph.num_nodes * NODE_WIDTH, graph.num_nodes * NODE_HEIGHT};
    grid.chars = malloc(sizeof(char *) * grid.height);
    for(int row_index = 0; row_index < grid.height; row_index++) {
        grid.chars[row_index] = malloc(sizeof(char) * grid.width);
        for(int col_index = 0; col_index < grid.width; col_index++) {
            grid.chars[row_index][col_index] = EMPTY;
        }
    }

    // Put nodes on grid and calculate how to draw arcs between them
    location_t node_locations[graph.num_nodes]; // array mapping node indices to their location on grid (as given by centre)
    arc_segment_t arc_segments[graph.num_nodes * graph.num_nodes * MAX_SEGMENTS_PER_ARC];
    initialise_nodes(graph, &grid, node_locations);
    int num_arc_segments = calc_all_arc_segs(graph, node_locations, arc_segments);

    // Draw initial graph (no colouring)
    // Allows user to request redraws in case graph is unclear
    undirected_arc arcs_to_colour[graph.num_visited_arcs];
    int arcs_to_colour_index = 0;
    char redraw_input[USER_IN_MAX_LENGTH] = "Y";
    do {
        draw_arcs(graph, &grid, arc_segments, num_arc_segments, arcs_to_colour, arcs_to_colour_index);
        print_grid(grid);
        printf("Redraw graph with nodes, arcs in different position? (Y or N) ");
        fgets(redraw_input, sizeof(redraw_input), stdin);
        strip_trailing_newline(redraw_input);
    } while(strcmp(redraw_input, "Y") == 0);


    undirected_arc *curr = graph.visited_arcs;
    while(curr) {
        system("clear");
        arcs_to_colour[arcs_to_colour_index] = *curr;
        draw_arcs(graph, &grid, arc_segments, num_arc_segments, arcs_to_colour, arcs_to_colour_index);
        print_grid(grid);
        delay(animation_delay);
        arcs_to_colour_index++;
    }

    for(int row_index = 0; row_index < grid.height; row_index++) {
        free(grid.chars[row_index]);
    }
    free(grid.chars);
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
        char user_choice[USER_IN_MAX_LENGTH];
        fgets(user_choice, sizeof(user_choice), stdin);
        strip_trailing_newline(user_choice);
        if(strcmp(user_choice, "PRINT") == 0) {
            print_traversal(graph);
        }
        else if(strcmp(user_choice, "ANIMATE") == 0) {
            char animation_delay[USER_IN_MAX_LENGTH];
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

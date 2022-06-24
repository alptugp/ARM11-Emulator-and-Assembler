#ifndef DFS_VISUALISE
#define DFS_VISUALISE

#include "utils.h"

#define NODE_WIDTH 1
#define NODE_HEIGHT 1
#define EMPTY ' '
#define NODE_CENTRE_TO_BTM 0
#define NODE_CENTRE_TO_RIGHT 0
#define MAX_SEGMENTS_PER_ARC 2
#define MIN_NODE_GAP 2
#define MILLIS_TO_SECONDS 1000
#define COLOUR "\x1b[32m"
#define COLOUR_RESET "\x1b[0m"
#define HORIZONTAL_ARC_CHAR '-'
#define VERTICAL_ARC_CHAR '|'
#define HORIZONTAL_AND_VERTICAL_ARC_CHAR '+'

typedef struct location {
    int row;
    int col;
} location_t;

typedef struct grid {
    char **chars;
    int height;
    int width;
} grid_t;

typedef struct arc_segment {
    location_t start_pt;
    location_t end_pt;
    int arc_source_index;
    int arc_target_index;
} arc_segment_t;

bool dfs_visualise(graph_union_t graph_union);

#endif

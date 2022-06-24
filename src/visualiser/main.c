#include "utils.h"
#include "dfs_one_step.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void initialise_algorithm(initialise_t *initialise, one_step_t *one_step, visualise_t *visualise) {
    printf("Enter an algorithm you wish to explore.\n");
    printf("The currently supported algorithms are: '%s'\n", "DFS");
    char *algo_name;
    str_stdin(algo_name);
    if(strcmp(algo_name, "DFS") == 0) {
        initialise = &undirected_initialise;
        one_step = &dfs_one_step;
    }
    else {
        printf("Not a valid algorithm name.\n");
        initialise_algorithm(initialise, one_step, visualise);
    }
    free(algo_name);
}

int main() {
    srand(time(NULL));

    initialise_t initialise;
    one_step_t one_step;
    visualise_t visualise;

    initialise_algorithm(&initialise, &one_step, &visualise);

    graph_union_t graph_union = (*initialise)();

    int terminate = 0;
    while (!terminate) {
        terminate = (*one_step)(&graph_union);
        terminate |= (*visualise)(graph_union);
    }
    
    printf("Exiting.\n");

    return 0;
}

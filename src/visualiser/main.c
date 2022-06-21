#include "utils.h"
#include <string.h>
#include <stdio.h>

void strip_trailing_newline(char *str) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == '\n') {
            str[i] = '\0';
            return str;
        }
    }
    return str;
}

int main() {
    initialise_t initialise;
    one_step_t one_step;
    visualise_t visualise;

    char buffer[ALGO_NAME_MAX_LENGTH];
    fgets(buffer, sizeof(buffer), stdin);
    strip_trailing_newline(buffer);
    // TODO USE STRCMP TO SELECT ALGORITHM AND INITIALISE 3X FUNC PTRS

    graph_union_t graph_union = (*initialise)();

    int terminate = 0;
    while (!terminate) {
        terminate = (*one_step)(&graph_union);
        (*visualise)(graph_union);
    }
    
    return 0;
}

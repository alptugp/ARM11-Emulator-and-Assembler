#include "utils.h"

void strip_trailing_newline(char *str) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == '\n') {
            str[i] = '\0';
            return;
        }
    }
    return;
}

void str_stdin(char **buffer_ptr) {
    *buffer_ptr = malloc(sizeof(char) * USER_IN_MAX_LENGTH);
    fgets(*buffer_ptr, USER_IN_MAX_LENGTH, stdin);
    strip_trailing_newline(*buffer_ptr);
}

void str_file_in(char **buffer_ptr, FILE *fp) {
    *buffer_ptr = malloc(sizeof(char) * USER_IN_MAX_LENGTH);
    assert(*buffer_ptr);
    fgets(*buffer_ptr, USER_IN_MAX_LENGTH, fp);
    strip_trailing_newline(*buffer_ptr);
}

graph_union_t undirected_initialise(void) {
    graph_union_t new_union;
    new_union.undirected_graph = undirected_initialise_helper(true, "test_in_normal1.txt");
    return new_union;
}

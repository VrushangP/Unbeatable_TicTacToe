#include "ttt.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv) {
    if (argc < 2) {
        exit(1);
    }
    init_boards();
    init_board(START_BOARD);
    join_graph(START_BOARD);
    compute_score();
    int i;
    for ( i = argc - 1; i > 0; i--) {
        int hash = atoi(argv[argc - i]);
        print_node(htable[hash]);
    }
    return 0;
}
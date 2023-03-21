//
//  main.c
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main(int argc, char** argv) {
    GRAPH test = graph_init();
    for (int i = 1; i < 9; i++) {
        graph_addVertex(test, i, rand() % 20);
    }
    graph_addConnection(test, 1, 2);
    graph_addConnection(test, 1, 8);
    graph_addConnection(test, 1, 5);
    list_print(graph_getAdjacentVerticies(test, 1));
    graph_destroy(&test);
    return 0;
}


//graph_isConnected(test, 1, 8) ? printf("YES\n") : printf("No\n");

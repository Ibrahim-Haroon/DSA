//
//  main.c
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/14/23.
//
#include "graph.h"
#include <stdio.h>

int main(void) {
    GRAPH g = graph_init();
    for (int i = 1; i <= 8; i++)
        graph_addVertex(g, i);
    
    graph_addConnection(g, 1, 4, 5);
    graph_addConnection(g, 1, 6, 6);
    LIST res = graph_getAdjacentVerticies(g, 1);
    list_print(res);
    int weight = graph_getWeight(g, 1, 6);
    printf("%d\n", weight);
    graph_destroy(&g);
    return 0;
}



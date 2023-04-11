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
    for (int i = 1; i <= 4; i++) {
        graph_addVertex(g, i);
    }
    graph_addConnection(g, 1, 2, 3);
    graph_addConnection(g, 1, 4, 1);
    graph_addConnection(g, 2, 4, 5);
    graph_addConnection(g, 3, 2, 4);
    graph_addConnection(g, 4, 1, 2);

    int shortestPath = graph_shortestPath(g, 1, 3);
    printf("\nShortest path from 1 -> 3 is %d units\n", shortestPath); //-1

    shortestPath = graph_shortestPath(g, 2, 1);
    printf("\nShortest path from 2 -> 1 is %d units\n", shortestPath);  //5 + 2 = 7

    shortestPath = graph_shortestPath(g, 3, 1);
    printf("\nShortest path from 3 -> 1 is %d units\n", shortestPath); //4 + 5 + 2 = 11
    
    shortestPath = graph_shortestPath(g, 1, 4);
    printf("\nShortest path from 1 -> 4 is %d units\n", shortestPath);  //1 (direct path)
    
    shortestPath = graph_shortestPath(g, 3, 4);
    printf("\nShortest path from 3 -> 4 is %d units\n\n", shortestPath); //4 + 5 = 9
    
    graph_destroy(&g);
    return 0;
}



/*
 int main(void) {
 GRAPH g = graph_init();
 for (int i = 1; i <= 4; i++) {
 graph_addVertex(g, i);
 }
 graph_addConnection(g, 1, 2, 3);
 graph_addConnection(g, 1, 4, 1);
 graph_addConnection(g, 2, 4, 5);
 graph_addConnection(g, 3, 2, 4);
 graph_addConnection(g, 4, 1, 2);
 
 printf("1 = %d, %d\n", graph_getWeight(g, 1, 2), graph_getWeight(g, 1, 4));
 LIST res = graph_getAdjacentVerticies(g, 1);
 list_print(res);
 list_destroy(&res);
 
 printf("\n2 = %d\n", graph_getWeight(g, 2, 4));
 res = graph_getAdjacentVerticies(g, 2);
 list_print(res);
 list_destroy(&res);
 
 printf("\n3 = %d\n", graph_getWeight(g, 3, 2));
 res = graph_getAdjacentVerticies(g, 3);
 list_print(res);
 list_destroy(&res);
 
 printf("\n4 = %d\n", graph_getWeight(g, 4, 1));
 res = graph_getAdjacentVerticies(g, 4);
 list_print(res);
 list_destroy(&res);
 
 
 int shortestPath = graph_shortestPath(g, 1, 3);
 printf("\nShortest path from 1 -> 3 is %d units\n", shortestPath);
 
 shortestPath = graph_shortestPath(g, 2, 1);
 printf("\nShortest path from 2 -> 1 is %d units\n", shortestPath);
 
 shortestPath = graph_shortestPath(g, 3, 1);
 printf("\nShortest path from 3 -> 1 is %d units\n\n", shortestPath);
 
 graph_destroy(&g);
 return 0;
 }

 */

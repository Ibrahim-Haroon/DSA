//
//  graph.h
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#ifndef graph_h
#define graph_h

#include <stdbool.h>

typedef void* GRAPH;

GRAPH graph_init(void);
bool graph_isEmpty(GRAPH graph);
void graph_addVertex(GRAPH graph, int item, int weight); //set all to 1 if unweighted graph
void graph_addConnection(GRAPH graph, int from, int to);
bool graph_containsVertex(GRAPH graph, int item);
bool graph_isConnected(GRAPH graph, int from, int to);
void graph_removeConnection(GRAPH graph, int from, int to);
void graph_removeVertex(GRAPH graph, int item);
int* graph_getAdjacentVerticies(GRAPH graph, int from);
void graph_shortestPath(GRAPH graph, int from, int to);
void graph_dfs(GRAPH graph);
void graph_bfs(GRAPH graph);
void graph_destroy(GRAPH* graph);

#endif /* graph_h */

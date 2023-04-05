//
//  graph.c
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
/*
 !!!Graph is directed and weighted!!!
 assuming graph is sparse
 if graph is not sparse then using a adjagency_matrix to store vertex's is optimal
 */

#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct vertex {
    int item;
    int weight;
    struct vertex* edge;
    
}Vertex;

typedef struct digraph{
    int size;
    int capacity;
    Vertex** adjagency_list; //** because adjagency_list has to grow vertically and horizontally
}Graph;
static bool graph_isFull(GRAPH graph);                 //private
static void increase_adjagencyList_size(GRAPH graph); //private
static Vertex* createVertex(int item, int weight);               //private


GRAPH graph_init(void) {
    Graph* newGraph = (Graph*) malloc(sizeof(Graph));
    if (newGraph == NULL) {
        fprintf(stderr, "Failed to allocate space for graph\n");
        exit(EXIT_FAILURE);
    }
    newGraph ->size = 0;
    newGraph ->capacity = 1;
    newGraph ->adjagency_list = (Vertex**) calloc(sizeof(Vertex*), (newGraph ->capacity));
    if (newGraph ->adjagency_list == NULL) {
        fprintf(stderr, "Failed to allocate space for adjagency list\n");
        free(newGraph);
        exit(EXIT_FAILURE);
    }
    
    return newGraph;
}

bool graph_isFull(GRAPH graph) {
    Graph* weighted_graph = (Graph*)graph;
    if (weighted_graph ->size >= weighted_graph ->capacity) {
        return true;
    }
    return false;
}

#define LOAD_FACTOR (2)
void increase_adjagencyList_size(GRAPH graph) {     //update
    Graph* weighted_graph = (Graph*)graph;
    Vertex** larger_adjagencyList = (Vertex**) calloc(sizeof(Vertex*), (weighted_graph ->capacity * LOAD_FACTOR));
    for (int i = 0; i < weighted_graph ->size; i++) {
        larger_adjagencyList[i] = weighted_graph ->adjagency_list[i];
        Vertex* toInsert = createVertex(weighted_graph ->adjagency_list[i]->item, weighted_graph ->adjagency_list[i]->weight);
        larger_adjagencyList[i] = toInsert;
        Vertex* temp = weighted_graph ->adjagency_list[i]->edge;
        while (temp != NULL) {
            toInsert = createVertex(temp ->item, temp ->weight);
            toInsert ->edge = larger_adjagencyList[i] ->edge;
            larger_adjagencyList[i] ->edge = toInsert;
            temp = temp ->edge;
        }
    }
    free(weighted_graph ->adjagency_list);
    weighted_graph ->adjagency_list = larger_adjagencyList;
    weighted_graph ->capacity *= LOAD_FACTOR;
}

bool graph_isEmpty(GRAPH graph) {
    Graph* weighted_graph = (Graph*)graph;
    if (weighted_graph ->size <= 0) {
        return true;
    }
    return false;
}

static Vertex* createVertex(int item, int weight) {
    Vertex* newVertex = (Vertex*) malloc(sizeof(Vertex));
    if (newVertex == NULL) {
        fprintf(stderr, "Failed to allocate space for a new vector\n");
        exit(EXIT_FAILURE);
    }
    newVertex ->item = item;
    newVertex ->weight = weight;
    newVertex ->edge = NULL;
    return newVertex;
}

void graph_addVertex(GRAPH graph, int item) {
    if (graph_isFull(graph)) increase_adjagencyList_size(graph);
    Graph* weighted_graph = (Graph*)graph;
    Vertex* toInsert = createVertex(item, 0); //weight currently does not matter
    weighted_graph ->adjagency_list[weighted_graph ->size++] = toInsert;
    return;
}

void graph_addConnection(GRAPH graph, int from, int to, int weight) {
    Graph* weighted_graph = (Graph*)graph;
    if (graph_containsVertex(graph, from) &&
        graph_containsVertex(graph, to) &&
        !graph_isConnected(graph, from, to))
    {
        for (int i = 0; i < weighted_graph ->size; i++) {
            if (weighted_graph ->adjagency_list[i]->item == from) {
                Vertex* toInsert = createVertex(to, weight);
                toInsert ->edge = weighted_graph ->adjagency_list[i] ->edge;
                weighted_graph ->adjagency_list[i] ->edge = toInsert;
                return;
            }
        }
    }
    else printf("Invalid, one of the vertices do not exits\n");
    return;
}

bool graph_containsVertex(GRAPH graph, int item) {
    if (graph_isEmpty(graph)) return false;
    Graph* weighted_graph = (Graph*)graph;
    for (int i = 0; i < weighted_graph ->size; i++) {
        if (weighted_graph ->adjagency_list[i] == NULL) continue;
        if (weighted_graph ->adjagency_list[i]->item == item) {
            return true;
        }
    }
    return false;
}

bool graph_isConnected(GRAPH graph, int from, int to) {
    if (graph_isEmpty(graph)) return false;
    Graph* weighted_graph = (Graph*)graph;
    for (int i = 0; i < weighted_graph ->size; i++) {
        if (weighted_graph ->adjagency_list[i] == NULL) continue;
        if (weighted_graph ->adjagency_list[i]->item == from) {
            Vertex* temp = weighted_graph ->adjagency_list[i];
            while (temp != NULL) {
                if (temp ->item == to) {
                    return true;
                }
                temp = temp ->edge;
            }
        }
    }
    return false;
}

void graph_removeConnection(GRAPH graph, int from, int to) {
    if (graph_isEmpty(graph)) {
        printf("Invalid, EMPTY graph\n");
        return;
    }
    Graph* weighted_graph = (Graph*)graph;
    for (int i = 0; i < weighted_graph ->size; i++) {
        if (weighted_graph ->adjagency_list[i] == NULL) continue;
        if (weighted_graph ->adjagency_list[i]->item == from) {
            Vertex* fast = weighted_graph ->adjagency_list[i];
            Vertex* slow = fast;
            while (fast != NULL && fast ->item != to) {
                slow = fast;
                fast = fast ->edge;
            }
            if (fast == NULL) {
                printf("Invalid, connection from %d to %d never existed\n", from, to);
                return;
            }
            slow ->edge = fast ->edge;
            free(fast);
            fast = NULL;
        }
    }
    return;
}

void graph_removeVertex(GRAPH graph, int item) {
    if (graph_isEmpty(graph)) {
        printf("Invalid, EMPTY graph\n");
        return;
    }
    Graph* weighted_graph = (Graph*)graph;
    for (int i = 0; i < weighted_graph ->size; i++) {
        if (weighted_graph ->adjagency_list[i] ->edge == NULL) continue;
        if (weighted_graph ->adjagency_list[i]->item == item) {
            while (weighted_graph ->adjagency_list[i] != NULL) {
                Vertex* temp = weighted_graph ->adjagency_list[i];
                weighted_graph ->adjagency_list[i] = weighted_graph ->adjagency_list[i] ->edge;
                free(temp);
            }
        }
        free(weighted_graph ->adjagency_list[i]);
        weighted_graph ->adjagency_list[i] = NULL;
    }
    return;
}

LIST graph_getAdjacentVerticies(GRAPH graph, int from) {
    if (graph_isEmpty(graph)) {
        printf("Invalid, EMPTY graph\n");
        return NULL;
    }
    Graph* weighted_graph = (Graph*)graph;
    LIST adjacent_vertices = list_init();
    for (int i = 0; i < weighted_graph ->size; i++) {
        if (weighted_graph ->adjagency_list[i] == NULL) continue;
        if (weighted_graph ->adjagency_list[i]->item == from) {
            Vertex* temp = weighted_graph ->adjagency_list[i];
            while (temp != NULL) {
                list_add(adjacent_vertices, temp ->item);
                temp = temp ->edge;
            }
            return adjacent_vertices;
        }
    }
    printf("Vertex %d is not in graph\n", from);
    return adjacent_vertices;
}

void graph_dfs(GRAPH graph) {
    if (graph_isEmpty(graph)) {
        printf("EMPTY graph\n");
        return;
    }
    //Graph* weighted_graph = (Graph*)graph;
    return;
}

int graph_getWeight(GRAPH graph, int from, int to) {
    if (!graph_containsVertex(graph, from) || !graph_containsVertex(graph, to)) {
        printf("Invalid! Either one of the vertices do not exist\n");
        return 0xC0FFEE;
    }
    Graph* weighted_graph = (Graph*)graph;
    for (int i = 0; i < weighted_graph ->size; i++) {
        if (weighted_graph ->adjagency_list[i]->item == from) {
            Vertex* temp = weighted_graph ->adjagency_list[i];
            while (temp ->item != to) {
                temp = temp ->edge;
            }
            return temp ->weight;
        }
    }
    return 0xC0FFEE;
}

void graph_bfs(GRAPH graph) {
    if (graph_isEmpty(graph)) {
        printf("EMPTY graph\n");
        return;
    }
    //Graph* weighted_graph = (Graph*)graph;
    return;
}

int graph_shortestPath(GRAPH graph, int from, int to) {
    if (graph_isEmpty(graph)) {
        printf("EMPTY graph\n");
        return -1;
    }
    if (!graph_isConnected(graph, from, to)) {
        printf("No path exists from %d to %d\n", from, to);
        return -1;
    }
    //Graph* weighted_graph = (Graph*)graph;
    
    return 1;
}

LIST topological_sort(GRAPH graph) {
    if (graph_isEmpty(graph)) {
        return NULL;
    }
    LIST sorted = list_init();
    return sorted;
}

void graph_destroy(GRAPH* graph) {
    if (!graph_isEmpty(*graph)) {
        Graph* weighted_graph = (Graph*)*graph;
        for (int i = 0; i < weighted_graph ->size; i++) {
            while (weighted_graph ->adjagency_list[i] != NULL) {
                Vertex* temp = weighted_graph ->adjagency_list[i];
                weighted_graph ->adjagency_list[i] = weighted_graph ->adjagency_list[i]->edge;
                free(temp);
            }
        }
    }
    free(*graph);
    *graph = NULL;
    return;
}

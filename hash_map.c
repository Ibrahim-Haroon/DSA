//
//  hash_map.c
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include "hash_map.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node_m { //_m for map node
    int key;
    int value;
    struct node_m* next;
}Node_m;
unsigned int hash(unsigned int key, HashMap hashmap); //private
bool hashMap_isFull(HashMap hashmap);                //private
void increase_table_size(HashMap hashmap);          //private
Node_m* create_node_m(int key, int value);          //private

typedef struct map{
    int size;
    int capacity;
    Node_m** table;
}Map;

HashMap hashMap_init(void) {
    Map* newMap = (Map*) malloc(sizeof(Map));
    if (newMap == NULL) {
        fprintf(stderr, "Failed to allocated space for hashMap\n");
        exit(EXIT_FAILURE);
    }
    newMap ->size = 0;
    newMap ->capacity = 1;
    newMap -> table = (Node_m**) calloc(newMap ->capacity, sizeof(Node_m*));
    if (newMap ->table == NULL) {
        fprintf(stderr, "Failed to allocate space for table\n");
        free(newMap); //unncessary
        exit(EXIT_FAILURE);
    }

    return newMap;
}

unsigned int hash(unsigned int key, HashMap hashmap) {
    Map* map = (Map*)hashmap;
    return (((31 * key) + 101) % map ->capacity); //Horner's rule
}

bool hashMap_isFull(HashMap hashmap) {
    Map* map = (Map*)hashmap;
    if (map ->size >= map ->capacity) return true;
    return false;
}

#define LOAD_FACTOR (2)
void increase_table_size(HashMap hashmap) {
    Map* map = (Map*)hashmap;
    map ->capacity *= LOAD_FACTOR;
    Node_m** new_table = (Node_m**) calloc((map ->capacity), sizeof(Node_m*));
    for (int i = 0; i < map ->capacity / LOAD_FACTOR; i++) {            //rehash everything
        while (map ->table[i] != NULL) {                                //makes sure to rehash any collided keys
            int index = hash(map ->table[i]->key, hashmap);
            if (new_table[index] == NULL) {
                new_table[index] = create_node_m(map ->table[i]->key, map ->table[i]->value);
            }
            else {
                Node_m* toInsert = create_node_m(map ->table[i]->key, map ->table[i]->value);
                toInsert ->next = new_table[index];
                new_table[index] = toInsert;
            }
            map ->table[i] = map ->table[i] ->next;
        }
    }
    free(map ->table);
    map ->table = new_table;
    return;
}

Node_m* create_node_m(int key, int value) {
    Node_m* newNode = (Node_m*) malloc(sizeof(Node_m));
    if (newNode == NULL) {
        fprintf(stderr, "Failed to allocate space for Node_m\n");
        exit(EXIT_FAILURE);
    }
    newNode ->key = key;
    newNode ->value = value;
    newNode ->next = NULL;
    return newNode;
}

bool hashMap_isEmpty(HashMap hashmap) {
    Map* map = (Map*)hashmap;
    if (map ->size <= 0) return true; //safer, in case there is a bug somewhere
    return false;
}

bool hashMap_contains(HashMap hashmap, int key);
void hashMap_insert(HashMap hashmap, int key, int value) {
    if (hashMap_contains(hashmap, key)) return; //no duplicates
    if (hashMap_isFull(hashmap)) increase_table_size(hashmap);
    Map* map = (Map*)hashmap;
    unsigned int index = hash(key, hashmap);
    if (map ->table[index] == NULL) {           //collision did not occur
        map ->table[index] = create_node_m(key, value);
        map ->size++;
    }
    else {                                      //collision OCCURED
        Node_m* toInsert = create_node_m(key, value);
        toInsert ->next = map ->table[index];
        map ->table[index] = toInsert;
    }
    return;
}

void hashMap_remove_entry(HashMap hashmap, int key) {
    if (hashMap_isEmpty(hashmap)) return;
    Map* map = (Map*)hashmap;
    int index = hash(key, hashmap);
    if (map ->table[index] == NULL) return;     //key was never in map
    if (map ->table[index]->key == key) {
        if (map ->table[index]->next == NULL) { //no collision at that index
            free(map ->table[index]);           //same as removing a node from a linked list of size 1
            map ->table[index] = NULL;
            map ->size--;
        }
        else {                                  //same as linked list remove
            Node_m* toRemove = map ->table[index];
            map ->table[index] = map ->table[index]->next;
            free(toRemove);
            toRemove = NULL;
        }
    }
    else {
        Node_m* slow = map ->table[index];
        Node_m* fast = map ->table[index];
        while (fast != NULL && fast ->key != key) {
            slow = fast;
            fast = fast ->next;
        }
        if (fast == NULL) {                      //key was never in map
            printf("%d was never in map!\n", key);
            return;
        }
        slow ->next = fast ->next;
        free(fast);
        fast = NULL;
    }
    return;
}

bool hashMap_contains(HashMap hashmap, int key) {
    if (hashMap_isEmpty(hashmap)) {
        return false;
    }
    Map* map = (Map*)hashmap;
    int index = hash(key, hashmap);
    if (map ->table[index] == NULL) return false;       //nothing was there
    if (map ->table[index]->key == key) return true;
    if (map ->table[index]->next == NULL) return false; //collision did not occure
    Node_m* temp = map ->table[index];
    while (temp != NULL && temp ->key != key) {
        temp = temp ->next;
    }
    if (temp == NULL) return false;
    return true;
}

void hashMap_print(HashMap hashmap) {
    if (hashMap_isEmpty(hashmap)) {
        printf("<EMPTY>\n");
        return;
    }
    Map* map = (Map*)hashmap;
    for (int i = 0; i < map ->capacity; i++) {
        if (map ->table[i] == NULL) {
            printf("\t%d\t<EMPTY>\n", i);
        }
        else {
            printf("\t%d\t{%d:%d}", i, map ->table[i]->key, map ->table[i]->value);
            if (map ->table[i]->next != NULL) { //collision had occured
                Node_m* temp = map ->table[i];
                temp = temp ->next;
                while (temp != NULL) {
                    printf(" - {%d:%d}", temp ->key, temp ->value);
                }
            }
            printf(" - NULL\n");
        }
    }
}

void hashMap_destroy(HashMap* hashmap) {
    if (hashMap_isEmpty(*hashmap)) {
        free(*hashmap);
        *hashmap = NULL;
        return;
    }
    Map** map = (Map**)hashmap;
    for (int i = 0; i < (*map) ->capacity; i++) {
        while ((*map) ->table[i] != NULL) {
            Node_m* temp = (*map) ->table[i];
            (*map) ->table[i] = (*map) ->table[i]->next;
            free(temp);
            temp = NULL;
        }
    }
    free(*hashmap);
    *hashmap = NULL;
    return;
}

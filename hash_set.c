//
//  hash_set.c
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include "hash_set.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node_set { //differentiate between different node structs
    int key;
    struct node_set* next;
}Node_Set;
static unsigned int hash_function(unsigned int key, HashSet hashset); //private
static bool hashMap_isFull(HashSet hashset);                //private
static void increase_set_size(HashSet hashset);          //private
static Node_Set* create_node_set(int key);        //private

typedef struct set{
    int size;
    int capacity;
    Node_Set** table;
}Set;

HashSet hashSet_init(void) {
    Set* newSet = (Set*) malloc(sizeof(Set));
    if (newSet == NULL) {
        fprintf(stderr, "Failed to allocated space for hashMap\n");
        exit(EXIT_FAILURE);
    }
    newSet ->size = 0;
    newSet ->capacity = 1;
    newSet -> table = (Node_Set**) calloc(newSet ->capacity, sizeof(Node_Set*));
    if (newSet ->table == NULL) {
        fprintf(stderr, "Failed to allocate space for table\n");
        free(newSet); //unncessary
        exit(EXIT_FAILURE);
    }

    return newSet;
}

unsigned int hash_function(unsigned int key, HashSet hashset) {
    Set* set = (Set*)hashset;
    return (((31 * key) + 101) % set ->capacity); //Horner's rule
}

bool hashSet_isFull(HashSet hashset) {
    Set* set = (Set*)hashset;
    if (set ->size >= set ->capacity) return true;
    return false;
}

#define LOAD_FACTOR (2)
void increase_set_size(HashSet hashset) {
    Set* set = (Set*)hashset;
    set ->capacity *= LOAD_FACTOR;
    Node_Set** new_table = (Node_Set**) calloc((set ->capacity), sizeof(Node_Set*));
    for (int i = 0; i < set ->capacity / LOAD_FACTOR; i++) {            //rehash everything
        while (set ->table[i] != NULL) {                                //makes sure to rehash any collided keys
            int index = hash_function(set ->table[i]->key, hashset);
            if (new_table[index] == NULL) {
                new_table[index] = create_node_set(set ->table[i]->key);
            }
            else {
                Node_Set* toInsert = create_node_set(set ->table[i]->key);
                toInsert ->next = new_table[index];
                new_table[index] = toInsert;
            }
            set ->table[i] = set ->table[i] ->next;
        }
    }
    free(set ->table);
    set ->table = new_table;
    return;
}

Node_Set* create_node_set(int key) {
    Node_Set* newNode = (Node_Set*) malloc(sizeof(Node_Set));
    if (newNode == NULL) {
        fprintf(stderr, "Failed to allocate space for Node_m\n");
        exit(EXIT_FAILURE);
    }
    newNode ->key = key;
    newNode ->next = NULL;
    return newNode;
}

bool hashSet_isEmpty(HashSet hashset) {
    Set* set = (Set*)hashset;
    if (set ->size <= 0) return true; //safer, in case there is a bug somewhere
    return false;
}

bool hashSet_contains(HashSet hashset, int key);
void hashSet_add(HashSet hashset, int key) {
    if (hashSet_contains(hashset, key)) return; //no duplicates
    if (hashSet_isFull(hashset)) increase_set_size(hashset);
    Set* set = (Set*)hashset;
    unsigned int index = hash_function(key, hashset);
    if (set ->table[index] == NULL) {           //collision did not occur
        set ->table[index] = create_node_set(key);
        set ->size++;
    }
    else {                                      //collision OCCURED
        Node_Set* toInsert = create_node_set(key);
        toInsert ->next = set ->table[index];
        set ->table[index] = toInsert;
    }
    return;
}

void hashSet_remove_entry(HashSet hashset, int key) {
    if (hashSet_isEmpty(hashset)) return;
    Set* set = (Set*)hashset;
    int index = hash_function(key, hashset);
    if (set ->table[index] == NULL) return;     //key was never in map
    if (set ->table[index]->key == key) {
        if (set ->table[index]->next == NULL) { //no collision at that index
            free(set ->table[index]);           //same as removing a node from a linked list of size 1
            set ->table[index] = NULL;
            set ->size--;
        }
        else {                                  //same as linked list remove
            Node_Set* toRemove = set ->table[index];
            set ->table[index] = set ->table[index]->next;
            free(toRemove);
            toRemove = NULL;
        }
    }
    else {
        Node_Set* slow = set ->table[index];
        Node_Set* fast = set ->table[index];
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

bool hashSet_contains(HashSet hashset, int key) {
    if (hashSet_isEmpty(hashset)) {
        return false;
    }
    Set* set = (Set*)hashset;
    int index = hash_function(key, hashset);
    if (set ->table[index] == NULL) return false;       //nothing was there
    if (set ->table[index]->key == key) return true;
    if (set ->table[index]->next == NULL) return false; //collision did not occure
    Node_Set* temp = set ->table[index];
    while (temp != NULL && temp ->key != key) {
        temp = temp ->next;
    }
    if (temp == NULL) return false;
    return true;
}

void hashSet_print(HashSet hashset) {
    if (hashSet_isEmpty(hashset)) {
        printf("<EMPTY>\n");
        return;
    }
    Set* set = (Set*)hashset;
    for (int i = 0; i < set ->capacity; i++) {
        if (set ->table[i] == NULL) {
            printf("\t%d\t<EMPTY>\n", i);
        }
        else {
            printf("\t%d\t{%d}", i, set ->table[i]->key);
            if (set ->table[i]->next != NULL) { //collision had occured
                Node_Set* temp = set ->table[i];
                temp = temp ->next;
                while (temp != NULL) {
                    printf(" - {%d}", temp ->key);
                }
            }
            printf(" - NULL\n");
        }
    }
}

void hashSet_destroy(HashSet* hashset) {
    if (hashSet_isEmpty(*hashset)) {
        free(*hashset);
        *hashset = NULL;
        return;
    }
    Set** set = (Set**)*hashset;
    for (int i = 0; i < (*set) ->capacity; i++) {
        while ((*set) ->table[i] != NULL) {
            Node_Set* temp = (*set) ->table[i];
            (*set) ->table[i] = (*set) ->table[i]->next;
            free(temp);
            temp = NULL;
        }
    }
    free(*hashset);
    *hashset = NULL;
    return;
}

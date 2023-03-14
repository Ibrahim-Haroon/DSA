//
//  dynamic_array.c
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include "dynamic_array.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct list{
    int size;
    int capacity;
    int* data;
}List;
bool isFull(LIST list); //private method
void increase_size(LIST list); //private method

bool isEmpty(LIST list);

LIST list_init(void) {
    List* newList = (List*) malloc(sizeof(List));
    if (newList == NULL) {
        fprintf(stderr, "Failed to init list\n");
        exit(EXIT_FAILURE);
    }
    newList ->size = 0;
    newList ->capacity = 1;
    newList ->data = (int*) malloc(sizeof(int) * newList ->capacity);
    if (newList ->data == NULL) {
        free(newList);
        fprintf(stderr, "Failed to allocate space for list\n");
        exit(EXIT_FAILURE);
    }
    return newList;
    
}

bool isEmpty(LIST list) {
    List* curr_list = (List*)list;
    return !curr_list ->size;
}

bool isFull(LIST list) {
    List* curr_list = (List*)list;
    if (curr_list ->size >= curr_list ->capacity) return true;
    return false;
}

#define LOAD_FACTOR (2)
void increase_size(LIST list) {
    List* curr_list = (List*)list;
    int* bigger_data = (int*) malloc(sizeof(int) * (curr_list ->capacity * LOAD_FACTOR));
    if (bigger_data == NULL) {
        fprintf(stderr,"Failed to increase size of list\n");
        exit(EXIT_FAILURE);
    }
    //copy old list to new list
    for (int i = 0; i < curr_list ->size; i++) {
        bigger_data[i] = curr_list ->data[i];
    }
    curr_list ->capacity *= LOAD_FACTOR;
    free(curr_list ->data); //free old list
    curr_list ->data = bigger_data;
}

void list_add(LIST list, int num) {
    if (isFull(list)) increase_size(list);
    List* curr_list = (List*)list;
    curr_list ->data[curr_list ->size++] = num;
}

void list_remove(LIST list, int num) {
    if (isEmpty(list)) {
        printf("Cannot remove from empty list\n");
        return;
    }
    List* curr_list = (List*)list;
    //first find num and its index
    int index = -1;
    for (int i = 0; i < curr_list ->size; i++) {
        if (curr_list ->data[i] == num) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("%d is not in the list\n", num);
        return;
    }
    //if end of list
    if (index == curr_list ->size) { //constant time O(1)
        curr_list ->size--;
    }
    //anywhere else in list
    else { //linear time O(n)
        //move every element down one
        for (int i = index; i < curr_list ->size; i++) {
            curr_list ->data[i] = curr_list ->data[i + 1];
        }
        curr_list ->size--;
    }
}

bool list_contains(LIST list, int num) {
    if (isEmpty(list)) return false;
    List* curr_list = (List*)list;
    for (int i = 0; i < curr_list ->size; i++) {
        if (curr_list ->data[i] == num) return true;
    }
    return false;
}

void list_num_at(LIST list, int index) {
    if (isEmpty(list)) {
        printf("Empty list\n");
        return;
    }
    List* curr_list = (List*)list;
    if (index < 0 || index > curr_list ->size) {
        printf("Invalid index\n");
        return;
    }
    printf("%d\n", curr_list ->data[index]);
    return;
    
}

void print_list(LIST list) {
    if (isEmpty(list)) {
        printf("[EMPTY]\n");
        return;
    }
    List* curr_list = (List*)list;
    printf("[");
    for (int i = 0; i < curr_list ->size; i++) {
        if (i == curr_list ->size - 1) {
            printf("%d", curr_list ->data[i]);
        }
        else printf("%d, ", curr_list ->data[i]);
    }
    printf("]\n");
    return;
}

void list_destroy(LIST* list) {
    if (isEmpty(list)) {
        free(*list);
        *list = NULL;
        return;
    }
    List* curr_list = (List*)*list;
    free(curr_list ->data);
    free(*list);
    *list = NULL;
    return;
}

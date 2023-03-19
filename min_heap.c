//
//  min_heap.c
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
/*
 Quick Referesher!
 
 if NODE is at index i then:
    left child @ (2 * i) + 1
    right child @ (2 * i) + 2
    parent @ floor(i / 2)
 */

#include "min_heap.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct dynamic_array{
    int size;
    int capacity;
    int* data;
}Dynamic_Array;

typedef struct heap_min{
    Dynamic_Array table;
}Heap_min;
bool minHeap_isFull(HEAP_MIN heap); //private
void minHeap_increaseSize(HEAP_MIN Heap); //private
void minHeap_recursively_insert(Dynamic_Array table, int value, int index); //private
void minHeap_swap(int* a, int* b); //private
void minHeap_heapify(Dynamic_Array table, int index); //private

HEAP_MIN minHeap_init(void) {
    Heap_min* newHeap = (Heap_min*) malloc(sizeof(Heap_min));
    if (newHeap == NULL) {
        printf("Failed to allocate space for heap\n");
        exit(EXIT_FAILURE);
    }
    newHeap ->table.size = 0;
    newHeap ->table.capacity = 1;
    newHeap ->table.data = (int*) malloc(sizeof(int) * newHeap ->table.capacity);
    if (newHeap ->table.data == NULL) {
        printf("Failed to allocate space for max heap's table\n");
        free(newHeap);
        exit(EXIT_FAILURE);
    }
    return newHeap;
}

bool minHeap_isFull(HEAP_MIN heap) {
    if (((Heap_min*)heap) ->table.size >= ((Heap_min*)heap) ->table.capacity) return true;
    return false;
}

#define LOAD_FACTOR (2)
void minHeap_increaseSize(HEAP_MIN Heap) {
    Heap_min* heap = (Heap_min*)Heap;
    
    int* largerTable = (int*) malloc(sizeof(int) * (heap ->table.capacity * LOAD_FACTOR));
    if (largerTable == NULL) {
        printf("Failed to dynamically increase table size.\n");
        return;
    }
    for (int i = 0; i < heap ->table.size; i++) {
        largerTable[i] = heap ->table.data[i];
    }
    free(heap ->table.data);
    heap ->table.data = largerTable;
    heap ->table.capacity *= LOAD_FACTOR;
    return;
}

bool minHeap_isEmpty(HEAP_MIN heap) {
    if (((Heap_min*)heap) ->table.size <= 0) return true;
    return false;
}

void minHeap_swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void minHeap_recursively_insert(Dynamic_Array table, int value, int index) {
    if (index == 0) {
        table.data[index] = value;
        return;
    }
    int parent_value = table.data[(index - 1)/ 2]; // -1 because 0 based indexing
    if (value >= parent_value) {
        table.data[index] = value;
        return;
    }
    table.data[index] = parent_value;
    minHeap_recursively_insert(table, value, (index - 1)/ 2); // -1 because 0 based indexing

    return;
}

void minHeap_insert(HEAP_MIN heap, int value) {
    if (minHeap_isFull(heap)) minHeap_increaseSize(heap);
    Heap_min* minHeap = (Heap_min*)heap;
    if (minHeap_isEmpty(heap)) {
        minHeap ->table.data[minHeap ->table.size++] = value;
    }
    else {
        minHeap_recursively_insert(minHeap ->table, value, minHeap ->table.size++);
    }
    return;
}

bool minHeap_contain(HEAP_MIN heap, int value) {
    if (heap == NULL || minHeap_isEmpty(heap)) return false;
    if (minHeap_getMin(heap) == value) return true;
    Heap_min* minHeap = (Heap_min*)heap;
    for (int i = 0; i < minHeap ->table.size; i++) {
        if (minHeap ->table.data[i] == value) return true;
    }
    return false;
}

void minHeap_replace(HEAP_MIN heap, int value) {
    if (minHeap_isEmpty(heap)) {
        printf("Heap is Empty\n");
        return;
    }
    Heap_min* minHeap = (Heap_min*)heap;
    int min = minHeap_getMin(heap);
    minHeap ->table.data[0] = value;
    if (min < value) {
        minHeap_heapify(minHeap ->table, 0); //ensure the min heap property is not violated
    }
    return;
}

int minHeap_size(HEAP_MIN heap) {
    if (heap == NULL) {
        printf("Invalid!\n");
        return -1;
    }
    if (minHeap_isEmpty(heap)) return 0;
    return (((Heap_min*)heap) ->table.size);
}

int minHeap_getMin(HEAP_MIN heap) {
    if (heap == NULL) {
        printf("Invalid!\n");
        return 0xC0FFEE;
    }
    if (minHeap_isEmpty(heap)) {
        printf("Heap is EMPTY\n");
        return 0xC0FFEE; //will return 12,648,430
    }
    return (((Heap_min*)heap) ->table.data[0]);
}

int minHeap_extractMin(HEAP_MIN heap) {
    int min = minHeap_getMin(heap);
    minHeap_removeMin(heap);
    return min;
}

void minHeap_remove(HEAP_MIN heap, int value) {
    if (heap == NULL || minHeap_isEmpty(heap)) return;
    Heap_min* minHeap = (Heap_min*)heap;
    
    int index = -1; //invalid to know whether the value was found
    for (int i = 0; i < minHeap->table.size; i++) {
        if (minHeap->table.data[i] == value) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("%d is not in the max heap!", value);
        return;
    }
    
    minHeap->table.data[index] = minHeap->table.data[minHeap ->table.size - 1];
    minHeap->table.size--;
    //if the number to remove is the root or the min heap property is broken
    if (index == 0 || minHeap ->table.data[index] > minHeap ->table.data[(index - 1) / 2]) {
        minHeap_heapify(minHeap ->table, index);
    }
    else {
        //keep swapping the number (that will take the place of the deleted number) with its parent while it is less than
        while (index > 0 && minHeap ->table.data[index] < minHeap ->table.data[(index - 1) / 2]) {
            minHeap_swap(&minHeap ->table.data[index], &minHeap ->table.data[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }
    return;
}

void minHeap_heapify(Dynamic_Array table, int index) {
    int leftChild_index = (2 * index) + 1;
    int rightChild_index = (2 * index) + 2;
    int smallerNumber_index = index;
    //detetmine the smallest number amoung children
    if (leftChild_index < table.size) {
        smallerNumber_index = table.data[leftChild_index] < table.data[smallerNumber_index] ? leftChild_index : smallerNumber_index;
    }
    if (rightChild_index < table.size) {
        smallerNumber_index = table.data[rightChild_index] < table.data[smallerNumber_index] ? rightChild_index : smallerNumber_index;
    }
    if (smallerNumber_index == index) {
        return;
    }
    minHeap_swap(&table.data[index], &table.data[smallerNumber_index]);
    minHeap_heapify(table, smallerNumber_index);
}

void minHeap_removeMin(HEAP_MIN heap) {
    if (heap == NULL || minHeap_isEmpty(heap)) return;
    Heap_min* minHeap = (Heap_min*)heap;
    
    minHeap_swap(&minHeap ->table.data[0], &minHeap ->table.data[minHeap ->table.size - 1]); //first swap max with last elemment to maintain a left complete tree
    minHeap ->table.size--;
    
    minHeap_heapify(minHeap ->table, 0);
    return;
}

void minHeap_print(HEAP_MIN heap) {
    if (heap == NULL) {
        printf("Invalid\n");
        return;
    }
    if (minHeap_isEmpty(heap)) {
        printf("EMPTY!\n");
        return;
    }
    Heap_min* minHeap = (Heap_min*)heap;
    printf("[");
    for (int i = 0; i < minHeap ->table.size; i++) {
        if (i == minHeap ->table.size - 1) {
            printf("%d", minHeap ->table.data[i]);
        }
        else printf("%d, ", minHeap ->table.data[i]);
    }
    printf("]\n");
    return;
}

void minHeap_destroy(HEAP_MIN* heap) {
    if (heap == NULL) return;
    if (minHeap_isEmpty(heap)) {
        free(*heap);
        *heap = NULL;
        return;
    }
    free((((Heap_min*)*heap)) ->table.data);
    free(*heap);
    *heap = NULL;
}

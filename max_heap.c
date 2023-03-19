//
//  max_heap.c
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

#include "max_heap.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct dynamic_arr{
    int size;
    int capacity;
    int* data;
}Dynamic_Arr;

typedef struct heap_max{
    Dynamic_Arr table;
}Heap_max;
bool maxHeap_isFull(HEAP_MAX heap); //private
void maxHeap_increaseSize(HEAP_MAX Heap); //private
void maxHeap_recursively_insert(Dynamic_Arr table, int value, int index); //private
void maxHeap_swap(int* a, int* b); //private
void maxHeap_removeRecusively(Dynamic_Arr table, int index); //private

HEAP_MAX maxHeap_init(void) {
    Heap_max* newHeap = (Heap_max*) malloc(sizeof(Heap_max));
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

bool maxHeap_isFull(HEAP_MAX heap) {
    if (((Heap_max*)heap) ->table.size >= ((Heap_max*)heap) ->table.capacity) return true;
    return false;
}

#define LOAD_FACTOR (2)
void maxHeap_increaseSize(HEAP_MAX Heap) {
    Heap_max* heap = (Heap_max*)Heap;
    
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

bool maxHeap_isEmpty(HEAP_MAX heap) {
    if (((Heap_max*)heap) ->table.size <= 0) return true;
    return false;
}

void maxHeap_swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void maxHeap_recursively_insert(Dynamic_Arr table, int value, int index) {
    if (index == 0) {
        table.data[index] = value;
        return;
    }
    int parent_value = table.data[(index - 1)/ 2]; // -1 because 0 based indexing
    if (value <= parent_value) {
        table.data[index] = value;
        return;
    }
    table.data[index] = parent_value;
    maxHeap_recursively_insert(table, value, (index - 1)/ 2); // -1 because 0 based indexing

    return;
}

void maxHeap_insert(HEAP_MAX heap, int value) {
    if (maxHeap_isFull(heap)) maxHeap_increaseSize(heap);
    Heap_max* maxHeap = (Heap_max*)heap;
    if (maxHeap_isEmpty(heap)) {
        maxHeap ->table.data[maxHeap ->table.size++] = value;
    }
    else {
        maxHeap_recursively_insert(maxHeap ->table, value, maxHeap ->table.size++);
    }
    
    return;
}

bool maxHeap_contain(HEAP_MAX heap, int value) {
    if (heap == NULL || maxHeap_isEmpty(heap)) return false;
    if (maxHeap_getMax(heap) == value) return true;
    Heap_max* maxHeap = (Heap_max*)heap;
    for (int i = 0; i < maxHeap ->table.size; i++) {
        if (maxHeap ->table.data[i] == value) return true;
    }
    return false;
}

void maxHeap_replace(HEAP_MAX heap, int value) {
    if (maxHeap_isEmpty(heap)) {
        printf("Heap is Empty\n");
        return;
    }
    Heap_max* maxHeap = (Heap_max*)heap;
    int max = maxHeap_getMax(heap);
    maxHeap ->table.data[0] = value;
    if (max > value) {
        maxHeap_heapify(heap); //ensure the max heap property is not violated
    }
    return;
}

int maxHeap_size(HEAP_MAX heap) {
    if (heap == NULL) {
        printf("Invalid!\n");
        return -1;
    }
    if (maxHeap_isEmpty(heap)) return 0;
    return (((Heap_max*)heap) ->table.size);
}

int maxHeap_getMax(HEAP_MAX heap) {
    if (heap == NULL) {
        printf("Invalid!\n");
        return 0xC0FFEE;
    }
    if (maxHeap_isEmpty(heap)) {
        printf("Heap is EMPTY\n");
        return 0xC0FFEE; //will return 12,648,430
    }
    return (((Heap_max*)heap) ->table.data[0]);
}

int maxHeap_extractMax(HEAP_MAX heap) {
    maxHeap_removeMax(heap);
    return maxHeap_getMax(heap);
}

void maxHeap_heapify(HEAP_MAX heap) {
    return;
}

void maxHeap_remove(HEAP_MAX heap, int value) {
    return;
}

void maxHeap_removeRecusively(Dynamic_Arr table, int index) {
    int leftChild_index = (2 * index) + 1;
    int rightChild_index = (2 * index) + 2;
    int largerIndex = index;
    //detetmine the largest number amoung children
    if (leftChild_index < table.size) {
        largerIndex = table.data[leftChild_index] > table.data[largerIndex] ? leftChild_index : largerIndex;
    }
    
    if (rightChild_index < table.size) {
        largerIndex = table.data[rightChild_index] > table.data[largerIndex] ? rightChild_index : largerIndex;
    }
    if (largerIndex == index) {
        return;
    }
    maxHeap_swap(&table.data[index], &table.data[largerIndex]);
    maxHeap_removeRecusively(table, largerIndex);
}

void maxHeap_removeMax(HEAP_MAX heap) {
    if (heap == NULL || maxHeap_isEmpty(heap)) return;
    Heap_max* maxHeap = (Heap_max*)heap;
    
    maxHeap_swap(&maxHeap ->table.data[0], &maxHeap ->table.data[maxHeap ->table.size - 1]); //first swap max with last elemment to maintain a left complete tree
    maxHeap ->table.size--;
    
    maxHeap_removeRecusively(maxHeap ->table, 0);
    return;
}

void maxHeap_print(HEAP_MAX heap) {
    if (heap == NULL) {
        printf("Invalid\n");
        return;
    }
    if (maxHeap_isEmpty(heap)) {
        printf("EMPTY!\n");
        return;
    }
    Heap_max* maxHeap = (Heap_max*)heap;
    printf("[");
    for (int i = 0; i < maxHeap ->table.size; i++) {
        if (i == maxHeap ->table.size - 1) {
            printf("%d", maxHeap ->table.data[i]);
        }
        else printf("%d, ", maxHeap ->table.data[i]);
    }
    printf("]\n");
    return;
}

void maxHeap_destroy(HEAP_MAX* heap) {
    if (heap == NULL) return;
    if (maxHeap_isEmpty(heap)) {
        free(*heap);
        *heap = NULL;
        return;
    }
    free((((Heap_max*)*heap)) ->table.data);
    free(*heap);
    *heap = NULL;
}

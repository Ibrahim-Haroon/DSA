//
//  min_heap.h
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#ifndef min_heap_h
#define min_heap_h

#include <stdbool.h>

typedef void* HEAP_MIN;

HEAP_MIN minHeap_init(void);
void minHeap_insert(HEAP_MIN heap, int value);
bool minHeap_contain(HEAP_MIN heap, int value);
void minHeap_replace(HEAP_MIN heap, int value);
bool minHeap_isEmpty(HEAP_MIN heap);
int minHeap_size(HEAP_MIN heap);
int minHeap_getMin(HEAP_MIN heap);
int minHeap_extractMin(HEAP_MIN heap);
void minHeap_remove(HEAP_MIN heap, int value);
void minHeap_removeMin(HEAP_MIN heap);
void minHeap_heapify(HEAP_MIN heap, int* array, int size);
void minHeap_print(HEAP_MIN heap);
void minHeap_destroy(HEAP_MIN* heap);

#endif /* min_heap_h */

//
//  max_heap.h
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#ifndef max_heap_h
#define max_heap_h

#include <stdbool.h>

typedef void* HEAP_MAX;

HEAP_MAX maxHeap_init(void);
bool maxHeap_isEmpty(HEAP_MAX heap);
void maxHeap_insert(HEAP_MAX heap, int value);
bool maxHeap_contain(HEAP_MAX heap, int value);
void maxHeap_replace(HEAP_MAX heap, int value);
int maxHeap_size(HEAP_MAX heap);
int maxHeap_getMax(HEAP_MAX heap);
int maxHeap_extractMax(HEAP_MAX heap);
void maxHeap_remove(HEAP_MAX heap, int value);
void maxHeap_removeMax(HEAP_MAX heap);
void maxHeap_heapify(int* array, int size);
void maxHeap_print(HEAP_MAX heap);
void maxHeap_destroy(HEAP_MAX* heap);


#endif /* max_heap_h */

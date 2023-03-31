//
//  main.c
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/14/23.
//
#include "max_heap.h"

int main() {
    int arr[] = {17, 45, 36, 78, 92, 101, 32, 17, 89, 102};
    HEAP_MAX test = maxHeap_init();
    maxHeap_heapify(test, arr, sizeof(arr)/sizeof(arr[0]));
    maxHeap_print(test);
    maxHeap_destroy(&test);
    return 0;
}

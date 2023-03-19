//
//  main.c
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include <stdlib.h>
#include <stdio.h>
#include "min_heap.h"

int main(int argc, char** argv) {
    HEAP_MIN test = minHeap_init();
    for (int i = 0; i < 23; i++) {
        minHeap_insert(test, rand() % 100);
    }
    minHeap_print(test);
    for (int i = 0; i < 23; i++) {
        printf("%d ", minHeap_extractMin(test));
    }
    minHeap_destroy(&test);
    printf("\n");
    return 0;
}

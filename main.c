//
//  main.c
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include <stdlib.h>
#include <stdio.h>
#include "max_heap.h"

int main(int argc, char** argv) {
    HEAP_MAX test = maxHeap_init();
    for (int i = 0; i < 23; i++) {
        maxHeap_insert(test, rand() % 100);
    }
    maxHeap_print(test);
    maxHeap_contain(test, 54) ? printf("YES\n") : printf("No\n");
    maxHeap_replace(test, 101);
    for (int i = 0; i < 23; i++) {
        printf("%d ", maxHeap_extractMax(test));
    }
    maxHeap_destroy(&test);
    printf("\n");
    return 0;
}

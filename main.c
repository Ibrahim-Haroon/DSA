//
//  main.c
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include <stdio.h>
#include "queue.h"

int main(int argc, char** argv) {
    QUEUE test = queue_init();
    for (int i = 0; i < 5; i++) {
        enqueue(test, i);
    }
    for (int i = 0; i < 3; i++) {
        dequeue(test);
    }
    queue_print(test);
    queue_destroy(&test);
    return 0;
}

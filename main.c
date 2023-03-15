//
//  main.c
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include "stack.h"
#include <stdio.h>

int main(int argc, char** argv) {
    STACK test = stack_init();
    for (int i = 0; i < 15; i++) {
        stack_push(test, i);
    }
    stack_pop(test);
    int peak = stack_peak(test);
    printf("%d\n", peak);
    stack_print(test);
    return 0;
}

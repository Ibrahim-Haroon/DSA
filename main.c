//
//  main.c
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include <stdio.h>
#include "binary_tree.h"

int main(int argc, char** argv) {
    BST test = bst_init();
    for (int i = 0; i < 100; i++) {
        bst_insert(test, i);
    }
    bst_print(test);
    bst_destroy(&test);
    return 0;
}

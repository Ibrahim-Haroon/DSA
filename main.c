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
    for (int i = 1; i <= 6; i++) {
        bst_insert(test, i);
    }
    
    bst_remove(test, 4);
    bst_contains(test, 4) ? printf("YES\n") : printf("NO\n");
    bst_print(test);
    bst_destroy(&test);
    return 0;
}

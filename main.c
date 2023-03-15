//
//  main.c
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include "doubly_linked_list.h"
#include <stdio.h>

int main(int argc, char** argv) {
    DOUBLY_LINKED_LIST test = dll_init();
    for (int i = 0; i < 15; i++) {
        dll_add(&test, i);
    }
    dll_remove_num(&test, 9);
    dll_remove(&test);
    dll_print(test);
    dll_contains(test, 23) ? printf("YES\n") : printf("NO\n");
    dll_destroy(&test);
    return 0;
}

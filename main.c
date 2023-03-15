//
//  main.c
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include "singly_linked_list.h"
#include <stdio.h>

int main(int argc, char** argv) {
    
    SINGLY_LINKED_LIST test = ll_init();
    for (int i = 0; i < 15; i++) {
        ll_add(&test, i);
    }
    ll_remove(&test);
    ll_remove_num(&test, 8); //need address of linked list in case the number being removed is the first node
    ll_print(test);
    ll_contains(test, 32) ? printf("YES\n") : printf("NO\n");
    ll_destroy(&test);
    return 0;
}

//
//  main.c
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include <stdio.h>
#include "hash_set.h"

int main(int argc, char** argv) {
    HashSet test = hashSet_init();
    for (int i = 0; i < 10; i++) {
        hashSet_add(test, i);
    }
    hashSet_remove_entry(test, 4);
    hashSet_print(test);
    hashSet_destroy(&test);
    return 0;
}

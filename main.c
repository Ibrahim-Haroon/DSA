//
//  main.c
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "hash_map.h"

int main(int argc, char** argv) {
    HashMap test = hashMap_init();
    for (int i = 0; i < 100; i++) {
        hashMap_insert(test, i, rand() % 250);
    }
    hashMap_print(test);
    hashMap_contains(test, 9) ? printf("YES\n") : printf("NO\n");
    hashMap_destroy(&test);
    return 0;
}

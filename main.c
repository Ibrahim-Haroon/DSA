//
//  main.c
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include "dynamic_array.h"
#include <stdio.h>

int main(int argc, const char * argv[]) {
    LIST test = list_init();
    list_remove(test, 10);
    for (int i = 0; i < 10; i++) {
        list_add(test, i);
    }
    list_remove(test, 4);
    list_remove(test, 0);
    list_remove(test, 9);
    print_list(test);
    list_contains(test, 3) ? printf("Found!\n") : printf("Not in List\n");
    list_destroy(&test);

    return 0;
}

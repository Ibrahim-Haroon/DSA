//
//  sorting.c
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

int* create_unsorted_arr(void) {
    //init array
    int* arr = (int*) malloc(sizeof(int) * ARRAY_SIZE);
    //check
    if (arr == NULL) {
        printf("Failed to allocate space for array on the heap\n");
        exit(EXIT_FAILURE);
    }
    //fill array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand();
    }
    return arr;
}
//definition: sorting algorithm that compares two adjacent elements and swaps them if they are out of order, it does this for the entire array for size - 1 times. Because at the end, the last item can only be in the correct spot since all other spots are taken.
void bubble_sort(int* arr) {
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        for (int j = 0; j < ARRAY_SIZE - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return;
}
//definition: sorting algorithm that finds the smallest item in the unsorted portion of the array and moves it to the sorted portion of the array, it does this size - 1 times. Because at the end, the last item can only be in the correct spot since all other spots are taken.
void selection_sort(int* arr) {
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        for (int j = 0; j < ARRAY_SIZE - 1; j++) {
            //TODO
        }
    }
    return;
}
//definition: sorting algorithm that finds the item of place in the unsorted portion of the array, and keeps moving the item that is the incorrect place to the left, which is the sorted portion. It does this size - 1 times. Because at the end, the last item can only be in the correct spot since all other spots are taken.
void insertion_sort(int* arr) {
    
    return;
}
//definition: sorting algorithm that compares items H away from each other, and if they are out of place, it swaps them. This is done size - 1 times. Because at the end, the last item can only be in the correct spot since all other spots are taken.
void shell_sort(int* arr) {
    
    return;
}
//definition:
void heap_sort(int* arr) {
    
    return;
}
//definition:
void quick_sort(int* arr) {
    
    return;
}
//definition:
void merge_sort(int* arr) {
    
    return;
}

void sort(int* arr, Sort_By technique) {
    switch (technique) {
        case BUBBLE:
            bubble_sort(arr);
            break;
        case SELECTION:
            selection_sort(arr);
            break;
        case INSERTION:
            insertion_sort(arr);
            break;
        case SHELL:
            shell_sort(arr);
            break;
        case HEAP:
            heap_sort(arr);
            break;
        case QUICK:
            quick_sort(arr);
            break;
        case MERGE:
            merge_sort(arr);
            break;
        default:
            printf("Invalid sorting algorithm\n");
            return;
    }
}


void sort_print(int *arr) {
    printf("[");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (i == ARRAY_SIZE - 1) {
            printf("%d]\n", arr[i]);
        }
        else printf("%d, ", arr[i]);
    }
    return;
}

void sort_destroy(int* arr) {
    free(arr);
    arr = NULL;
    return;
}



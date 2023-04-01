//
//  sorting.c
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

#define TIMED(_code) \
clock_t _start_time = clock(); \
_code; \
clock_t _end_time = clock(); \
return (_end_time - _start_time) / (double)CLOCKS_PER_SEC; \


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
        arr[i] = rand() % 20;
    }
    return arr;
}

double bubble_sort(int* arr) {
    TIMED (
        for (int i = 0; i < ARRAY_SIZE - 1; i++) {
            for (int j = 0; j < ARRAY_SIZE - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    )
}

double selection_sort(int* arr) {
    TIMED (
        for (int i = 0; i < ARRAY_SIZE - 1; i++) {
            int index_of_smallest = i;
            for (int j = i; j < ARRAY_SIZE; j++) {
                index_of_smallest = arr[j] < arr[index_of_smallest] ? j : index_of_smallest;
            }
            int temp = arr[index_of_smallest];
            arr[index_of_smallest] = arr[i];
            arr[i] = temp;
        }
    )
}

double insertion_sort(int* arr) {
    TIMED (
        for (int i = 1; i < ARRAY_SIZE; i++) {
            int j = i;
            int temp = arr[j];
            while (j > 0 && temp < arr[j - 1]) {
                arr[j] = arr[j - 1]; //moving items to the right
                j--;
            }
            arr[j] = temp; //there will not be a open spot to insert the item
        }
    )
}

double shell_sort(int* arr) {
    TIMED (
        //Knuth sequence
        int h = 2;
        while (h < ARRAY_SIZE / 3) {
            h *= 2;
        }
        h--;
        //^memorize
        while (h != 0) {
            for (int i = h; i < ARRAY_SIZE; i++) {
                int j = i;
                int temp = arr[j];
                while (j >= h && temp < arr[j - 1]) {
                    arr[j] = arr[j - 1];
                    j -= h;
                }
                arr[j] = temp;
            }
            h /= 2;
        }
    )
}

void heap_sort_fix_down(int* arr, int size, int i) {
    int index_left = i * 2 + 1;
    int index_right = i * 2 + 2;
    int index_largest = i;
    
    if (index_left < size) {
        index_largest = arr[index_left] > arr[index_largest] ? index_left : index_largest;
    }
    if (index_right < size) {
        index_largest = arr[index_right] > arr[index_largest] ? index_right : index_largest;
    }
    if (index_largest == i) {
        return;
    }
    int temp = arr[i];
    arr[i] = arr[index_largest];
    arr[index_largest] = temp;
    heap_sort_fix_down(arr, size, index_largest);
}

double heap_sort(int* arr) {
    TIMED (
        for (int i = (ARRAY_SIZE / 2 - 1); i >= 0; i--) {
            heap_sort_fix_down(arr, ARRAY_SIZE, i);
        }

        for (int i = 0; i < ARRAY_SIZE - 1; i++) {
           int temp = arr[0];
           arr[0] = arr[ARRAY_SIZE - i - 1];
           arr[ARRAY_SIZE - i - 1] = temp;
           heap_sort_fix_down(arr, ARRAY_SIZE - i - 1, 0);
        }
    )
}

double quick_sort(int* arr) {
    
    return 0;
}

double merge_sort(int* arr) {
    
    return 0;
}

double count_sort(int* arr) {
    
    return 0;
}

double radix_sort(int* arr) {
    
    return 0;
}

void sort(int* arr, Sort_By technique, TIME timed) {
    switch (technique) {
        case BUBBLE:
            if (timed == withTime) {
                double time = bubble_sort(arr);
                printf("Bubble sort took %.2f seconds\n", time);
            }
            else bubble_sort(arr);
            break;
        case SELECTION:
            if (timed == withTime) {
                double time = selection_sort(arr);
                printf("Selection sort took %.2f seconds\n", time);
            }
            else selection_sort(arr);
            break;
        case INSERTION:
            if (timed == withTime) {
                double time = insertion_sort(arr);
                printf("Insertion sort took %.2f seconds\n", time);
            }
            else insertion_sort(arr);
            break;
        case SHELL:
            if (timed == withTime) {
                double time = shell_sort(arr);
                printf("Shell sort took %.2f seconds\n", time);
            }
            else shell_sort(arr);
            break;
        case HEAP:
            if (timed == withTime) {
                double time = heap_sort(arr);
                printf("Heap sort took %.2f seconds\n", time);
            }
            else heap_sort(arr);
            break;
        case QUICK:
            if (timed == withTime) {
                double time = quick_sort(arr);
                printf("Quick sort took %.2f seconds\n", time);
            }
            else quick_sort(arr);
            break;
        case MERGE:
            if (timed == withTime) {
                double time = merge_sort(arr);
                printf("Merge sort took %.2f seconds\n", time);
            }
            else merge_sort(arr);
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



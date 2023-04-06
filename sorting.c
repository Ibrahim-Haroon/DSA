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


int* create_unsorted_arr(int size) {
    //init array
    int* arr = (int*) malloc(sizeof(int) * size);
    //check
    if (arr == NULL) {
        printf("Failed to allocate space for array on the heap\n");
        exit(EXIT_FAILURE);
    }
    //fill array
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 20;
    }
    return arr;
}

double bubble_sort(int* arr, int size) {
    TIMED (
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    )
}

double selection_sort(int* arr, int size) {
    TIMED (
        for (int i = 0; i < size - 1; i++) {
            int index_of_smallest = i;
            for (int j = i; j < size; j++) {
                index_of_smallest = arr[j] < arr[index_of_smallest] ? j : index_of_smallest;
            }
            int temp = arr[index_of_smallest];
            arr[index_of_smallest] = arr[i];
            arr[i] = temp;
        }
    )
}

double insertion_sort(int* arr, int size) {
    TIMED (
        for (int i = 1; i < size; i++) {
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

double shell_sort(int* arr, int size) {
    TIMED (
        //Knuth sequence
        int h = 2;
        while (h < size / 3) {
            h *= 2;
        }
        h--;
        //^memorize
        while (h != 0) {
            for (int i = h; i < size; i++) {
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

static void heap_sort_fix_down(int* arr, int size, int i) { //private helper function
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

double heap_sort(int* arr, int size) {
    TIMED (
        for (int i = (size / 2 - 1); i >= 0; i--) {
            heap_sort_fix_down(arr, size, i);
        }

        for (int i = 0; i < size - 1; i++) {
           int temp = arr[0];
           arr[0] = arr[size - i - 1];
           arr[size - i - 1] = temp;
           heap_sort_fix_down(arr, size - i - 1, 0);
        }
    )
}

void quick_sort(int* arr, int size) {
    if (size <= 7) {
        insertion_sort(arr, size);
        return;
    }
    int rand_pivot_index = rand() % size;

    int left = 0, right = size - 1;
    while (left < right) {
        if (arr[right] >= arr[rand_pivot_index]) {
            right--;
        }
        else if (arr[left] <= arr[rand_pivot_index]) {
            left++;
        }
        else {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
        }
    }
    //exists loop when left == right so pivot must be swapped with left or right
    int temp = arr[rand_pivot_index];
    arr[rand_pivot_index] = arr[left];
    arr[left] = temp;

    quick_sort(arr, left); //sort left subarray
    quick_sort(arr + left + 1, size - left - 1); //sort right subarray
    
    //should never reach here
    return;
}

double qsort_w_time(int* arr, int size) {
    TIMED (
           if (size <= 7) {
               insertion_sort(arr, size);
           }
           else {
               quick_sort(arr, size);
           }
       )
}

double merge_sort(int* arr, int size) {
    
    return 0;
}

double count_sort(int* arr, int size) {
    TIMED (
       //first find max
       int max = arr[0];
       for (int i = 0; i < size; i++) {
           max = arr[i] > max ? arr[i] : max;
       }
       int* iterative_count = (int*) calloc(sizeof(int), max + 1); //sets all values to 0
       if (iterative_count == NULL) {
           printf("Failed to allocate space for iterative count for count sort\n");
           return 0.0;
       }
        //iteration
       for (int i = 0; i < size; i++) {
           int index = arr[i];
           iterative_count[index]++;
       }
       int* accumulative_sum = (int*) calloc(sizeof(int), max + 1); //sets all values to 0
       if (accumulative_sum == NULL) {
           printf("Failed to allocate space for accumulative sum for count sort\n");
           return 0.0;
       }
       accumulative_sum[0] = iterative_count[0];
       for (int i = 1; i < max + 1; i++) {
           accumulative_sum[i] = iterative_count[i] + accumulative_sum[i - 1];
       }
       free(iterative_count);   //no longer need
       int* res = (int*) malloc(sizeof(int) * size);
       if (res == NULL) {
           printf("Failed to allocate space for res array for count sort\n");
       }
       for (int i = size - 1; i >= 0; i--) {
           int index = accumulative_sum[arr[i]] - 1;
           res[index] = arr[i];
           accumulative_sum[arr[i]]--;
       }
       free(accumulative_sum);  //no longer need
       //copy res to orginal array
       for (int i = 0; i < size; i++) {
           arr[i] = res[i];
       }
       free(res);              //no longer need
   )
}

double radix_sort(int* arr, int size) {
    
    return 0.0;
}

void sort(int* arr, int size, Sort_By technique, TIME timed) {
    switch (technique) {
        case BUBBLE:
            if (timed == withTime) {
                double time = bubble_sort(arr, size);
                printf("Bubble sort took %.2f seconds\n", time);
            }
            else bubble_sort(arr, size);
            break;
        case SELECTION:
            if (timed == withTime) {
                double time = selection_sort(arr, size);
                printf("Selection sort took %.2f seconds\n", time);
            }
            else selection_sort(arr, size);
            break;
        case INSERTION:
            if (timed == withTime) {
                double time = insertion_sort(arr, size);
                printf("Insertion sort took %.2f seconds\n", time);
            }
            else insertion_sort(arr, size);
            break;
        case SHELL:
            if (timed == withTime) {
                double time = shell_sort(arr, size);
                printf("Shell sort took %.2f seconds\n", time);
            }
            else shell_sort(arr, size);
            break;
        case HEAP:
            if (timed == withTime) {
                double time = heap_sort(arr, size);
                printf("Heap sort took %.2f seconds\n", time);
            }
            else heap_sort(arr, size);
            break;
        case QUICK:
            if (timed == withTime) {
                double time = qsort_w_time(arr, size);
                printf("Quick sort took %.2f seconds\n", time);
            }
            else quick_sort(arr, size);
            break;
        case MERGE:
            if (timed == withTime) {
                double time = merge_sort(arr, size);
                printf("Merge sort took %.2f seconds\n", time);
            }
            else merge_sort(arr, size);
            break;
        case COUNT:
            if (timed == withTime) {
                double time = count_sort(arr, size);
                printf("Count sort took %.2f seconds\n", time);
            }
            else count_sort(arr, size);
            break;
        case RADIX:
            if (timed == withTime) {
                double time = count_sort(arr, size);
                printf("Count sort took %.2f seconds\n", time);
            }
            else radix_sort(arr, size);
            break;
        default:
            printf("Invalid sorting algorithm\n");
            return;
    }
}


void sort_print(int *arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        if (i == size - 1) {
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



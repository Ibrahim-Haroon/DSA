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
        arr[i] = rand();
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
    int index_largest = i;
    while (1) {
        int index_left = i * 2 + 1;
        int index_right = i * 2 + 2;
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
        
        i = index_largest;
    }
    return;
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
    int left_index = 0;
    int middle_index = size / 2;
    int right_index = size - 1;
    
    if (arr[middle_index] < arr[left_index]) {
        int temp = arr[left_index];
        arr[left_index] = arr[middle_index];
        arr[middle_index] = temp;
    }
    if (arr[right_index] < arr[middle_index]) {
        int temp = arr[right_index];
        arr[right_index] = arr[middle_index];
        arr[middle_index] = temp;
    }
    if (arr[middle_index] < arr[left_index]) {
        int temp = arr[middle_index];
        arr[middle_index] = arr[left_index];
        arr[left_index] = temp;
    }
    
    int pivot_index = 1;
    
    int temp =  arr[middle_index];
    arr[middle_index] = arr[pivot_index];
    arr[pivot_index] = temp;

    int left = 1, right = size - 2;
    while (left < right) {
        if (arr[right] >= arr[pivot_index]) {
            right--;
        }
        else if (arr[left] <= arr[pivot_index]) {
            left++;
        }
        else {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
        }
    }
    //exists loop when left == right so pivot must be swapped with either left or right
    temp = arr[pivot_index];
    arr[pivot_index] = arr[left];
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

void merge(int arr[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    
    int* leftArr = (int*)malloc(n1 * sizeof(int));
    if (leftArr == NULL) {
        fprintf(stderr, "Failed to allocate space for left array\n");
        return;
    }
    int* rightArr = (int*)malloc(n2 * sizeof(int));
    if (rightArr == NULL) {
        fprintf(stderr, "Failed to allocate space for right array\n");
        return;
    }
    
    for (i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    
    for (j = 0; j < n2; j++) {
        rightArr[j] = arr[middle + 1 + j];
    }
    
    i = 0;
    j = 0;
    k = left;
    
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
    
    free(leftArr);
    free(rightArr);
}


int min(int a, int b) {
    return a < b ? a : b;
}

void merge_sort(int* arr, int size) {
    int currSize;
    int leftStart, middle, rightEnd;
    
    for (currSize = 1; currSize < size; currSize *= 2) {
        for (leftStart = 0; leftStart < size - 1; leftStart += 2 * currSize) {
            middle = leftStart + currSize - 1;
            rightEnd = min(leftStart + 2 * currSize - 1, size - 1);
            merge(arr, leftStart, middle, rightEnd);
        }
    }

    return;
}

double timed_mergeSort(int* arr, int size) {
    int currSize;
    int leftStart, middle, rightEnd;
    TIMED (
           for (currSize = 1; currSize < size; currSize *= 2) {
               for (leftStart = 0; leftStart < size - 1; leftStart += 2 * currSize) {
                   middle = leftStart + currSize - 1;
                   rightEnd = min(leftStart + 2 * currSize - 1, size - 1);
                   merge(arr, leftStart, middle, rightEnd);
               }
           }
        )
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

int maxElement(int* arr, int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

void radix_helper(int* arr, int size, int digitPlace) {
    int tempArraysSize = maxElement(arr, size) + 1;
    
    int* iterationCount = (int*) calloc(tempArraysSize, sizeof(int));
    if (iterationCount == NULL) exit(EXIT_FAILURE);
    //determine occurence of each element
    for (int i = 0; i < size; i++) {
        int num = (arr[i] / digitPlace) % 10;
        iterationCount[num]++;
    }
    
    int* accumulativeSum = (int*) calloc (tempArraysSize, sizeof(int));
    if (accumulativeSum == NULL) exit(EXIT_FAILURE);
    //determine the element and element before
    accumulativeSum[0] = iterationCount[0];
    for (int i = 1; i < tempArraysSize; i++) {
        accumulativeSum[i] = iterationCount[i] + accumulativeSum[i - 1];
    }
    free(iterationCount);
    
    int* res = (int*) malloc (sizeof(int) * size);
    if (res == NULL) exit(EXIT_FAILURE);
    //place all numbers in correct slot
    for (int i = size - 1; i >= 0; i--) {
        int index = accumulativeSum[(arr[i] / digitPlace) % 10] - 1;
        res[index] = arr[i];
        accumulativeSum[(arr[i] / digitPlace) % 10]--;
    }
    free(accumulativeSum);
    //copy sorted arr to original arr
    for (int i = 0; i < size; i++) arr[i] = res[i];
}

double radix_sort(int* arr, int size) {
    TIMED (
       int max = maxElement(arr, size);
       for (int digitPlace = 1; max / digitPlace > 0; digitPlace *=10) {
           radix_helper(arr, size, digitPlace);
       }
       )
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
                double time = timed_mergeSort(arr, size);
                printf("Merge sort took %.2f seconds\n", time);
            }
             merge_sort(arr, size);
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



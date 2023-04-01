//
//  sorting.h
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/31/23.
//

#ifndef sorting_h
#define sorting_h

#define ARRAY_SIZE (10)

typedef enum sorting_technique {
    BUBBLE,     //O(n^2)
    SELECTION,  //O(n^2)
    INSERTION,  //O(n^2)
    SHELL,      //O(n^2)
    HEAP,       //O(n*log n)
    QUICK,      //O(n*log n)
    MERGE,      //O(n*log n)
    COUNT,      //O(n) ***in some cases
    RADIX       //O(n) ***in some cases
}Sort_By;

typedef enum time{
    withTime,
    withoutTime
}TIME;

int* create_unsorted_arr(void);
void sort(int* arr, Sort_By technique, TIME timed);
//definition: sorting algorithm that compares two adjacent elements and swaps them if they are out of order, it does this for the entire array for size - 1 times. Because at the end, the last item can only be in the correct spot since all other spots are taken.
double bubble_sort(int* arr);
//definition: sorting algorithm that finds the smallest item in the unsorted portion of the array and moves it to the sorted portion of the array, it does this size - 1 times. Because at the end, the last item can only be in the correct spot since all other spots are taken.
double selection_sort(int* arr);
//definition: sorting algorithm that finds the item of place in the unsorted portion of the array, and keeps moving the item that is in the incorrect place to the left, which is the sorted portion. It does this size - 1 times. Because at the end, the last item can only be in the correct spot since all other spots are taken.
double insertion_sort(int* arr);
//definition: sorting algorithm that compares and swaps items that are at certain gap, h,  distance apart. The algorithm starts with a larger gap size and reduces it over multiple passes until the gap size becomes 1, at which point the algorithm becomes equivalent to an insertion sort.
double shell_sort(int* arr);
//definition:
double heap_sort(int* arr);
//definition:
double quick_sort(int* arr);
//definition:
double merge_sort(int* arr);
//definition:
double count_sort(int* arr);
//definition:
double radix_sort(int* arr);
void sort_print(int *arr);
void sort_destroy(int* arr);

#endif /* sorting_h */

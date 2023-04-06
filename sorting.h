//
//  sorting.h
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/31/23.
//

#ifndef sorting_h
#define sorting_h

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

int* create_unsorted_arr(int size);
void sort(int* arr, int size, Sort_By technique, TIME timed);
//definition: sorting algorithm that compares two adjacent elements and swaps them if they are out of order, it does this for the entire array for size - 1 times. Because at the end, the last item can only be in the correct spot since all other spots are taken.
double bubble_sort(int* arr, int size);
//definition: sorting algorithm that finds the smallest item in the unsorted portion of the array and moves it to the sorted portion of the array, it does this size - 1 times. Because at the end, the last item can only be in the correct spot since all other spots are taken.
double selection_sort(int* arr, int size);
//definition: sorting algorithm that finds the item of place in the unsorted portion of the array, and keeps moving the item that is in the incorrect place to the left, which is the sorted portion. It does this size - 1 times. Because at the end, the last item can only be in the correct spot since all other spots are taken.
double insertion_sort(int* arr, int size);
//definition: sorting algorithm that compares and swaps items that are at certain gap, h,  distance apart. The algorithm starts with a larger gap size and reduces it over multiple passes until the gap size becomes 1, at which point the algorithm becomes equivalent to an insertion sort.
double shell_sort(int* arr, int size);
//definition:
double heap_sort(int* arr, int size);
//definition:
void quick_sort(int* arr, int size);
//definition:
double merge_sort(int* arr, int size);
//definition: sorting algorithm that uses non-comparison based technique to sort items. Count sort uses 3 auxillary arrays. The first array (iteration count) will determine the amount of times each number repeats, so you first find the largest element and make the array of that size + 1. The second array (accumulative sum) which will be the same size as the first array, will then go through the first array and add all previous numbers together. Ex. Array 1 = [0, 2, 4, 1] => Array 2 = [0, 2, 6, 7]. In the final array, the size of the inputed array, will start from the last item in the second array, and put it in the correct slot. So if in the index 5 is the number 3 => in the final array at index 3 will be the number 5. You then have to subtract -1 each time from value at the index in Array 2 until it is 0. Finally copy the final array into the original array.
double count_sort(int* arr, int size);
//definition: sorting algorithm that does count sort on every single digit, from least to most significant.
double radix_sort(int* arr, int size);
void sort_print(int *arr, int size);
void sort_destroy(int* arr);

#endif /* sorting_h */

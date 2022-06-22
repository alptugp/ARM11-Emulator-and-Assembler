#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

// Gets the number of elements in an array
int get_int_array_size(int *array);

// Prints an array of integers 
void print_int_array(int *array);

// Gets an integer array from the user 
int *get_int_array(void);

// Visualises the bubble sort algorithm
// Print the number of steps required to sort the array
// Returns the final sorted array
int *bubble_sort_visualiser(int *array);

// The partition function used in quick sort
int partition(int* array, int start, int end)

// Visualise the quick sort algorithm
// Prints the number of steps required to sort the array and the final sorted array
// Returns the final sorted array
int *insertion_sort_visualiser(int *array);

// Pivot function used in quick sort
// Takes the last element as the pivot, and moves all elements less than the pivot to the left of the pivot,
// and all elements greater than the pivot to the right of the pivot
int pivot(int* array, int start, int end);

// Visualises the selection sort algorithm
// Prints the number of steps required to sort the array and the final sorted array
// Returns the final sorted array
int *selection_sort_visualiser(int *array);

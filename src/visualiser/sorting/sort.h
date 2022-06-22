#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

// Gets the number of elements in an array
int get_int_array_size(int *array);

// Prints an array of integers 
void print_int_array(int *array);

// A function to get an integer array from the user by reading command line input
// Should ask for the size of the array and then ask for the elements of the array
// Should return the array
// Should check for errors in the input, e.g. if the user enters a non-integer, or an integer that is too large
// Should throw an error and exit if the user enters invalid input

int *get_int_array(void);

// A function to perform bubble sort on an array of integers, and show each step of the sort, explain what is happening
// and the final sorted array
// and should print the number of steps required to sort the array
// Should return the final sorted array
int *bubble_sort_visualiser(int *array);

#include "sort.h"

int get_int_array_size(int *array) {
    int i;
    for (i = 0; array[i] != '\0'; i++) {
        continue;
    }
    return i;
}

void print_int_array(int *array) {
    for (int i = 0; i < get_int_array_size(array); i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int* get_int_array(void) {
    int array_size;
    int* array;
    printf("Enter the size of the array.\n");
    scanf("%d", &array_size);
    array = malloc(sizeof(int) * array_size);
    for (int i = 0; i < array_size; i++) {
        printf("Enter the %dth element of the array.\n", i);
        scanf("%d", &(array[i]));
    }
    return array;
}

int *bubble_sort_visualiser(int *array) {
    int array_size = get_int_array_size(array);
    printf("Initial array: ");
    print_int_array(array);
    int i, j, temp;
    int num_steps = 0;
    for (i = 0; i < array_size - 1; i++) {
        for (j = 0; j < array_size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                printf("Step %d: Swapped %d and %d\n", num_steps, array[j], array[j + 1]);
                printf("Current array: ");
                print_int_array(array);
                num_steps++;
            }
        }
    }
    printf("\nTotal number of steps required to sort: %d\n", num_steps);
    printf("Final sorted array: ");
    print_int_array(array);
    return array;
}
#include "sort.h"
#include <assert.h>

// A function to check if two arrays are equal
// Should return 1 if the arrays are equal, 0 otherwise
int check_arrays_equal(int *array1, int *array2) {
    int array1_size = get_int_array_size(array1);
    int array2_size = get_int_array_size(array2);
    if (array1_size != array2_size) {
        return 0;
    }
    for (int i = 0; i < array1_size; i++) {
        if (array1[i] != array2[i]) {
            return 0;
        }
    }
    return 1;
}

// A unit test for check_arrays_equal
void test_check_arrays_equal() {
    int array1[] = {1, 2, 3, 4, 5};
    int array2[] = {1, 2, 3, 4, 5};
    int array3[] = {1, 2, 3, 4, 6};
    int array4[] = {1, 2, 3, 4};
    int array5[] = {34, 25, 32, 41, 54};
    int array6[] = {4, 2, 329532, 4, 55};
    int array7[] = {34, 25, 32, 41, 54};
    int array8[] = {4, 2, 329532, 4, 55};
    int array9[] = {};

    assert(check_arrays_equal(array1, array2) == 1);
    assert(check_arrays_equal(array1, array3) == 0);
    assert(check_arrays_equal(array1, array4) == 0);
    assert(check_arrays_equal(array1, array5) == 0);
    assert(check_arrays_equal(array1, array6) == 0);
    assert(check_arrays_equal(array3, array4) == 0);
    assert(check_arrays_equal(array3, array5) == 0);
    assert(check_arrays_equal(array3, array6) == 0);
    assert(check_arrays_equal(array4, array5) == 0);
    assert(check_arrays_equal(array4, array6) == 0);
    assert(check_arrays_equal(array5, array6) == 0);
    assert(check_arrays_equal(array7, array8) == 1);
    assert(check_arrays_equal(array7, array9) == 0);
    assert(check_arrays_equal(array8, array9) == 0);
    assert(check_arrays_equal(array8, array6) == 1);

    assert(check_arrays_equal(array1, array1) == 1);
    assert(check_arrays_equal(array2, array2) == 1);
    assert(check_arrays_equal(array3, array3) == 1);
    assert(check_arrays_equal(array4, array4) == 1);
    assert(check_arrays_equal(array5, array5) == 1);
    assert(check_arrays_equal(array6, array6) == 1);
    assert(check_arrays_equal(array7, array7) == 1);
    assert(check_arrays_equal(array8, array8) == 1);
    assert(check_arrays_equal(array9, array9) == 1);

    printf("All check_arrays_equal tests passed.\n");
}

// A unit test for bubble sort visualiser
// Uses the check_arrays_equal function to check if the sorted array is correct
void test_bubble_sort_visualiser() {
    int array1[] = {1, 2, 3, 4, 5};
    int array2[] = {4, 5, 3, 2, 1};
    int array3[] = {443232, 34, 25, 32, 41, 54};
    int array4[] = {4, 2, 329532, 4, 55};
    int array5[] = {34, 25, 32, 41, 54};
    int array6[] = {4, 2, 329532, 4, 55};
    int array7[] = {849, 33, 3434, 2221, 4234, 99};
    int array8[] = {};

    int array1_sorted[] = {1, 2, 3, 4, 5};
    int array2_sorted[] = {1, 2, 3, 4, 5};
    int array3_sorted[] = {25, 32, 34, 41, 54, 443232};
    int array4_sorted[] = {2, 4, 4, 55, 329532};
    int array5_sorted[] = {25, 32, 34, 41, 54};
    int array6_sorted[] = {2, 4, 4, 55, 329532};
    int array7_sorted[] = {849, 2221, 33, 99, 3434, 4234};
    int array8_sorted[] = {};

    int *bubble_sorted_array1 = bubble_sort_visualiser(array1);
    int *bubble_sorted_array2 = bubble_sort_visualiser(array2);
    int *bubble_sorted_array3 = bubble_sort_visualiser(array3);
    int *bubble_sorted_array4 = bubble_sort_visualiser(array4);
    int *bubble_sorted_array5 = bubble_sort_visualiser(array5);
    int *bubble_sorted_array6 = bubble_sort_visualiser(array6);
    int *bubble_sorted_array7 = bubble_sort_visualiser(array7);
    int *bubble_sorted_array8 = bubble_sort_visualiser(array8);

    assert(check_arrays_equal(bubble_sorted_array1, array1_sorted) == 1);
    assert(check_arrays_equal(bubble_sorted_array2, array2_sorted) == 1);
    assert(check_arrays_equal(bubble_sorted_array3, array3_sorted) == 1);
    assert(check_arrays_equal(bubble_sorted_array4, array4_sorted) == 1);
    assert(check_arrays_equal(bubble_sorted_array5, array5_sorted) == 1);
    assert(check_arrays_equal(bubble_sorted_array6, array6_sorted) == 1);
    assert(check_arrays_equal(bubble_sorted_array7, array7_sorted) == 1);
    assert(check_arrays_equal(bubble_sorted_array8, array8_sorted) == 1);

    assert(check_arrays_equal(bubble_sorted_array1, bubble_sorted_array2) == 1);
    assert(check_arrays_equal(bubble_sorted_array1, bubble_sorted_array3) == 0);
    assert(check_arrays_equal(bubble_sorted_array1, bubble_sorted_array4) == 0);
    assert(check_arrays_equal(bubble_sorted_array1, bubble_sorted_array5) == 0);
    assert(check_arrays_equal(bubble_sorted_array1, bubble_sorted_array6) == 0);
    assert(check_arrays_equal(bubble_sorted_array3, bubble_sorted_array4) == 0);
    assert(check_arrays_equal(bubble_sorted_array3, bubble_sorted_array5) == 0);
    assert(check_arrays_equal(bubble_sorted_array3, bubble_sorted_array6) == 0);
    assert(check_arrays_equal(bubble_sorted_array4, bubble_sorted_array5) == 0);
    assert(check_arrays_equal(bubble_sorted_array4, bubble_sorted_array6) == 0);
    assert(check_arrays_equal(bubble_sorted_array5, bubble_sorted_array6) == 0);

    printf("All bubble sort visualiser tests passed\n");
}

// A unit test for selection sort visualiser
// Uses the check_arrays_equal function to check if the sorted array is correct
void test_selection_sort_visualiser() {
    int array1[] = {1, 2, 3, 4, 5};
    int array2[] = {4, 5, 3, 2, 1};
    int array3[] = {443232, 34, 25, 32, 41, 54};
    int array4[] = {4, 2, 329532, 4, 55};
    int array5[] = {34, 25, 32, 41, 54};
    int array6[] = {4, 2, 329532, 4, 55};
    int array7[] = {849, 33, 3434, 2221, 4234, 99};
    int array8[] = {};

    int array1_sorted[] = {1, 2, 3, 4, 5};
    int array2_sorted[] = {1, 2, 3, 4, 5};
    int array3_sorted[] = {25, 32, 34, 41, 54, 443232};
    int array4_sorted[] = {2, 4, 4, 55, 329532};
    int array5_sorted[] = {25, 32, 34, 41, 54};
    int array6_sorted[] = {2, 4, 4, 55, 329532};
    int array7_sorted[] = {849, 2221, 33, 99, 3434, 4234};
    int array8_sorted[] = {};

    int *selection_sorted_array1 = selection_sort_visualiser(array1);
    int *selection_sorted_array2 = selection_sort_visualiser(array2);
    int *selection_sorted_array3 = selection_sort_visualiser(array3);
    int *selection_sorted_array4 = selection_sort_visualiser(array4);
    int *selection_sorted_array5 = selection_sort_visualiser(array5);
    int *selection_sorted_array6 = selection_sort_visualiser(array6);
    int *selection_sorted_array7 = selection_sort_visualiser(array7);
    int *selection_sorted_array8 = selection_sort_visualiser(array8);

    assert(check_arrays_equal(selection_sorted_array1, array1_sorted) == 1);
    assert(check_arrays_equal(selection_sorted_array2, array2_sorted) == 1);
    assert(check_arrays_equal(selection_sorted_array3, array3_sorted) == 1);
    assert(check_arrays_equal(selection_sorted_array4, array4_sorted) == 1);
    assert(check_arrays_equal(selection_sorted_array5, array5_sorted) == 1);
    assert(check_arrays_equal(selection_sorted_array6, array6_sorted) == 1);
    assert(check_arrays_equal(selection_sorted_array7, array7_sorted) == 1);
    assert(check_arrays_equal(selection_sorted_array8, array8_sorted) == 1);
    
    assert(check_arrays_equal(selection_sorted_array1, selection_sorted_array2) == 1);
    assert(check_arrays_equal(selection_sorted_array1, selection_sorted_array3) == 0);
    assert(check_arrays_equal(selection_sorted_array1, selection_sorted_array4) == 0);
    assert(check_arrays_equal(selection_sorted_array1, selection_sorted_array5) == 0);
    assert(check_arrays_equal(selection_sorted_array1, selection_sorted_array6) == 0);
    assert(check_arrays_equal(selection_sorted_array3, selection_sorted_array4) == 0);
    assert(check_arrays_equal(selection_sorted_array3, selection_sorted_array5) == 0);
    assert(check_arrays_equal(selection_sorted_array3, selection_sorted_array6) == 0);
    assert(check_arrays_equal(selection_sorted_array4, selection_sorted_array5) == 0);
    assert(check_arrays_equal(selection_sorted_array4, selection_sorted_array6) == 0);

    printf("All selection sort visualiser tests passed\n");
}

// A unit test for insertion sort visualiser
// Uses the check_arrays_equal function to check if the sorted array is correct
void test_insertion_sort_visualiser() {
    int array1[] = {1, 2, 3, 4, 5};
    int array1[] = {1, 2, 3, 4, 5};
    int array2[] = {4, 5, 3, 2, 1};
    int array3[] = {443232, 34, 25, 32, 41, 54};
    int array4[] = {4, 2, 329532, 4, 55};
    int array5[] = {34, 25, 32, 41, 54};
    int array6[] = {4, 2, 329532, 4, 55};
    int array7[] = {849, 33, 3434, 2221, 4234, 99};
    int array8[] = {};

    int array1_sorted[] = {1, 2, 3, 4, 5};
    int array2_sorted[] = {1, 2, 3, 4, 5};
    int array3_sorted[] = {25, 32, 34, 41, 54, 443232};
    int array4_sorted[] = {2, 4, 4, 55, 329532};
    int array5_sorted[] = {25, 32, 34, 41, 54};
    int array6_sorted[] = {2, 4, 4, 55, 329532};
    int array7_sorted[] = {849, 2221, 33, 99, 3434, 4234};
    int array8_sorted[] = {};

    int *insertion_sorted_array1 = insertion_sort_visualiser(array1);
    int *insertion_sorted_array2 = insertion_sort_visualiser(array2);
    int *insertion_sorted_array3 = insertion_sort_visualiser(array3);
    int *insertion_sorted_array4 = insertion_sort_visualiser(array4);
    int *insertion_sorted_array5 = insertion_sort_visualiser(array5);
    int *insertion_sorted_array6 = insertion_sort_visualiser(array6);
    int *insertion_sorted_array7 = insertion_sort_visualiser(array7);
    int *insertion_sorted_array8 = insertion_sort_visualiser(array8);

    assert(check_arrays_equal(insertion_sorted_array1, array1_sorted) == 1);
    assert(check_arrays_equal(insertion_sorted_array2, array2_sorted) == 1);
    assert(check_arrays_equal(insertion_sorted_array3, array3_sorted) == 1);
    assert(check_arrays_equal(insertion_sorted_array4, array4_sorted) == 1);
    assert(check_arrays_equal(insertion_sorted_array5, array5_sorted) == 1);
    assert(check_arrays_equal(insertion_sorted_array6, array6_sorted) == 1);
    assert(check_arrays_equal(insertion_sorted_array7, array7_sorted) == 1);
    assert(check_arrays_equal(insertion_sorted_array8, array8_sorted) == 1);

    assert(check_arrays_equal(insertion_sorted_array1, insertion_sorted_array2) == 1);
    assert(check_arrays_equal(insertion_sorted_array1, insertion_sorted_array3) == 0);
    assert(check_arrays_equal(insertion_sorted_array1, insertion_sorted_array4) == 0);
    assert(check_arrays_equal(insertion_sorted_array1, insertion_sorted_array5) == 0);
    assert(check_arrays_equal(insertion_sorted_array1, insertion_sorted_array6) == 0);
    assert(check_arrays_equal(insertion_sorted_array3, insertion_sorted_array4) == 0);
    assert(check_arrays_equal(insertion_sorted_array3, insertion_sorted_array5) == 0);
    assert(check_arrays_equal(insertion_sorted_array3, insertion_sorted_array6) == 0);
    assert(check_arrays_equal(insertion_sorted_array4, insertion_sorted_array5) == 0);
    assert(check_arrays_equal(insertion_sorted_array4, insertion_sorted_array6) == 0);

    printf("All insertion sort visualiser tests passed\n");
}


int main(void) {
    test_check_arrays_equal();
    test_bubble_sort_visualiser();
    test_selection_sort_visualiser();
    printf("All sort tests passed\n");
    return 0;
}

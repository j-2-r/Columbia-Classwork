#include <stdio.h>
#include <string.h>
#include "quicksort.h"

/* Static (private to this file) function prototypes. */
static void swap(void *a, void *b, size_t size);
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*));
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*));

/**
 * Swaps the values in two pointers.
 *
 * Casts the void pointers to type (char *) and works with them as char pointers
 * for the remainder of the function. Swaps one byte at a time, until all 'size'
 * bytes have been swapped. For example, if ints are passed in, size will be 4
 * and this function will swap 4 bytes starting at a and b pointers.
 */
static void swap(void *a, void *b, size_t size) {

    char temp_bit;
    char *a_c = (char *)a;
    char *b_c = (char *)b;

    for (size_t i=0 ; i<size; i++){
        temp_bit = b_c[i];
        b_c[i] = a_c[i];
        a_c[i] = temp_bit;
    }
}
/**
 * Partitions array around a pivot, utilizing the swap function. Each time the
 * function runs, the pivot is placed into the correct index of the array in
 * sorted order. All elements less than the pivot should be to its left, and all
 * elements greater than or equal to the pivot should be to its right.
 */

static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*)) {
    char *A = (char*) array;
    void *p = A + (left * elem_sz);
    int s = left;

    for (int i = left + 1; i < right+1; i++) {
        if (cmp(A + (i * elem_sz), p) < 0) {
            s++;
            swap(A + (s * elem_sz), A + (i * elem_sz), elem_sz);
        }
    }

    // Finally, swap the pivot element with the element at partition index
    swap(A + (left * elem_sz), A + (s * elem_sz), elem_sz);

    // Return the partition index
    return s;
}
/**
 * Sorts with lomuto partitioning, with recursive calls on each side of the
 * pivot.
 * This is the function that does the work, since it takes in both left and
 * right index values.
 */
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*)) {
   
    // TODO
  
    if (left < right){
        int s = lomuto(array, left, right, elem_sz, cmp);
	quicksort_helper(array, left, s-1, elem_sz, cmp);
	quicksort_helper(array, s+1, right,elem_sz,cmp);
    }
}

int int_cmp(const void *a, const void *b){
    int *a_i = (int*)a;
    int *b_i = (int*)b;
    if (*a_i>*b_i){
        return 1;
    } else if(*a_i<*b_i){
        return -1;
    }else{
        return 0;
    }
}

int dbl_cmp(const void *a, const void *b){
    double *a_d = (double*)a;
    double *b_d = (double*)b;
    if(*a_d>*b_d){
        return 1;
    }else if(*a_d<*b_d){
        return -1;
    }else{
        return 0;
    }
}

int str_cmp(const void *a, const void *b){
    char **a_c = (char**)a;
    char **b_c = (char**)b;
    return strcmp(*a_c,*b_c);
}

void quicksort(void *array, size_t len, size_t elem_sz, int (*cmp) (const void*, const void*)){
    quicksort_helper(array, 0, len - 1, elem_sz, cmp);
}



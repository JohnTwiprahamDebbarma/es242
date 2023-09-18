#include <stdio.h>
// #include "test.h"


/*
 * Generate k-selections of a[0..n-1] in lexicographic order and call process_selection to process them.
 *
 * The array b[] will have enough space to hold k elements.
 * For a selection i1, ..., ik, you should set b[0] = a[i1], ..., b[k-1] = a[ik].
 * Selections should be generated in lexicographic order.
 * a[0..k-1] is the smallest selection and a[n-k..n-1] is the largest.
 */
void sort(int a[], int n)
{
    int i, j, temp;
    for (i = 0; i < n; i++){
        for (j = i+1; j < n; j++){
            if (a[i] > a[j]){
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

void process_selection(int b, int k)
{
    int i;
    sort(b);
    printf("Selection: ");
    for (i = 0; i < k; i++){
        printf("%d ", b[i]);
    }
    printf("\n");
}

void generate_selections(int a[], int n, int k, int b[], void (process_selection)(int b, int k)){
    for (int i = 0; i < k-1; i++){
        b[i] = a[i+j];
        for (int j = k-1; j <= n; j++){
            b[k-1] = a[j];
            process_selection(b, k);
    }
    return 0;
    }
}


/*
 * See Exercise 2 (a), page 94 in Jeff Erickson's textbook.
 * The exercise only asks you to count the possible splits.
 * In this assignment, you have to generate all possible splits into buf[]
 * and call process_split() to process them.
 * The dictionary parameter is an array of words, sorted in dictionary order.
 * nwords is the number of words in this dictionary.
 */
void generate_splits(const char *source, const char *dictionary[], int nwords, char buf[], void *data, void (*process_split(char buf[], void *data)))
{}

/*
 * Transform a[] so that it becomes the previous permutation of the elements in it.
 * If a[] is the first permutation, leave it unchanged.
 */
void previous_permutation(int a[], int n)
{}

/* Write your tests here. Use the previous assignment for reference. */

void main()
{
    int a[] = {1, 2, 3, 4};
    int b[3];
    generate_selections(a, 4, 3, b, int (process_selection)(int b, int k));

    return 0;
}

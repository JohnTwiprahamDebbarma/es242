#include <stdio.h>
#include "test.h"


/*
 * Generate k-selections of a[0..n-1] in lexicographic order and call process_selection to process them.
 *
 * The array b[] will have enough space to hold k elements.
 * For a selection i1, ..., ik, you should set b[0] = a[i1], ..., b[k-1] = a[ik].
 * Selections should be generated in lexicographic order.
 * a[0..k-1] is the smallest selection and a[n-k..n-1] is the largest.
 */
int generate_selections(int a[], int n, int k, int b[], void *data, void (*process_selection)(int *b, int k, void *data))
{
    for (int j = 0; j <= n; j++)
        for (int i = j; i < j + k; i++)
            b[i] = a[i];
        process_selection(b, k, data);

}

int process_selection(int *b, int k, void *data)
{
    int i;
    for (i = 0; i < k; i++)
        printf("%d ", b[i]);
    printf("\n");
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

int main()
{
    int a[] = {1, 2, 3, 4};
    int b[3];
    return generate_selections(a, 4, 3, b, NULL, process_selection);

    //return 0;
}

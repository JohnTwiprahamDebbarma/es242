#include <stdio.h>

// Function to sort an array in ascending order (selection sort)
void sort(int a[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

// Function to process a selection
void process_selection(int b[], int k) {
    int i;
    sort(b, k); // Sort the first k elements of b
    printf("Selection: ");
    for (i = 0; i < k; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");
}

// Recursive function to generate k-selections
void generate_selections(int a[], int n, int k, int b[], int b_index, void (*process_selection)(int[], int)) {
    if (k == 0) {
        // If k elements have been selected, process the selection
        process_selection(b, b_index);
        return;
    }

    for (int i = 0; i <= n - k; i++) {
        b[b_index] = a[i];
        generate_selections(a + i + 1, n - i - 1, k - 1, b, b_index + 1, process_selection);
    }
}

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(a) / sizeof(a[0]);
    int k = 4;
    int b[k];

    generate_selections(a, n, k, b, 0, process_selection);

    return 0;
}
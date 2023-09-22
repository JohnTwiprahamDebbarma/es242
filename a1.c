#include <stdio.h>

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

void process_selection(int b[], int k) {
    int i;
    sort(b, k);
    printf("Selection: ");
    for (i = 0; i < k; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");
}

void generate_selections(int a[], int n, int k, int b[], void *data, void (*process_selection)(int[], int)) {
    int *b_index = (int *)data;
    if (k == 0) {
        process_selection(b, b_index - b); // Calculate the number of elements using pointer subtraction
        return;
    }

    for (int i = 0; i <= n - k; i++) {
        *b_index = a[i];
        generate_selections(a + i + 1, n - i - 1, k - 1, b, b_index + 1, process_selection);
    }
}

int main() {
    int a[] = {1, 2, 3, 4, 5, 6};
    int b[3];
    generate_selections(a, 6, 3, b, b, process_selection); // Pass the pointer to b as the starting point
    return 0;
}

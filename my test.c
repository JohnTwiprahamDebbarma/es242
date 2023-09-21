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

void generate_selections(int a[], int n, int k, int b[], int b_index, void (*process_selection)(int[], int)) {
    if (k == 0) {
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
    int k = 3;
    int b[k];

    generate_selections(a, n, k, b, 0, process_selection);

    return 0;
}
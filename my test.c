#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Custom sorting function for sorting combinations
void customSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void generate_combinations(int a[], int n, int k, int b[], int start, int current, void *data, void (*process_combination)(int[], int, void *)) {
    if (current == k) {
        // Sort the combination before processing
        customSort(b, k);
        process_combination(b, k, data);
        return;
    }

    for (int i = start; i < n; i++) {
        b[current] = a[i];
        generate_combinations(a, n, k, b, i + 1, current + 1, data, process_combination);
    }
}

void process_selection(int combination[], int k, void *data) {
    // Print the sorted combination
    for (int i = 0; i < k; i++) {
        printf("%d ", combination[i]);
    }
    printf("\n");
}

void generate_selections(int a[], int n, int k, int b[], void *data, void (*process_selection)(int[], int, void *)) {
    generate_combinations(a, n, k, b, 0, 0, data, process_selection);
}

int main() {
    int n = 4; // Size of the array
    int k = 2; // Number of elements in each combination
    int a[] = {6,1,2,5}};
    int b[k]; // Buffer to store each combination

    generate_selections(a, n, k, b, NULL, process_selection);

    return 0;
}


// int main() {
//     int n = 4; // Size of the array
//     int k = 2; // Number of elements in each combination
//     int a[] = {1, 2, 3, 4};
//     int b[k]; // Buffer to store each combination

//     generate_selections(a, n, k, b, NULL, process_selection);

//     return 0;
// }



/* Write your tests here. Use the previous assignment for reference. */

typedef struct {
    int index;
    int err;
    int first;
} state_t;

static void test_selections_2165(int b[], int k, void *data)
{
    state_t *s = (state_t *)data;
    if (s->first) {
        s->err = 0;
        s->first = 0;
    }
    switch (s->index) {
    case 0:
        if ((b[0] != 2) || (b[1] != 1)) {
            s->err = 1;
        }
        break;
    case 1:
        if ((b[0] != 2) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 2:
        if ((b[0] != 2) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 3:
        if ((b[0] != 1) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 4:
        if ((b[0] != 1) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 5:
        if ((b[0] != 6) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
    ++(s->index);
}

void count_selections(int b[], int k, void *data)
{
    int *d = (int*)data;
    ++*d;
}

typedef struct {
    int b[100];
} selection_t;

void last_selection(int b[], int k, void *data)
{
    selection_t *s = (selection_t*)data;
    for (int i = 0; i < k; ++i) {
        s->b[i] = b[i];
    }
}

BEGIN_TEST(generate_selections) {
    int a[] = { 2, 1, 6, 5 };
    int b[10];
    state_t s2165 = { .index = 0, .err = 1, .first = 1 };
    generate_selections(a, 4, 2, b, &s2165, test_selections_2165);
    ASSERT(!s2165.err, "Failed on 2 1 6 5.");
    int c = 0;
    int aa[] = { 1, 5, 3, 0, 1, 12, 4, 3, 6, 6 };
    generate_selections(aa, 10, 5, b, &c, count_selections);
    ASSERT_EQ(c, 252, "Failed on 10C5.");

    selection_t s;
    generate_selections(aa, 10, 5, b, &s, last_selection);
    ASSERT_ARRAY_VALUES_EQ(s.b, 5, "Failed on last of 10C5.", 12, 4, 3, 6, 6);
} END_TEST


// int main() {
//     int a[] = {1, 5, 3, 0, 1, 12, 4, 3, 6, 6};
//     int b[10];
//     int count = 0;
//     generate_selections(a, 10, 5, b, 0, process_selection); // Removed the extra comma and set count to 0
//     return 0;
// }


int main()
{
    run_tests((test_t[]) {
            TEST(generate_selections),
            // TEST(generate_splits),
            // TEST(previous_permutation),
            0
        });
    return 0;
}
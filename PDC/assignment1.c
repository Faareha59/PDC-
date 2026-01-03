#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_array(float *arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        arr[i] = (float)rand() / RAND_MAX; // random float between 0 and 1
    }
}

int main() {
    size_t input_sizes[] = {
        100000, 500000, 1000000, 5000000, 10000000,
        20000000, 30000000, 40000000, 50000000
    };
    int num_sizes = sizeof(input_sizes) / sizeof(input_sizes[0]);

    printf("S. Num\tInput Size\tExecution Time (Sec)\n");

    for (int i = 0; i < num_sizes; i++) {
        size_t n = input_sizes[i];
        float *arr = (float *)malloc(n * sizeof(float));
        if (arr == NULL) {
            printf("%d\t%zu\tMemory allocation failed\n", i+1, n);
            continue;
        }

        clock_t start = clock();
        fill_array(arr, n);
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%d\t%zu\t%.6f\n", i+1, n, time_taken);

        free(arr);
    }

    return 0;
}
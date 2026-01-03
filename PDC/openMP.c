#include <stdio.h>
#include <omp.h>

int main() {
    omp_set_num_threads(4);
    int sum = 0;

    // reduction is used to calculate the sum
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= 1000; i++) {
        sum += i;
    }

    printf("Final sum: %d\n", sum);

    return 0;
}
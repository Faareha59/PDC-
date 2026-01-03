#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 10000

int arr[SIZE];
long long partSum[10];

struct data {
    int start;
    int end;
    int index;
};

void* findSum(void* arg) {
    struct data* d = (struct data*)arg;
    long long sum = 0;
    for(int i = d->start; i < d->end; i++) {
        sum += arr[i];
    }
    partSum[d->index] = sum;
    pthread_exit(NULL);
}

long long serialSum() {
    long long sum = 0;
    for(int i = 0; i < SIZE; i++) {
        sum += arr[i];
    }
    return sum;
}

long long parallelSum(int n) {
    pthread_t t[n];
    struct data d[n];
    int chunk = SIZE / n;

    for(int i = 0; i < n; i++) {
        d[i].start = i * chunk;
        d[i].end = (i == n - 1) ? SIZE : (i + 1) * chunk;
        d[i].index = i;
        pthread_create(&t[i], NULL, findSum, (void*)&d[i]);
    }

    for(int i = 0; i < n; i++) {
        pthread_join(t[i], NULL);
    }

    long long total = 0;
    for(int i = 0; i < n; i++) {
        total += partSum[i];
    }
    return total;
}

int main() {
    srand(time(0));

    for(int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100 + 1;
    }

    clock_t s1 = clock();
    long long sTotal = serialSum();
    clock_t e1 = clock();
    double stime = (double)(e1 - s1) / CLOCKS_PER_SEC;
    printf("Serial Sum = %lld\n", sTotal);
    printf("Serial Time = %.6f sec\n\n", stime);

    int threads[] = {4,5,10};

    for(int i = 0; i < 3; i++) {
        int n = threads[i];
        clock_t s2 = clock();
        long long pTotal = parallelSum(n);
        clock_t e2 = clock();
        double ptime = (double)(e2 - s2) / CLOCKS_PER_SEC;
        double speed = stime / ptime;

        printf("Threads: %d\n", n);
        printf("Parallel Sum = %lld\n", pTotal);
        printf("Parallel Time = %.6f sec\n", ptime);
        printf("Speedup = %.2fx\n\n", speed);
    }

    return 0;
}

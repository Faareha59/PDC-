#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <time.h>

#define NUM_SERVERS 3
#define NUM_CHUNKS 8
#define NUM_USERS 10

// Simulate delay
void wait(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000); // ms -> microseconds
#endif
}

int getRandomServer() {
    return rand() % NUM_SERVERS; // server 0,1,2
}

int main() {
    srand(time(NULL));

    printf("\n========================================\n");
    printf("   NETFLIX PARALLEL STREAMING DEMO\n");
    printf("========================================\n\n");

    printf("STEP 1: Load Balancer Assigning Users to Servers (Distributed System)\n");
    printf("--------------------------------------------------------------------\n");

    // DEMO 1: Load Balancer
#pragma omp parallel for num_threads(NUM_SERVERS)
    for (int user = 1; user <= NUM_USERS; user++) {
        int server = getRandomServer();

#pragma omp critical
        {
            printf("User %2d → Assigned to Server %d\n", user, server + 1);
        }

        wait(200);
    }

    printf("\n\nSTEP 2: Parallel Video Chunk Streaming (Parallel Computing)\n");
    printf("-----------------------------------------------------------\n");

    printf("Movie is divided into small chunks...\n\n");

#pragma omp parallel for num_threads(4)
    for (int chunk = 1; chunk <= NUM_CHUNKS; chunk++) {

        // each chunk is downloaded by a different thread (parallel)
        int thread_id = omp_get_thread_num();

#pragma omp critical
        {
            printf("Thread %d ↓ Downloading Chunk %d...\n", thread_id, chunk);
        }

        wait(300);

#pragma omp critical
        {
            printf("Thread %d ✓ Chunk %d Completed!\n", thread_id, chunk);
        }
    }

    printf("\n\nSTEP 3: Final Output\n");
    printf("---------------------\n");
    printf("✔ All users successfully connected to distributed servers.\n");
    printf("✔ All video chunks streamed in parallel with no buffering.\n");
    printf("✔ This is exactly how Netflix serves millions of users smoothly.\n");

    printf("\n========================================\n");
    printf("      DEMO COMPLETE — THANK YOU!\n");
    printf("========================================\n");

    return 0;
}

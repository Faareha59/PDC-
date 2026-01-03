#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Mutex for telescope
pthread_mutex_t telescope;

void* use_telescope(void* arg) {
    int id = *(int*)arg;

    // Astronaut wants to use telescope
    printf("Astronaut %d is waiting to use the telescope...\n", id);

    // Lock telescope
    pthread_mutex_lock(&telescope);
    printf("Astronaut %d is now using the telescope.\n", id);

    sleep(2); // simulate research time

    printf("Astronaut %d has finished using the telescope.\n", id);
    // Unlock telescope
    pthread_mutex_unlock(&telescope);

    return NULL;
}

int main() {
    pthread_t astronauts[5];
    int ids[5];

    // Initialize mutex
    pthread_mutex_init(&telescope, NULL);

    // Create astronaut threads
    for (int i = 0; i < 5; i++) {
        ids[i] = i + 1;
        pthread_create(&astronauts[i], NULL, use_telescope, &ids[i]);
    }

    // Wait for all astronauts
    for (int i = 0; i < 5; i++) {
        pthread_join(astronauts[i], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&telescope);

    return 0;
}

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank);

    if (rank == 0) {
        printf("\n--- Ride-Sharing Revenue Simulation (C + Open MPI) ---\n\n");
        char* zones[] = {"DHA", "Gulberg", "Johar Town", "Model Town"};
        int total = 0, revenue;

        for (int i = 1; i < size; i++) {
            MPI_Send(zones[i - 1], 20, MPI_CHAR, i, 10, MPI_COMM_WORLD);
        }

        for (int i = 1; i < size; i++) {
            MPI_Recv(&revenue, 1, MPI_INT, i, 20, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total += revenue;
            printf("Received revenue from Process %d → Rs %d\n", i, revenue);
        }

        printf("\n💰 Total City Revenue = Rs %d\n", total);
    } 
    else {
        char zone[20];
        MPI_Recv(zone, 20, MPI_CHAR, 0, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int rides = rand() % 11 + 5;
        int revenue = 0;
        for (int i = 0; i < rides; i++)
            revenue += (rand() % 601) + 200;

        sleep(rand() % 3 + 1);
        printf("Process %d (%s): %d rides → Rs %d\n", rank, zone, rides, revenue);
        MPI_Send(&revenue, 1, MPI_INT, 0, 20, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

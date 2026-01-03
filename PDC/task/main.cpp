#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    char name[100];
    int length;

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Get_processor_name(name, &length);

    std::cout << "Process " << world_rank << " of " << world_size
              << " running on " << name << std::endl;

    MPI_Finalize();
    return 0;
}

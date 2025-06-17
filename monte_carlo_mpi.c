// monte_carlo_mpi.c for sequential programming
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    long long int total_points = 1000000000;
    long long int local_count = 0, global_count = 0;
    double x, y;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get current process ID
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get total number of processes

    long long int points_per_process = total_points / size;
    unsigned int seed = rank + 1;  // Unique seed per process

    double start = MPI_Wtime();  // Start timer

    for (long long int i = 0; i < points_per_process; i++) {
        x = (double)rand_r(&seed) / RAND_MAX;
        y = (double)rand_r(&seed) / RAND_MAX;

        if (x * x + y * y <= 1.0)
            local_count++;
    }

    MPI_Reduce(&local_count, &global_count, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double end = MPI_Wtime();  // End timer

    if (rank == 0) {
        double pi_estimate = 4.0 * global_count / total_points;
        printf("MPI estimate of Pi = %.10f\n", pi_estimate);
        printf("Execution Time = %.4f seconds\n", end - start);
    }

    MPI_Finalize();
    return 0;
}

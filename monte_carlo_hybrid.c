// monte_carlo_hybrid.c - combines MPI (distributed memory) and OpenMP 
// (shared memory) to perform a highly efficient Monte Carlo simulation
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int rank, size;
    long long int total_points = 1000000000;
    long long int local_count = 0, global_count = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long int points_per_process = total_points / size;

    double start = MPI_Wtime();

    #pragma omp parallel reduction(+:local_count)
    {
        unsigned int seed = rank * 100 + omp_get_thread_num();
        #pragma omp for
        for (long long int i = 0; i < points_per_process; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;

            if (x * x + y * y <= 1.0)
                local_count++;
        }
    }

    MPI_Reduce(&local_count, &global_count, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double end = MPI_Wtime();

    if (rank == 0) {
        double pi_estimate = 4.0 * global_count / total_points;
        printf("Hybrid MPI+OpenMP estimate of Pi = %.10f\n", pi_estimate);
        printf("Execution Time = %.4f seconds\n", end - start);
    }

    MPI_Finalize();
    return 0;
}

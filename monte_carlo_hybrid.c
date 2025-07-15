#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int rank, size;
    long long int total_points, points_per_process;
    long long int local_count = 0, global_count = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0)
            printf("Usage: %s <total_points>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    total_points = atoll(argv[1]);
    points_per_process = total_points / size;

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
        double pi_error = fabs(M_PI - pi_estimate);
        double time_taken = end - start;

        printf("Total Points: %lld\n", total_points);
        printf("Hybrid MPI+OpenMP estimate of Pi = %.10f\n", pi_estimate);
        printf("Error = %.10f\n", pi_error);
        printf("Execution Time = %.4f seconds\n", time_taken);
    }

    MPI_Finalize();
    return 0;
}

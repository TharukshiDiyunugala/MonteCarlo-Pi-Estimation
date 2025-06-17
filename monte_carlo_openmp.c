// monte_carlo_openmp.c for parallel programming
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    long long int total_points = 1000000000;  // Number of random points
    long long int inside_circle = 0;
    double x, y;

    double start = omp_get_wtime();  // Start timer

    #pragma omp parallel private(x, y) reduction(+:inside_circle)
    {
        unsigned int seed = omp_get_thread_num();  // Thread-safe random seed
        #pragma omp for
        for (long long int i = 0; i < total_points; i++) {
            x = (double)rand_r(&seed) / RAND_MAX;
            y = (double)rand_r(&seed) / RAND_MAX;

            if (x * x + y * y <= 1.0)
                inside_circle++;
        }
    }

    double pi_estimate = 4.0 * inside_circle / total_points;
    double end = omp_get_wtime();  // End timer

    printf("OpenMP estimate of Pi = %.10f\n", pi_estimate);
    printf("Execution Time = %.4f seconds\n", end - start);
    return 0;
}

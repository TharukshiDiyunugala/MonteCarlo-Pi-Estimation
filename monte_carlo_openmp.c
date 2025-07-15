#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <total_points>\n", argv[0]);
        return 1;
    }

    long long int total_points = atoll(argv[1]);  
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
    double pi_error = fabs(M_PI - pi_estimate);
    double end = omp_get_wtime();  // End timer
    double time_taken = end - start;

    printf("Total Points: %lld\n", total_points);
    printf("OpenMP estimate of Pi = %.10f\n", pi_estimate);
    printf("Error = %.10f\n", pi_error);
    printf("Execution Time = %.4f seconds\n", time_taken);

    return 0;
}

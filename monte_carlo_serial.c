#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <total_points>\n", argv[0]);
        return 1;
    }

    long long int total_points = atoll(argv[1]);
    long long int inside_circle = 0;
    double x, y;

    srand(time(NULL));

    clock_t start = clock();  // start timer

    for (long long int i = 0; i < total_points; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        if (x * x + y * y <= 1.0)
            inside_circle++;
    }

    double pi_estimate = 4.0 * inside_circle / total_points;
    double pi_error = fabs(M_PI - pi_estimate);

    clock_t end = clock();  // end timer
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Total Points: %lld\n", total_points);
    printf("Pi Estimate: %.10f\n", pi_estimate);
    printf("Error: %.10f\n", pi_error);
    printf("Execution Time: %.4f seconds\n", time_taken);

    return 0;
}

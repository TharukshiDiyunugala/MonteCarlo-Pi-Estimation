// monte_carlo_serial.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Number of random points to simulate
    long long int total_points = 1000000000;  // 1 billion points for better performance test
    long long int inside_circle = 0;
    double x, y;

    // Seed the random number generator with current time
    srand(time(NULL));

    // Start measuring time
    clock_t start = clock();

    // Perform the Monte Carlo simulation
    for (long long int i = 0; i < total_points; i++) {
        x = (double)rand() / RAND_MAX;  // Random x in [0,1]
        y = (double)rand() / RAND_MAX;  // Random y in [0,1]

        // Check if the point (x, y) lies inside the unit circle
        if (x * x + y * y <= 1.0)
            inside_circle++;
    }

    // Estimate the value of Pi
    double pi_estimate = 4.0 * inside_circle / total_points;

    // End measuring time
    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    // Print results
    printf("Serial estimate of Pi = %.10f\n", pi_estimate);
    printf("Execution Time = %.4f seconds\n", time_taken);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>// for seeding random numbers for current time

int main(){
	long num_points = 100000000; //100 million random points will be generated
	long inside_circle = 0;
	double x,y:

	srand(time(NULL));//set the seed for randomness

	for(long i =0; i < num_points; i++){
		x = (double)rand()/RAND_MAX;//generate random numbers
		Y = (double)rand()/RAND_MAX;

		if(x*x + y*y <= 1.0)
			inside_circle++;
	}
	
	double pi = 4.0 * inside_circle / num_points;
	printf("Estimated Pi = %f\n" , pi);
	return 0;
)

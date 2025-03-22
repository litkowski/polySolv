#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum iteration_method {BISECTION, SECANT, FIXED};
void iterate_bisect (double a, double b, double coeffs[], int iteration);
void iterate_secant (double x0, double x1, double coeffs[], int iteration);
void iterate_fixed (double x, int iteration);
double calc_poly (double x, double coeffs[]);
int degree;
int steps;

int main (int argc, char* argv[]) {

	enum iteration_method method;

	/* Extract the user's preferred iteration method */
	if (*argv[1] == 'b') {
		method = BISECTION;
	} else if (*argv[1] == 's') {
		method = SECANT;
	} else if (*argv[1] == 'f') {
		method = FIXED;
	}

	/*
	 * NOTE: For the bisection method, [a, b] is the interval of interest
	 * For the secant method, x0 = a and x1 = b
	 */
	double a;
	double b;
	a = atof(argv[2]);
	b = atof(argv[3]);

	/*
	 * Extract the number of steps
	 */
	steps = atoi(argv[4]);
	degree = argc - 6;
	double coeffs[degree + 1];

	/*
	 * Iterate through the remaining arguments and pass them to the coefficient array
	 */
	for (int i = 0; i <= degree; i++) {
		coeffs[i] = atof(argv[(degree - i) + 5]);
	}

	/*
	 * Initiate approximation
	 */
	if (method == BISECTION) {
		printf("Performing bisection method on interval of interest [%f, %f]\n", a, b);
		iterate_bisect(a, b, coeffs, 1);
	} else if (method == SECANT) {
		printf("Performing secant method with initial points x0 = %f, x1 = %f\n", a, b);
		iterate_secant(a, b, coeffs, 1);
	} else if (method == FIXED) {
		iterate_fixed(a, 1);
	}

}

/*
 * Calculate the steps needed from the bisection method to

int calc_steps_bisection () {
	double

	printf("Steps required to be correct to %d decimal places:" );
} */

void iterate_fixed (double x, int iteration) {

	double next = (x / 2) + (1 / pow(x, 3));
	printf("ITERATION %d : x = %f \n", iteration, x);

	if (iteration != steps) {
		iterate_fixed(next, iteration  +1);
	}
}

/*
 * Perform a bisection method iteration and print the results.
 */
void iterate_bisect (double a, double b, double coeffs[], int iteration) {

	double midpoint = (a + b) / 2;
	double approx = calc_poly(midpoint, coeffs);
	printf("ITERATION %d : x = %.20f, f(x) = %.20f \n", iteration, midpoint, approx);

	if (approx > 0) {
		b = midpoint;
	} else {
		a = midpoint;
	}

	if (iteration != steps) {
		iterate_bisect(a, b, coeffs, iteration + 1);
	}
}

/*
 * Perform a secant method iteration and print the results
 */
void iterate_secant (double x0, double x1, double coeffs[], int iteration) {

	double f_x1 = calc_poly(x1, coeffs);
	double f_x0 = calc_poly(x0, coeffs);

	double x2 = x1 - (f_x1 * ((x1 - x0) / (f_x1 - f_x0)));
	printf("ITERATION %d : x_n = %.20f, f(x_n-1) = %.20f \n", iteration, x1, f_x1);

	if (iteration != steps) {
		iterate_secant(x1, x2, coeffs, iteration + 1);
	}
}

/*
void iterate_fixed (double x, double coeffs[], int iteration) {

	double next = calc_poly(x, coeffs);
	printf("ITERATION %d : f(x) = %0.15f \n", iteration, next);

	if (iteration != steps) {
		iterate_fixed(next, coeffs, iteration + 1);
	}
}
*/

/*
 * Calculate the value of the polynomial determined by coeffs[] at point x
 */
double calc_poly (double x, double coeffs[]) {

	double sum = 0;

	for (int i = 0; i <= degree; i++) {
		double term_val = pow(x, (double) i);
		term_val *= coeffs[i];
		sum += term_val;
	}

	return sum;
}

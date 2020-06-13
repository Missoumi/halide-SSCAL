#include "Halide.h"
#include <stdio.h>
#include <stdlib.h>

using namespace Halide;

Halide::Func SSCAL(int a,Halide::Buffer<int> input, int incx) {
    Halide::Var x;
    Halide::Func sscal("SSCAL");
    Halide::Expr e = select(x%incx != 0 ,input(x) , input(x) * a);
    sscal(x) = print(e, "<- this is the output when x= ", input(x));
    sscal.parallel(x);
    return sscal;
}

int * SSCAL_C(int n, int a,int x[], int incx){
	// allocate memory for result table
	int *result = (int*) malloc(n * sizeof(int));
	for (int i=0; i<n; i++) {
		if (i%incx==0){
			result[i] = x[i]*a;
		}else {
			result[i] = x[i];
		}
	}
	return result;

}


int main(int argc, char **argv) {
	int a = 2;
	int incx = 2;
	int n = 11;
	int x[] = {0,1,2,3,4,5,6,7,8,1999, 1998};
	
	// create input for Halide Fun
	Halide::Buffer<int> input = Halide::Buffer<int>(x); 
	Halide::Func sscal = SSCAL(a, input, incx); 
	// run Halide Fun
	printf("Evaluating SSCAL halide version\n");
	Buffer<int> output = sscal.realize(input.width()); 

	// run C function
	int *result = 	SSCAL_C(n, a, x, incx);
	printf("\n\nEvaluating SSCAL c version\n");
	for (int i=0; i<n; i++) {
		printf("%d <- this is the output when x= %d\n", result[i], x[i]);
	}

	// Comparring result
	printf("\ncomparring halide and c version of SSCAl\n");
	for (int i=0; i<n; i++) {
		if (result[i] != output(i)	){
			return -1;
		}
	}
	printf("Success!\n");

	return 0;
}

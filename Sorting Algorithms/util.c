#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "util.h"


// print: Integer[] -> void
// Obj.: prints the whole array into the screen
void print(int arr[], int size){
	for(int i=0; i<size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}


// printhl: Integer[], Integer, Integer -> void
// Obj.: print array from index lo to index hi(including)
void printhl(int arr[], int lo, int hi){
	for(int i=lo; i<=hi; i++)
		printf("%d ", arr[i]);
	printf("\n");
}



// isCrescent: Integer[], Integer -> Integer
// obj.: checks if an array is sorted in crescent order. 
// returns true(1) if it is, false(0) if it isn't
int isCrescent(int arr[], int size){
	for(int i=1; i<size; i++){
		if(arr[i-1] > arr[i])
			return 0;
	}
	return 1;
}


// errorLogger: Integer[], Integer -> Integer
// obj.: checks if an array is sorted in crescent order. If it isn't it logs the errors and the positions which they occurr
// returns the number of errors
int errorLogger(int arr[], int size){
	int errors=0;
	for(int i=1; i<size; i++){
		if(arr[i-1] > arr[i]){
			printf("%d and %d, @ %d and %d\n", arr[i-1], arr[i], i-1, i);
			errors++;
		}
	}
	return errors;
}


//uses typedef void (SORTING_FUNCTION)(int*, int); function type definition (may use another you prefer, but you must change the sorting function type in util.h)

// stressTest: SORTING_FUNCTION, Integer[], Integer, const long Integer -> Integer
// tests provided sorting function on a random array of length size up to MAX_TESTS times
// if MAX_TESTS is 0, it tests until a failure occurs or the user force closes the program
// if it fails, the errors are logged (see errorLogger function)
int stressTest(SORTING_FUNCTION *sorting_function, int arr[], int size, const unsigned long int MAX_TESTS){
	unsigned long int counter = 0;
	char errors = 0;
	do{
		for(int a = size-1; a >= 0; a--)
			arr[a] = rand();

			clock_t beg = clock();
			(*sorting_function)(arr, size);
			clock_t delta = clock() - beg;
			
			if((errors = errorLogger(arr, size)) == 0){
				counter++;
				printf("sort #%ld runtime (new): %lf\n", counter, (double)delta/CLOCKS_PER_SEC);
			}else{
				printf("%d ERRORS ON SORTING!\n", errors);
				return -1;
			}
	}while(errors == 0 && MAX_TESTS == 0 || MAX_TESTS >= counter);
	return 0;
}

// unlimitedStressTest: SORTING_FUNCTION, Integer[], Integer -> Integer
// calls stressTest with 0 as the last argument.
// it's a special case of stessTest where the algorithm runs until
// a faliure occurs or until the user force closes it
int unlimitedStressTest(SORTING_FUNCTION *sorting_function, int arr[], int size){
	stressTest(sorting_function, arr, size, 0);
}
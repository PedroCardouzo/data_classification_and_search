#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Sorting Algorithms/quicksort.h"

#define SIZE_MAX 10000000
#define INPUT_FILENAME "randomnumbers.bin"
#define OUTPUT_FILENAME "R00275739-.txt"

// error log:
// 0: program finished as expected
// 1: couldn't open/find input file
// 2: couldn't read from input file
// 3: output file already exists and you don't want to overwrite it
// 4: couldn't open/create output file

typedef void (SORTING_FUNCTION)(int*, int);

int benchmark(SORTING_FUNCTION *sorting_function, int array[], int size, const char* sort_id, char arr_id);
int appendToOutput(char *string, char *filename);
int exists(const char *fname);

int comps;
int swaps;

int main(){
	unsigned int *arr_random, *arr_crescent, *arr_decrescent, *arr_aux;
	arr_random = (int*) malloc(SIZE_MAX*sizeof(int));
	arr_crescent = (int*) malloc(SIZE_MAX*sizeof(int));
	arr_decrescent = (int*) malloc(SIZE_MAX*sizeof(int));
	arr_aux = (int*) malloc(SIZE_MAX*sizeof(int));

	FILE *input = fopen(INPUT_FILENAME, "rb");
	if(!input){
		printf("Error! Couldn't open or find %s in current directory!\n", INPUT_FILENAME);
		return 1;
	}else{
		if(fread(arr_random, sizeof(int), SIZE_MAX, input) == SIZE_MAX)
			printf("File reading was successful!\n");
		else{
			printf("Fail on file reading\n");
			return 2;
		}
		fclose(input);
	}
	memcpy((void *)arr_crescent, (void *)arr_random, SIZE_MAX*sizeof(int));
	quicksort(arr_crescent, SIZE_MAX); // arr_crescent recieves the crescent ordered version of arr_random

	for(int i=0; i < SIZE_MAX; i++)
		arr_decrescent[i] =  arr_crescent[SIZE_MAX-1-i]; // arr_decrescent recieves the decrescent ordered version of arr_random

	// open output file

	if(exists(OUTPUT_FILENAME)){
		printf("The file %s already exists.\nDo you want to overwrite it? (y for yes)", OUTPUT_FILENAME);
		char overwrite = 0;
		scanf(" %c", &overwrite);

		if(overwrite == 'y') 
			remove(OUTPUT_FILENAME);
		else
			return 3;
	}
	FILE *output = fopen(OUTPUT_FILENAME, "a");
	if(output == NULL){
		printf("Fail on opening/creating output file\n");
		return 4;
	}else
		fclose(output); // file will be opened each time we write a line to it, so we can close it now
		

	// now benchmark the functions

	// quicksort (QukS)
		// Random
		for(int i=1000; i <= 10000000; i*=10){
			memcpy((void *)arr_aux, (void *)arr_random, SIZE_MAX*sizeof(int));
			benchmark(quicksort, arr_aux, i, "QukS", 'R');
		}
/* when i fix the order i can put this back
		// Crescent
		for(int i=1000; i <= 10000000; i*=10){
			memcpy((void *)arr_aux, (void *)arr_crescent, SIZE_MAX*sizeof(int));
			benchmark(quicksort, arr_aux, i, "QukS", 'O');
		}
		// decrescent
		for(int i=1000; i <= 10000000; i*=10){
			memcpy((void *)arr_aux, (void *)arr_decrescent, SIZE_MAX*sizeof(int));
			benchmark(quicksort, arr_aux, i, "QukS", 'I');
		}

*/
	free(arr_random);
	free(arr_crescent);
	free(arr_decrescent);
	free(arr_aux);
	return 0;
}

// benchmark: SORTING_FUNCTION, Integer[], Integer, String, Char -> Integer
// evaluates a sorting function and returns a string with its benchmark, of the following format:
// "sort_id, arr_id, size of array, number of swaps, number of comparisons, elapsed time"
// the returned value a Integer where 0 is successful and any other number is a error code
int benchmark(SORTING_FUNCTION *sorting_function, int array[], int size, const char* sort_id, char arr_id){
	comps = 0;
	swaps = 0;
	clock_t delta = clock();
	(*sorting_function)(array, size); // run the sorting function on the array of length size
	delta = clock()-delta; // difference between clocks from before and after the function
	int time = delta/(CLOCKS_PER_SEC/1000);

	if(isCrescent(array, size)) // checks if the array was successfuly sorted in O(n)
		printf("Sorting Successful!\n");
	else
		printf("ERROR! SORTING FAILED!\n");

	char *result = (char *) malloc(sizeof(char)*100);
	sprintf(result, "%s, %c, %d, %d, %d, %d.\n", sort_id, arr_id, size, swaps, comps, time);
	
	int status = appendToOutput(result, OUTPUT_FILENAME);
	free(result);
	return status;
	
}

int appendToOutput(char *string, char *filename){
	FILE *output = fopen(filename, "a");
	if(output==NULL){
		printf("ERROR OPENING %s\n", filename);
		return -1;
	}else{
		// fseek(output, 0, SEEK_END);
		if(fprintf(output, "%s", string) < 0)
			printf("ERROR WRITING TO  %s\n", filename);
		return -2;
	}
	fclose(output);
	return 0;
}

// exists: String -> Boolean
// returns true(1) if file exists, false(0) otherwise
int exists(const char *fname){
	FILE *file = fopen(fname, "r+");
	if(file){
		fclose(file);
		return 1;
	}else
		return 0;
}
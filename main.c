/*********************************************************
 * This program benchmarks sorting algorithms            *
 * Take a look at main.h for documentation aswell        *
 * The output file is defined at OUTPUT_FILENAME         *
 * The output format is :                                *
 * 	sort_id, array_type, size, swaps, comparisons, time  *
 *********************************************************/
// ## -> to erase
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//for interruption
#include <signal.h>
#include <unistd.h>

#include "Sorting Algorithms/util.h"

#include "Sorting Algorithms/binaryInsertionSort.h"
#include "Sorting Algorithms/linearInsertionSort.h"
#include "Sorting Algorithms/selectionSort.h"
#include "Sorting Algorithms/bubbleSort.h"


#include "Sorting Algorithms/quicksort.h"
#include "Sorting Algorithms/mergesort.h"
#include "Sorting Algorithms/heapsort.h"
#include "Sorting Algorithms/timsort.h"

#include "main.h"

char OVERTIME_FLAG;
unsigned long int comps;
unsigned long int swaps;

unsigned int *arr_random, *arr_crescent, *arr_decrescent, *arr_aux;

	
int main(){

	// allocating space for the arrays
	arr_random = (int*) malloc(SIZE_MAX*sizeof(int));
	arr_crescent = (int*) malloc(SIZE_MAX*sizeof(int));
	arr_decrescent = (int*) malloc(SIZE_MAX*sizeof(int));
	arr_aux = (int*) malloc(SIZE_MAX*sizeof(int));


	// checks if the input file exists, if it does, read its information into arr_random
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
	// create arrays (random, ordered, unordered)
	memcpy((void *)arr_crescent, (void *)arr_random, SIZE_MAX*sizeof(int));
	quicksort(arr_crescent, SIZE_MAX); // arr_crescent recieves the crescent ordered version of arr_random

	for(int i=0; i < SIZE_MAX; i++)
		arr_decrescent[i] =  arr_crescent[SIZE_MAX-1-i]; // arr_decrescent recieves the decrescent ordered version of arr_random

	// open output file
	if(exists(OUTPUT_FILENAME)){
		printf("The file %s already exists.\nDo you want to overwrite it? (y for yes) ", OUTPUT_FILENAME);
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
		
	// get time interruption ready 
	signal(SIGALRM, set_OVERTIME_FLAG);
	

	// now we benchmark all functions

	fullBenchmark(quicksort, "QukS");
	fullBenchmark(mergesort, "MerS");
	fullBenchmark(heapsort, "HepS");
	fullBenchmark(timsort, "TimS");
	fullBenchmark(binaryInsertionSort, "ISBB");

	free(arr_random);
	free(arr_crescent);
	free(arr_decrescent);
	free(arr_aux);
	return 0;
}

int fullBenchmark(SORTING_FUNCTION *sorting_function, const char* sort_id){
	// benchmark the functions

	// random
	for(int i=1000; i <= SIZE_MAX; i*=10){
		memcpy((void *)arr_aux, (void *)arr_random, SIZE_MAX*sizeof(int));
		benchmark(sorting_function, arr_aux, i, sort_id, 'R');
	}

	// crescent
	for(int i=1000; i <= SIZE_MAX; i*=10){
		memcpy((void *)arr_aux, (void *)arr_crescent, SIZE_MAX*sizeof(int));
		benchmark(sorting_function, arr_aux, i, sort_id, 'O');
	}

	// decrescent
	for(int i=1000; i <= SIZE_MAX; i*=10){
		memcpy((void *)arr_aux, (void *)arr_decrescent, SIZE_MAX*sizeof(int));
		benchmark(sorting_function, arr_aux, i, sort_id, 'I');
	}
}

// benchmark: SORTING_FUNCTION, Integer[], Integer, String, Char -> Integer
// evaluates a sorting function and returns a string with its benchmark, of the following format:
// "sort_id, arr_id, size of array, number of swaps, number of comparisons, elapsed time"
// the returned value a Integer where 0 is successful and any other number is a error code
int benchmark(SORTING_FUNCTION *sorting_function, int array[], int size, const char* sort_id, char arr_id){
	OVERTIME_FLAG = 0;
	comps = 0;
	swaps = 0;
	
	clock_t delta = clock();
	
	alarm(TIME_LIMIT); // sets a time interruption in TIME_LIMIT seconds
	
	(*sorting_function)(array, size); // run the sorting function on the array of length size
	
	alarm(0); // clears time interruption timer

	delta = clock()-delta; // difference between clocks from before and after the function
	int time = delta/(CLOCKS_PER_SEC/1000);

	if(OVERTIME_FLAG)
		printf("Sorting Took Too Long (more than %d seconds)\n", TIME_LIMIT);

	else if(isCrescent(array, size)) // checks if the array was successfuly sorted in O(n)
		printf("Sorting Successful!\n");

	else
		printf("ERROR! SORTING FAILED!\n");

	char *result = (char *) malloc(sizeof(char)*100);
	if(OVERTIME_FLAG == 0)
		sprintf(result, "%s, %c, %u, %lu, %lu, %u.\n", sort_id, arr_id, size, swaps, comps, time);
	else
		sprintf(result, "%s, %c, %u, *, *, *.\n", sort_id, arr_id, size);
	
	int status = appendToOutput(result, OUTPUT_FILENAME);
	free(result);
	return status;
	
}

// appendToOutput: String String -> int
// obj.: appends the string to the end of the file with name filename
int appendToOutput(char *string, char *filename){
	FILE *output = fopen(filename, "a");
	if(output==NULL){
		printf("ERROR OPENING %s\n", filename);
		return -1;
	}else{
		// fseek(output, 0, SEEK_END);
		if(fprintf(output, "%s", string) < 0){
			printf("ERROR WRITING TO  %s\n", filename);
			return -2;
		}
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


// set_OVERTIME_FLAG: void -> void
// obj.: sets OVERTIME_FLAG to 1 (true), that means that the algorithm was running for more than TIME_LIMIT seconds
void set_OVERTIME_FLAG(){
	OVERTIME_FLAG = 1;
	return;
}
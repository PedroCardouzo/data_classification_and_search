/*********************************************************
 * Software developed by                                 *
 * Pedro Cardouzo and Luma Beserra                       *
 * This program benchmarks sorting and search algorithms *
 * Take a look at main.h and Readme.md for documentation *
 * The output file is defined at OUTPUT_FILENAME         *
 * The output format is :                                *
 * 	sort_id, array_type, size, swaps, comparisons, time  *
 *********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// for interruption
#include <signal.h>
#include <unistd.h>

// sorting algorithms
#include "Sorting Algorithms/util.h"

#include "Sorting Algorithms/linearInsertionSort.h"
#include "Sorting Algorithms/binaryInsertionSort.h"
#include "Sorting Algorithms/selectionSort.h"
#include "Sorting Algorithms/bubbleSort.h"

#include "Sorting Algorithms/combsort.h"
#include "Sorting Algorithms/shellsort.h"
#include "Sorting Algorithms/quicksort.h"
#include "Sorting Algorithms/mergesort.h"
#include "Sorting Algorithms/heapsort.h"
#include "Sorting Algorithms/timsort.h"

// search algorithms
#include "Search Algorithms/linearSearch.h"
#include "Search Algorithms/binarySearch.h"

#include "main.h"

char OVERTIME_FLAG;
unsigned long int comps;
unsigned long int swaps;

unsigned int *A0, *A1, *A2, *arr_aux;

// see main.h for consise documentation
int main(){

	// allocating space for the arrays
	A0 = (int*) malloc(SIZE_MAX*sizeof(int));
	A1 = (int*) malloc(SIZE_MAX*sizeof(int));
	A2 = (int*) malloc(SIZE_MAX*sizeof(int));
	arr_aux = (int*) malloc(SIZE_MAX*sizeof(int));


	// checks if the input file exists, if it does, read its information into A0
	FILE *input = fopen(INPUT_FILENAME, "rb");
	if(!input){
		printf("Error! Couldn't open or find %s in current directory!\n", INPUT_FILENAME);
		return 1;
	}else{
		if(fread(A0, sizeof(int), SIZE_MAX, input) == SIZE_MAX)
			printf("File reading was successful!\n");
		else{
			printf("Fail on file reading\n");
			return 2;
		}
		fclose(input);
	}
	// create output file
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
	

	// create arrays (random, ordered, unordered)
	memcpy((void *)A1, (void *)A0, SIZE_MAX*sizeof(int));
	quicksort(A1, SIZE_MAX); // A1 recieves the crescent ordered version of A0

	for(int i=0; i < SIZE_MAX; i++)
		A2[i] =  A1[SIZE_MAX-1-i]; // A2 recieves the decrescent ordered version of A0

		
	// get time interruption ready 
	signal(SIGALRM, set_OVERTIME_FLAG);
	

	// now we benchmark all functions
	printf("ISBL:\n");
	fullBenchmark(linearInsertionSort, "ISBL");
	printf("ISBB:\n");
	fullBenchmark(binaryInsertionSort, "ISBB");
	printf("SelS:\n");
	fullBenchmark(selectionSort, "SelS");
	printf("BubS:\n");
	fullBenchmark(bubbleSort, "BubS");
	printf("CbSt:\n");
	fullBenchmark(combsort, "CbSt");
	printf("SheS:\n");
	fullBenchmark(shellsort, "SheS");
	printf("QukS:\n");
	fullBenchmark(quicksort, "QukS");
	printf("MerS:\n");
	fullBenchmark(mergesort, "MerS");
	printf("HepS:\n");
	fullBenchmark(heapsort, "HepS");
	printf("TimS:\n");
	fullBenchmark(timsort, "TimS");

	searchBenchmark(); // benchmarks linear search and binary search for VALUE_TO_BE_SEARCHED element

	free(A0);
	free(A1);
	free(A2);
	free(arr_aux);
	return 0;
}

// searchBenchmark: void -> void
// obj.: benchmarks linearSearch and binarySearch functions
void searchBenchmark(){
	comps = 0;
	swaps = 0;
	int index;
	
	clock_t delta = clock();

	// benchmark linearSearch
	index = linearSearch(A1, SIZE_MAX, VALUE_TO_BE_SEARCHED);

	delta = clock()-delta; // difference between clocks from before and after the function
	int time = delta/(CLOCKS_PER_SEC/1000);
	
	char *result = (char *) malloc(sizeof(char)*100);
	if(index != -1 && A1[index] == VALUE_TO_BE_SEARCHED){
		sprintf(result, "BLin, O, %u, %lu, %lu, %u.\n", SIZE_MAX, swaps, comps, time);
		printf("Linear Search for the element %d was successful!\n", VALUE_TO_BE_SEARCHED);
	}else{
		sprintf(result, "Elemento %d não está no array fornecido ou o algoritmo está errado", VALUE_TO_BE_SEARCHED);
		printf("***ERROR*** Element %d wasn't found!\n", VALUE_TO_BE_SEARCHED);
	}
	
	appendToOutput(result, OUTPUT_FILENAME);

	comps = 0;
	swaps = 0;

	delta = clock();
	index = binarySearch(A1, SIZE_MAX, VALUE_TO_BE_SEARCHED);
	delta = clock()-delta;
	time = delta/(CLOCKS_PER_SEC/1000);

	if(index != -1 && A1[index] == VALUE_TO_BE_SEARCHED){
		sprintf(result, "Bbin, O, %u, %lu, %lu, %u.\n", SIZE_MAX, swaps, comps, time);
		printf("Binary Search for the element %d was successful!\n", VALUE_TO_BE_SEARCHED);
	}else{
		sprintf(result, "Elemento %d não está no array fornecido ou o algoritmo está errado", VALUE_TO_BE_SEARCHED);
		printf("***ERROR*** Element %d wasn't found!\n", VALUE_TO_BE_SEARCHED);
	}
	appendToOutput(result, OUTPUT_FILENAME);
}

// fullBenchmark: SORTING_FUNCTION, const char* -> void
// obj.: benchmarks the recieved sorting_function in random, 
// crescent and decrescent array (using benchmark function)
void fullBenchmark(SORTING_FUNCTION *sorting_function, const char* sort_id){
	// benchmark the functions

	// random
	for(int i=1000; i <= SIZE_MAX; i*=10){
		memcpy((void *)arr_aux, (void *)A0, SIZE_MAX*sizeof(int));
		benchmark(sorting_function, arr_aux, i, sort_id, 'R');
	}

	// crescent
	for(int i=1000; i <= SIZE_MAX; i*=10){
		memcpy((void *)arr_aux, (void *)A1, SIZE_MAX*sizeof(int));
		benchmark(sorting_function, arr_aux, i, sort_id, 'O');
	}

	// decrescent
	for(int i=1000; i <= SIZE_MAX; i*=10){
		memcpy((void *)arr_aux, (void *)A2, SIZE_MAX*sizeof(int));
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
/*********************************************************
 * Software developed by                                 *
 * Pedro Cardouzo and Luma Beserra                       *
 * This program benchmarks sorting and search algorithms *
 * Take a look at main.h for documentation               *
 * The output file is defined at OUTPUT_FILENAME         *
 * The output format is :                                *
 * 	sort_id, array_type, size, swaps, comparisons, time  *
 *********************************************************/

#define SIZE_MAX 10000000
#define INPUT_FILENAME "randomnumbers.bin"
#define OUTPUT_FILENAME "R00275739-00268612.txt"
#define TIME_LIMIT 3600 // time is in seconds
#define VALUE_TO_BE_SEARCHED 1438215

// error log:
// 0: program finished as expected
// 1: couldn't open/find input file
// 2: couldn't read from input file
// 3: output file already exists and you don't want to overwrite it
// 4: couldn't open/create output file

typedef void (SORTING_FUNCTION)(int*, int);



// fullBenchmark: SORTING_FUNCTION, const char* -> void
// obj.: benchmarks the recieved sorting_function in random, 
// crescent and decrescent array (using benchmark function)
void fullBenchmark(SORTING_FUNCTION *sorting_function, const char* sort_id);

// benchmark: SORTING_FUNCTION, Integer[], Integer, String, Char -> Integer
// evaluates a sorting function and returns a string with its benchmark, of the following format:
// "sort_id, arr_id, size of array, number of swaps, number of comparisons, elapsed time"
// the returned value a Integer where 0 is successful and any other number is a error code
int benchmark(SORTING_FUNCTION *sorting_function, int array[], int size, const char* sort_id, char arr_id);

// searchBenchmark: void -> void
// obj.: benchmarks linearSearch and binarySearch functions
void searchBenchmark();

// appendToOutput: String String -> int
// obj.: appends the string to the end of the file with name filename
int appendToOutput(char *string, char *filename);

// exists: String -> Boolean
// returns true(1) if file exists, false(0) otherwise
int exists(const char *fname);

// set_OVERTIME_FLAG: void -> void
// obj.: sets OVERTIME_FLAG to 1 (true), that means that the algorithm was running for more than TIME_LIMIT seconds
void set_OVERTIME_FLAG();

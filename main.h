#define SIZE_MAX 10000000
#define INPUT_FILENAME "randomnumbers.bin"
#define OUTPUT_FILENAME "R00275739-00268612.txt"
#define TIME_LIMIT 5 // time is in seconds

// error log:
// 0: program finished as expected
// 1: couldn't open/find input file
// 2: couldn't read from input file
// 3: output file already exists and you don't want to overwrite it
// 4: couldn't open/create output file

typedef void (SORTING_FUNCTION)(int*, int);



int fullBenchmark(SORTING_FUNCTION *sorting_function, const char* sort_id);
int benchmark(SORTING_FUNCTION *sorting_function, int array[], int size, const char* sort_id, char arr_id);
int appendToOutput(char *string, char *filename);
int exists(const char *fname);
void set_OVERTIME_FLAG();
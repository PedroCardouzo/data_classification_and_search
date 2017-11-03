// sorting function type
typedef void (SORTING_FUNCTION)(int*, int);

// print: Integer[] -> void
// Obj.: prints the whole array into the screen
void print(int arr[], int size);

// printhl: Integer[], Integer, Integer -> void
// Obj.: print array from index lo to index hi(including)
void printhl(int arr[], int lo, int hi);

// isCrescent: Integer[], Integer -> Integer
// obj.: checks if an array is sorted in crescent order. 
// returns true(1) if it is, false(0) if it isn't
int isCrescent(int arr[], int size);

// errorLogger: Integer[], Integer -> Integer
// obj.: checks if an array is sorted in crescent order. If it isn't it logs the errors and the positions which they occurr
// returns the number of errors
int errorLogger(int arr[], int size);

typedef void (SORTING_FUNCTION)(int*, int);
int stressTest(SORTING_FUNCTION *sorting_function, int arr[], int size, const unsigned long int MAX_TESTS);
int unlimitedStressTest(SORTING_FUNCTION *sorting_function, int arr[], int size);


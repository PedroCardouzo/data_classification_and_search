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


// stressTest: SORTING_FUNCTION, Integer[], Integer, const long Integer -> Integer
// tests provided sorting function on a random array of length size up to MAX_TESTS times
// if MAX_TESTS is 0, it tests until a failure occurs or the user force closes the program
// if it fails, the errors are logged (see errorLogger function)
int stressTest(SORTING_FUNCTION *sorting_function, int arr[], int size, const unsigned long int MAX_TESTS);

// unlimitedStressTest: SORTING_FUNCTION, Integer[], Integer -> Integer
// calls stressTest with 0 as the last argument.
// it's a special case of stessTest where the algorithm runs until
// a faliure occurs or until the user force closes it
int unlimitedStressTest(SORTING_FUNCTION *sorting_function, int arr[], int size);
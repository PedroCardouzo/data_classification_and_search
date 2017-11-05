// quicksort: Integer[], Integer -> void
// obj.: wrapper for QuickSort so that you can order it
// passing just a pointer to the vector and its size
// Time complexity: Ω(n logn), O(n²), usual: O(n logn)
// Space complexity: O(1) (auxiliary), O(n) total
void quicksort(int arr[], int size);

// QuickSort: Integer[], Integer, Integer -> void
// obj.: recieves a vector and orders it in a crescent order
// Time complexity: Ω(n logn), O(n²), usual: O(n logn)
// Space complexity: O(1) (auxiliary), O(n) total
void QuickSort(int arr[], int low, int high);

// medianIndex: Integer[], Integer, Integer -> Integer
// Obj: calculate the median between three values from an array, these values are at low, high and (high+low)/2, rounded up
// returns the index where the median element is located in the array
int medianIndex(int arr[], int low, int high);

// quicksort: Integer[], Integer -> void
// obj.: orders an array using the classic quicksort algorithm (unoptmized)
void quicksort_old(int arr[], int low, int high);
#define SHRINK_FACTOR 1.3

// combsort: Integer[] Integer -> void
// obj.: recieves an array and sorts it in crescent order
// Time complexity: Ω(n log²n)*, O(n²)
// Space complexity: O(1) (auxiliary), O(n) total
// *it's an approximation as I didn't found any sources on this
void combsort(int arr[], int size);
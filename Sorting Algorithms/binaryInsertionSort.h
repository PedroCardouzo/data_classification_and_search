//binaryInsertionSort:Integer[], Integer -> void
// obj.: recieves a vector and orders it in a crescent order 
// Time complexity: Ω(n), O(n²)
// Space complexity: O(1) (auxiliary), O(n) total
void binaryInsertionSort(int vector[], int size);

// binaryInsertion: Integer[], Integer -> void
// obj.: recieves a vector and makes the swaps to put it in a crescent order
void binaryInsertion(int vector[], int size, int n);

// binarySearch: Integer[], Integer -> Interger
// obj.: returns the position where the number should be located
int binaryResearch(int vector[], int size, int n);
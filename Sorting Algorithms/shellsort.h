#define NUMBER_OF_GAPS 55

// shellsort: Integer[] Integer -> void
// uses shellsort method with a gap sequence discovered by Vaughan Pratt
// Time complexity: Ω(n logn), O(n log²n)* 
// Space complexity: O(1) (auxiliary), O(n) total
// *research shows that Pratt's sequence is one of the best known and provides 
// worst case O(n log²n), although I didn't find any decisive proof
void shellsort(int arr[], int size);
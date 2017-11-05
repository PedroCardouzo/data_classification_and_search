#include "shellsort.h"

extern int comps;
extern int swaps;

// shellsort: Integer[] Integer -> void
// uses shellsort method with a gap sequence discovered by Vaughan Pratt
void shellsort(int arr[], int size){
	int gaps[NUMBER_OF_GAPS] = {3888, 3456, 3072, 2916, 2592, 2304, 2187, 2048, 1944, 1728, 1536, 1458, 1296, 1152, 1024, 972, 864, 768, 729, 648, 576, 512, 486, 432, 384, 324, 288, 256, 243, 216, 192, 162, 144, 128, 108, 96, 81, 72, 64, 54, 48, 36, 32, 27, 24, 18, 16, 12, 9, 8, 6, 4, 3, 2, 1};
	int value, j, gap;
	for(int g_i=0; g_i < NUMBER_OF_GAPS; g_i++)
		for(int i = gaps[g_i]; i < size; i++){

        	gap = gaps[g_i]; // gap recieves the current gap
        	value = arr[i];
			j = i - gap;
			
			comps++;
			while (j >= 0 && value < arr[j]) {
				swaps++;
				arr[j + gap] = arr[j];
				j -= gap;
			}
			swaps++;
			arr[j + gap] = value;
        }
}
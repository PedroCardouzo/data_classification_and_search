#include "combsort.h"

extern char OVERTIME_FLAG;
extern int comps;
extern int swaps;

// combsort: Integer[] Integer -> void
// obj.: recieves an array and sorts it in crescent order
void combsort(int arr[], int size){
	int gap = size-1, temp, sorted = 0;

	while(!sorted){
		if(gap > 1)
			sorted = 0;
		else{
			sorted = 1;
			gap = 1;
		}
		for(int i=gap; i<size; i++){
			comps++;
			if(arr[i] < arr[i-gap]){
				swaps++;
				sorted = 0;
				temp = arr[i-gap];
				arr[i-gap] = arr[i];
				arr[i] = temp;
			}
			if(OVERTIME_FLAG)
				return;
		}
		gap = gap/SHRINK_FACTOR; // default is 1.3
	}
}
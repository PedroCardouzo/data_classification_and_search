#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// size bigger than about 2.000.000 raise segmentation fault 
#define SIZE 2000000

extern int comps;
extern int swaps;

void print(int arr[], int size){
	for(int i=0; i<size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

// mergesort: Integer[], Integer -> void
// obj.: recieves a vector and orders it in a crescent order
// uses memcpy for speed benefits when possible
// Time complexity = Θ(n logn)
void mergesort(int vector[], int size){
	if(size > 1){

		int half_size = size/2;
		
		mergesort(vector, half_size);
		mergesort(&vector[half_size], size-half_size);

		int i=0, j=half_size, k=0;
		int *temp = (int *) malloc(sizeof(int)*size);

		while(i < half_size && j < size){
			swaps++;
			if(vector[i] <= vector[j])
				temp[k++] = vector[i++];
			else
				temp[k++] = vector[j++];
		}

		if(i < half_size) // there are still elements to be transferred in the first half of temp
			memcpy(&temp[k], &vector[i], (half_size-i)*sizeof(int));
		else // there are still elemetns to be transferred in the second half of temp
			memcpy(&temp[k], &vector[j], (size-j)*sizeof(int));

		// now copy all the ordered temp array to the respective position in the vector to be ordered
		memcpy(vector, temp, size*sizeof(int));

		free(temp);
	}
}

void fillDecrescent(int vec[]){
	for(int i=0; i<SIZE; i++)
		vec[i] = SIZE-i;
}

// isCrescent := Integer[], Integer -> Integer
// obj.: checks if an array is sorted in crescent order. If it isn't it logs the errors and the positions which they occurr
// returns the number of errors
int isCrescent(int arr[], int size){
	int errors=0;
	for(int i=1; i<size; i++){
		if(arr[i-1] > arr[i]){
			printf("%d and %d, @ %d and %d\n", arr[i-1], arr[i], i-1, i);
			errors++;
		}
	}
	return errors;
}

int main(){
	int arr[SIZE];
	int counter = 0;
	char errors = 0;
	do{
		for(int a = SIZE-1; a >= 0; a--)
			arr[a] = rand();

			clock_t beg = clock();
			mergesort(arr, SIZE);
			clock_t delta = clock() - beg;
			
			if((errors = isCrescent(arr, SIZE)) == 0)
				counter++;

			printf("sort #%d runtime (new): %lf\n", counter, (double)delta/CLOCKS_PER_SEC);

	}while(errors == 0);
	print(arr, SIZE);
}
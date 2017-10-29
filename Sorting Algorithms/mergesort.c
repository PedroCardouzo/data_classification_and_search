#include <stdlib.h>
#include <string.h>
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 2000000

void print(int arr[], int size){
	for(int i=0; i<size; i++)
		printf("%d ", arr[i]);
	printf("\n");
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

void heapfy(int arr[], int heap_size, int i){
	int larger, aux, is_a_heap=0; 
	while(!is_a_heap){
		larger = i;
		if(2*i+1 < heap_size && arr[larger] < arr[2*i+1])
			larger = 2*i+1;
		if(2*i+2 < heap_size && arr[larger] < arr[2*i+2])
			larger = 2*i+2;
		if(larger != i){
			aux = arr[i];
			arr[i] = arr[larger];
			arr[larger] = aux;
			i = larger;
		}else // if the children are already smaller than the parent
			is_a_heap = 1;
	}	
	
}

// build_heap: Integer[], Integer -> void
// given an array and its length, transform it into a maxheap
void build_heap(int arr[], int heap_size){
	for(int i=heap_size/2; i >= 0; i--)
		heapfy(arr, heap_size, i);
}

// heapExtract: Integer[], Integer* -> void
// recieves a heap and the pointer to the heap_size 
// then takes the first element of the heap and swaps it 
// with the last of the heap, then heap_size is decreased by one
// (now the last element is not in the array anymore) 
// and heapfy is called on the first element to make the array a heap again
void heapExtract(int heap[], int *heap_size){
	
	int aux = heap[0];
	heap[0] = heap[*heap_size-1];
	heap[*heap_size-1] = aux;

	(*heap_size)--; //decreases heap_size by 1;
	heapfy(heap, *heap_size, 0);
}


// heapsort: Integer[], Integer -> void
// recieves an array and its size and returns it ordered in crescenting order
void heapsort(int heap[], int heap_size){
	build_heap(heap, heap_size); // now heap is actually a heap

	while(heap_size > 0) //while a part of the array is still a heap, do heapExtract
		heapExtract(heap, &heap_size);
}

int main(){
	int arr[SIZE];
	int counter = 0;
	char errors = 0;
	do{
		for(int a = SIZE-1; a >= 0; a--)
			arr[a] = rand();

			clock_t beg = clock();
			heapsort(arr, SIZE);
			clock_t delta = clock() - beg;
			
			if((errors = isCrescent(arr, SIZE)) == 0)
				counter++;

			printf("sort #%d runtime (new): %lf\n", counter, (double)delta/CLOCKS_PER_SEC);

	}while(errors == 0);
	print(arr, SIZE);
}
#include "heapsort.h"

// everything marked with //# is for algorithm evaluation (testing number of comparisons and such)
extern int comps; //#
extern int swaps; //#

// heapfy: Integer[], Integer, Integer -> void
// obj.: recieves an array, the heap_size, and the index which 
// we want to make sure that it and its left and right children
//  form a heap and makes it a heap
void heapfy(int arr[], int heap_size, int i){
	int larger, aux, is_a_heap=0; 
	while(!is_a_heap){
		larger = i;

		comps++;
		if(2*i+1 < heap_size && arr[larger] < arr[2*i+1])
			larger = 2*i+1;
		
		comps++;
		if(2*i+2 < heap_size && arr[larger] < arr[2*i+2])
			larger = 2*i+2;
		
		if(larger != i){
			swaps++;
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
	swaps++;
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
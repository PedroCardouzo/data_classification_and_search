#include <stdlib.h>
#include <string.h>
#include "binaryInsertionSort.h"
#include "timsort.h"

extern int comps;
extern int swaps;

int *array; // for debugging purposes

// initializeStack: void -> STACK**
// obj.: this function returns a default initialized STACK** (pointer to a stack that it initializes)
STACK** initializeStack(){
	STACK **stack = (STACK **) malloc(sizeof(STACK *));
	*stack = NULL;
	return stack;
}

// push: Integer*, Integer, STACK** -> void
// obj.: pushes a STACK element with values baseAddr and length into the stack
void push(int *baseAddr, int length, STACK **stack){
	STACK *new = (STACK *) malloc(sizeof(STACK));
	new->baseAddr = baseAddr;
	new->length = length;
	new->next = *stack;
	*stack = new;
}

// destroyStack: STACK** -> void
// obj.: frees allocated memory for the stack
void destroyStack(STACK **stack){
	STACK *aux = *stack, *prev;
	while(aux != NULL){
		prev = aux;
		aux = aux->next;
		free(prev);
	}
}

// getMinrun: Integer -> Integer
// obj.: returns the optimal value of the minrun to an array of size n
int getMinrun(int n){
	/* becomes 1 if the least significant bits contain at least one off bit */
    int r = 0;  
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

// invertVector: Integer[], Integer, Integer -> void
// obj.: recieves an array and its leftmost and rightmost indexes and invert the array order
void invertVector(int vector[], int leftIndex, int rightIndex){
	int aux;
	while(leftIndex < rightIndex){
		swaps++;
		aux = vector[leftIndex];
		vector[leftIndex] = vector[rightIndex];
		vector[rightIndex] = aux;
		leftIndex++;
		rightIndex--;
	}
}

// merge: Integer[], Integer, Integer -> void
// obj.: recieves one vector that has two subvectors that are ordered, and the 
// length of the first and second subvectors. Then it merges them both together
// so we have the full vector ordered
void merge(int vec[], int len1, int len2){
	int i = len1-1, j = len2-1, k = j+len1;
	int *aux = (int *) malloc(len2*sizeof(int)); // len2 should be the smaller one, if they aren't equals
	memcpy(aux, vec+len1, len2*sizeof(int));
	
	while(i >= 0 && j >= 0){
		comps++;
		swaps += k%2; // because each 2 attribuitions will count as one swap
		if(vec[i] >= aux[j])
			vec[k--] = vec[i--];
		else
			vec[k--] = aux[j--];
	}
	swaps++;
	if(j >= 0)
		memcpy(vec, aux, (j+1)*sizeof(int));
}

// mergeStacks: STACK** -> void
// takes a pass throught the stack merging each pair of stacks so that
// we are left with half (or half+1 if odd number of stacks) at the end
// of each iteration. It keeps doing it until all stacks are merged
void mergeStacks(STACK **stack){
	
	if(*stack == NULL || (*stack)->next == NULL)
		return;

	STACK *a = *stack, *b = a->next;
	*stack = (STACK *) malloc(sizeof(STACK));
	STACK *aux = *stack;
	while(a && b){
		merge(b->baseAddr, b->length, a->length);
		
		aux->baseAddr = b->baseAddr;
		aux->length = a->length + b->length;
		aux->next = b->next;

		free(a);
		
		free(b);
		
		a = aux->next;
		if(a != NULL && a->next){
			b = a->next;
			aux->next = (STACK *) malloc(sizeof(STACK));
			aux = aux->next;
		}else
			a = NULL; // flag to exit
	}
}

// timsort: Integer[] Integer -> void
// obj.: sorts a vector using timsort sorting algorithm
void timsort(int vector[], int size){
	int minrun = getMinrun(size), runsize;
	int stack_size = 0;
	// create stack and push runs into it
	STACK **stack = initializeStack();
	int pos = 0, init;

	while(pos < size){
		pos++;
		init = pos-1;
		comps++;
		if(pos < size && vector[init] > vector[pos]){

			while(vector[pos-1] > vector[pos]){ pos++; comps++;}
			invertVector(vector, init, pos-1);

		}else{
		
			while(pos < size && vector[pos-1] <= vector[pos]){ pos++; comps++;}
				
		}
		runsize = pos-init;
		stack_size++;

		// make sure that each run is at least minrun size, unless it is the last one (this also includes case where whole vector is smaller than minrun)
		if(size-init <= minrun){
		
			binaryInsertionSort(vector+init, size-init); // marker
			push(vector+init, size-init, stack);
			break;
		
		}else if(runsize >= minrun || pos >= size)
			push(vector+init, pos-init, stack);
		
		else{
			pos -= runsize;
			binaryInsertionSort(vector+init, minrun);
			pos += minrun;
			push(vector+init, minrun, stack);
		}
	}

	// stack is ready with partitions
	while(stack_size > 1){
		mergeStacks(stack);
		stack_size = (stack_size+1)/2;
	}
	// // merge the runs acording to the timsort rules
	// while(stack != NULL && stack->next != NULL)
	// 	STACK *X, *Y, *Z;
	// 	X = *stack;
	// 	Y = X->next;
	// 	Z = Y->next;

	// 	if(Z->length > X->length + Y->length && Y->length > X->length){
	// 		//

	// 	}else{
	// 		if(X->length <= Z->length){
	// 			// merge X and Y
	// 		}else{
	// 			// merge Z and Y
	// 		}
	// 	}

	destroyStack(stack);
	free(stack);
}
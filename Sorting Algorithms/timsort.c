#include <stdlib.h>
#include <string.h>

typedef struct STRUCT_STACK STACK;
struct STRUCT_STACK{
	int *baseAddr;
	int length;
	STACK *next;
};

int *array; // for debugging purposes


STACK** initializeStack(){
	STACK **stack = (STACK **) malloc(sizeof(STACK *));
	*stack = NULL;
	return stack;
}

void push(int *baseAddr, int length, STACK **stack){
	STACK *new = (STACK *) malloc(sizeof(STACK));
	new->baseAddr = baseAddr;
	new->length = length;
	new->next = *stack;
	*stack = new;
}


void destroyStack(STACK **stack){
	STACK *aux = *stack, *prev;
	while(aux != NULL){
		prev = aux;
		aux = aux->next;
		free(prev);
	}
}

int getMinrun(int n){
	/* becomes 1 if the least significant bits contain at least one off bit */
    int r = 0;  
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}


void invertVector(int vector[], int leftIndex, int rightIndex){
	int aux;
	while(leftIndex < rightIndex){
		aux = vector[leftIndex];
		vector[leftIndex] = vector[rightIndex];
		vector[rightIndex] = aux;
		leftIndex++;
		rightIndex--;
	}
}

// A binary search based function to find the position
// where item should be inserted in a[low..high]
int binarySearch(int a[], int item, int low, int high)
{
    if (high <= low)
        return (item > a[low])?  (low + 1): low;
 
    int mid = (low + high)/2;
 
    if(item == a[mid])
        return mid+1;
 
    if(item > a[mid])
        return binarySearch(a, item, mid+1, high);
    return binarySearch(a, item, low, mid-1);
}
 
// Function to sort an array a[] of size 'n'
void insertionSort(int a[], int n)
{
    int i, loc, j, k, selected;
 
    for (i = 1; i < n; ++i)
    {
        j = i - 1;
        selected = a[i];
 
        // find location where selected sould be inseretd
        loc = binarySearch(a, selected, 0, j);
 
        // Move all elements after location to create space
        while (j >= loc)
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = selected;
    }
}

void merge(int vec[], int len1, int len2){
	int i = len1-1, j = len2-1, k = j+len1;
	int *aux = (int *) malloc(len2*sizeof(int)); // len2 should be the smaller one, if they aren't equals
	memcpy(aux, vec+len1, len2*sizeof(int));
	
	while(i >= 0 && j >= 0){
		if(vec[i] >= aux[j])
			vec[k--] = vec[i--];
		else
			vec[k--] = aux[j--];
	}
	if(j >= 0)
		memcpy(vec, aux, (j+1)*sizeof(int));
}



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



void timsort(int vector[], int size){
	int minrun = getMinrun(size), runsize;
	int stack_size = 0;
	// create stack and push runs into it
	STACK **stack = initializeStack();
	int pos = 0, init;

	while(pos < size){
		pos++;
		init = pos-1;
		if(pos < size && vector[init] > vector[pos]){

			while(vector[pos-1] > vector[pos]) pos++;
			invertVector(vector, init, pos-1);
		
		}else{
		
			while(pos < size && vector[pos-1] <= vector[pos]) pos++;
				
		}
		runsize = pos-init;
		stack_size++;

		// make sure that each run is at least minrun size, unless it is the last one (this also includes case where whole vector is smaller than minrun)
		if(size-init <= minrun){
		
			insertionSort(vector+init, size-init);
			push(vector+init, size-init, stack);
			break;
		
		}else if(runsize >= minrun || pos >= size)
			push(vector+init, pos-init, stack);
		
		else{
			pos -= runsize;
			insertionSort(vector+init, minrun);
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
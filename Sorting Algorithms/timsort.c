#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// size bigger than about 2.000.000 raise segmentation fault 
#define SIZE 2000000

typedef struct STRUCT_STACK STACK;
struct STRUCT_STACK{
	int *baseAddr;
	int length;
	STACK *next;
};


int *array;
char gc;
int global_ss;
void debug(char n){
	if(global_ss == 256){
		printf("IM HERE = %d\n", n);
	}
}

void prints(STACK *s){
	int *arr = s->baseAddr;
	int i = 0;
	
	printf("arr[0] = %d\n", arr[0]);

	while(array != arr) if(i++ > SIZE) break;
	
	printf("position = %d\n", i);
	for(i; i<SIZE; i++)
		printf("%d ", arr[i]);

}

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

void printRun(int arr[], int size){
	printf("\nPrinting Run:\n");
	for(int i=0; i<size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void printRuns(STACK *stack){
	while(stack != NULL){
		printRun(stack->baseAddr, stack->length);
		stack = stack->next;
	}
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


void print(int arr[], int size){
	for(int i=0; i<size; i++)
		printf("%d ", arr[i]);
	printf("\n");
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

int belongs(int arr[]){
	// printf("array[SIZE-1]-array = %lld  ==  %lld\n", (unsigned long long int)(array+SIZE-1-array), (unsigned long long int)SIZE-1);
	return arr-array <= SIZE-1; 
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

int validateStack(STACK *stack){
	while(stack != NULL){
		if(belongs(stack->baseAddr) == 0) return 0;
		stack = stack->next;
	}
	return 1;
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

// int main(){

// 	int arr[SIZE];

// 	for(int i=0; i < SIZE/2; i++)
// 		arr[i] = i;

// 	for(int i=SIZE/2; i < SIZE; i++)
// 		arr[i] = i;

// 	timsort(arr, SIZE);

// 	// print(arr, SIZE);

// 	if(isCrescent(arr, SIZE))
// 		printf("Okay\n");
// 	else
// 		printf("ERROR\n");
// }
int main(){
	int arr[SIZE];
	array = arr;
	int counter = 0;
	char errors = 0;
	do{
		for(int a = SIZE-1; a >= 0; a--)
			arr[a] = rand();

		clock_t beg = clock();
		timsort(arr, SIZE);
		clock_t delta = clock() - beg;
		
		if((errors = isCrescent(arr, SIZE)) == 0)
			counter++;
		else
			printf("UNORDERED\n");

		printf("sort #%d runtime (new): %lf\n", counter, (double)delta/CLOCKS_PER_SEC);

	}while(errors == 0);
	// print(arr, SIZE);
}
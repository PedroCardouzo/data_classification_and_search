#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// size bigger than about 2.000.000 raise segmentation fault 
#define SIZE_ARR 2000000

// print := Integer[] -> void
// Obj.: prints the whole array into the screen
void print(int arr[]){
	for(int i=0; i<SIZE_ARR; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

// print := Integer[] -> void
// Obj.: prints the whole array into the screen
void printhl(int arr[], int lo, int hi){
	for(int i=lo; i<=hi; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

// medianIndex := Integer[], Integer, Integer -> Integer
// Obj: calculate the median between three values from an array, these values are at low, high and (high+low)/2, rounded up
// returns the index where the median element is located in the array
int medianIndex(int arr[], int low, int high){
	int mid = (high+low+1)/2; // equivalent to ceil(high+low)/2);
	int temp[3] = {low, mid, high}, aux;

	for(int repeat =1; repeat >= 0; repeat--) // do 2 times
		for(int i=1; i<3; i++){
			if(arr[temp[i-1]] > arr[temp[i]]){
				aux = temp[i-1];
				temp[i-1] = temp[i];
				temp[i] = aux;
			}
		}

	return temp[1];
}



// QuickSort := Integer[], Integer, Integer -> void
// obj.: recieves a vector and orders it in a crescent order
void QuickSort(int arr[], int low, int high){
	int pivotIndex = medianIndex(arr, low, high);
	int pivot = arr[pivotIndex];

	int i=low, j=high, temp;
	


	if(high-low > 0){
		// printf("pivot = %d, low = %d, high = %d \n", pivot, low, high);
		// printf("in: ");
		// printhl(arr, low, high);
		while(i <= j){

			if(arr[i] <= pivot)
				i++;
			else{

				while(arr[j] > pivot && i<=j) j--;

				if(i < j){
					temp = arr[j];
					arr[j] = arr[i];
					arr[i] = temp;
					i++;
				}
			}
		}
		
		int middlePartitionEnd = i-1;
		i = low; j = middlePartitionEnd;
		while(i <= j){
			
			if(arr[i] == pivot){
				while(arr[j] == pivot && i <= j) j--;

				if(i < j){
					arr[i] = arr[j];
					arr[j] = pivot;
					i++;
				}
			}else
				i++;	
		}
		QuickSort(arr, low, i-1);
		QuickSort(arr, middlePartitionEnd+1, high);
	}
}

// quicksort := Integer[], Integer -> void
// obj.: wrapper for QuickSort so that you can order it
// passing just a pointer to the vector and its size
void quicksort(int arr[], int size){
	QuickSort(arr, 0, size-1);
}

// Unoptimized classic quicksort
void quicksort_old(int arr[], int low, int high){
	int pivot = arr[high];

	int i=low, j=high, temp;

	if(high-low > 0){
		while(i != j){
			
			if(arr[i] <= pivot)
				i++;
			else{
				while(arr[j] > pivot && i!=j)
					j--;
				if(arr[j] <= pivot){
					temp = arr[j];
					arr[j] = arr[i];
					arr[i] = temp;
					i++;
				}
			}
		}

		quicksort_old(arr, low, i-1);
		quicksort_old(arr, i, high);
	}
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

//* // this tests stability of the algorithm. It keeps looping until an error occurs (the array isn't crescently ordered)
int main(){
	int arr[SIZE_ARR];
	int counter = 0;
	char errors = 0;
	do{
		for(int a = SIZE_ARR-1; a >= 0; a--)
			arr[a] = rand()%256;

			clock_t beg = clock();
			quicksort(arr, 0, SIZE_ARR-1);
			clock_t delta = clock() - beg;
			
			if((errors = isCrescent(arr, SIZE_ARR)) == 0)
				counter++;

			printf("sort #%d runtime (new): %lf\n", counter, (double)delta/CLOCKS_PER_SEC);

	}while(errors == 0);
	print(arr);
}
//*/

/*
int main(){

	static int arr[SIZE_ARR];
	static int arr2[SIZE_ARR];

	int errors;
	srand(time(NULL));

//* // rand
	for(int a = SIZE_ARR-1; a >= 0; a--)
		arr[a] = rand();

	for(int a = SIZE_ARR-1; a >= 0; a--)
		arr2[a] = rand();
//*/

/* // crescente/decrescente
	for(int a = SIZE_ARR-1; a >= 0; a--)
		arr[a] = SIZE_ARR-a;

	for(int a = SIZE_ARR-1; a >= 0; a--)
		arr2[a] = SIZE_ARR-a;
//*/

/*/ // constante
	for(int a = SIZE_ARR-1; a >= 0; a--)
		arr[a] = 1520452;

	for(int a = SIZE_ARR-1; a >= 0; a--)
		arr2[a] = 1520452;

	arr[SIZE_ARR/3] = 1520451;
	arr[2*SIZE_ARR/3] = 15204;
	arr2[SIZE_ARR/3] = 1520451;
	arr2[2*SIZE_ARR/3] = 15204;
//*/ 
/*
	printf("Lists are %d elements long\n\n", SIZE_ARR);

	printf("Sorting Start\n");
	clock_t beg = clock();
	quicksort(arr, 0, SIZE_ARR-1);
	clock_t end = clock();
	
	double time = (double) (end-beg)/CLOCKS_PER_SEC;
	printf("sort runtime (new): %lf\n", time);

	
	if((errors = isCrescent(arr, SIZE_ARR)) == 0)
		printf("Array is in crescent order\n");
	else
		printf("Array is NOT in crescent order\n");
	


	printf("Sorting Start\n");
	beg = clock();
	quicksort_old(arr2, 0, SIZE_ARR-1);
	end = clock();
	
	time = (double) (end-beg)/CLOCKS_PER_SEC;
	printf("sort runtime (old): %lf\n", time);

	if((errors = isCrescent(arr, SIZE_ARR)) == 0)
		printf("Array is in crescent order\n");
	else
		printf("Array is NOT in crescent order\n");

	return 0;
}
//*/
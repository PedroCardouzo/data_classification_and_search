// everything marked with //# is for algorithm evaluation (testing number of comparisons and such)
extern int comps; //#
extern int swaps; //#

// medianIndex: Integer[], Integer, Integer -> Integer
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



// QuickSort: Integer[], Integer, Integer -> void
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

// quicksort: Integer[], Integer -> void
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
#include "binaryInsertionSort.h"

extern int comps;
extern int swaps;

//binaryInsertionSort:Integer[], Integer -> void
// obj.: recieves a vector and orders it in a crescent order 
void binaryInsertionSort(int vector[], int size){
	int i;

	for(i=0; i<size; i++){
		binaryInsertion(vector, vector[i], i);
	}

}


// binaryInsertion: Integer[], Integer -> void
// obj.: recieves a vector and makes the swaps to put it in a crescent order
void binaryInsertion(int vector[], int n, int size){
	int i;
	int temp;
	int start = binarySearch(vector, n, 0, size);

	for(i= start;i<size;i++){
		swaps++;
        temp = n;
		n = vector[i];
		vector[i] = temp;
	}
    
    swaps++;
    vector[i]= n;
}


// binarySearch: Integer[], Integer -> Interger
// obj.: returns the position where the number should be located
int binarySearch(int vector[], int n, int start, int end){
    int i = (start + end)/2;

    if(end == start){
        return end;
    }else{

    	comps++;

        if(n > vector[i]){
            if(i == start){
                i++;
            }
            binarySearch(vector, n, i, end);
        }else{
            if(i == end){
                i++;
            }
            binarySearch(vector, n, start, i);
        }
    }
}

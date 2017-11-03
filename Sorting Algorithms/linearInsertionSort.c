#include "linearInsertionSort.h"

extern char OVERTIME_FLAG;
extern int comps;
extern int swaps;


//linearInsertionSort:Integer[], Integer -> void
// obj.: recieves a vector and orders it in a crescent order 
void linearInsertionSort(int vector[], int size){
	
	for(int i=0; i<size; i++){
		insertion(vector, vector[i], i);
	}

}

//insertion:Integer[], Integer -> void
// obj.: recieves a vector inside another vector and inserts it in a crescent order 
void insertion(int vector[], int n, int size){
	int i;
	int temp;

	for(i=0;i<size;i++){
		comps++;
		if(vector[i]> n){
			swaps++;
			temp = n;
			n = vector[i];
			vector[i] = temp;
		}
		if(OVERTIME_FLAG)
			return;
	}

	swaps++;
    vector[i]= n;
}
/*
//linearInsertionSort:Integer[], Integer -> void
// obj.: recieves a vector and orders it in a crescent order 
void linearInsertionSort(int vector[], int size){
	
	for(int i=1; i<size; i++)
		insertion(vector, vector[i], i+1);

}

//insertion:Integer[], Integer -> void
// obj.: recieves a vector inside another vector and inserts it in a crescent order 
void insertion(int vector[], int n, int size){
	int i;
	int temp;

	for(i=size-2; i >= 0 && vector[i] > n;i++){
		comps++;
		if(vector[i]> n){
			swaps++;
			temp = n;
			n = vector[i];
			vector[i] = temp;
		}
		if(OVERTIME_FLAG)
			return;
	}
}*/
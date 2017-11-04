#include "linearInsertionSort.h"

extern char OVERTIME_FLAG;
extern int comps;
extern int swaps;

//linearInsertionSort:Integer[], Integer -> void
// obj.: recieves a vector and orders it in a crescent order 
void linearInsertionSort(int vector[], int size){

	for(int i=1; i<size; i++)
		insertion(vector, vector[i], i+1);

}

//insertion:Integer[], Integer -> void
// obj.: recieves a vector inside another vector and inserts it in a crescent order 
void insertion(int vector[], int n, int size){
	int i = size-1;
	int temp;

	comps++;
	while(vector[i] < vector[i-1] && i > 0){
		comps++;
		swaps++;
		temp = vector[i-1];
		vector[i-1] = vector[i];
		vector[i] = temp;
		i--;
		if(OVERTIME_FLAG)
			return;
	}
}
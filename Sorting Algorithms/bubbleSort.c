#include "bubbleSort.h"

extern char OVERTIME_FLAG;
extern int comps;
extern int swaps;

// bubbleSort: Integer[], Integer -> void
// obj.: recieves a vector and orders it in a crescent order 
void bubbleSort(int vector[], int size){
    int noSwaps = 0, temp;

    while(noSwaps == 0){
        noSwaps = 1;
        for(int i=0; i<size; i++){
            comps++;
            if(vector[i] > vector[i+1]){
                swaps++;
                temp = vector[i];
                vector[i] = vector[i+1];
                vector[i+1] = temp;
                noSwaps = 0;
            }
            if(OVERTIME_FLAG)
                return;
        }
    }
}
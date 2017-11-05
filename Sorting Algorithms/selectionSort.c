#include "selectionSort.h"

extern char OVERTIME_FLAG;
extern int comps;
extern int swaps;

//selectionSort:Integer[], Integer -> void
// obj.: recieves a vector and orders it in a crescent order 
// Time complexity: θ(n²)
// Space complexity: O(1) (auxiliary), O(n) total
void selectionSort(int vector[], int size){
    int i;
    int j;
    int min;
    int temp;

    for(i=0; i<size; i++){
            min = vector[i];
        for(j=i+1; j<size; j++){
            comps++;
            if(vector[j]<min){
                swaps++;
                temp = min;
                min = vector[j];
                vector[j] = temp;
                vector[i] = min;
            }
            if(OVERTIME_FLAG)
                return;
        }
    }
}

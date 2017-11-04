#include "bubbleSort.h"

extern char OVERTIME_FLAG;
extern int comps;
extern int swaps;

// binaryInsertionSort: Integer[], Integer -> void
// obj.: recieves a vector and orders it in a crescent order 
void bubbleSort(int vector[], int size){
    int flag;

    while(flag == 0){
        flag = pass(vector, size);
    }
}

// pass: Integer[], Integer -> Interger
// obj.: does a pass through the vector and swaps every consecutive elements which are unordered
// returns 1 if no swaps where made (vector is ordered), 0 otherwise 
int pass(int vector[], int size){
    int i;
    int temp;
    int flag = 1;

    for(i=0; i<size; i++){
        comps++;
        if(vector[i] > vector[i+1]){
            swaps++;
            temp = vector[i];
            vector[i] = vector[i+1];
            vector[i+1] = temp;
            flag = 0;
        }
        if(OVERTIME_FLAG)
            return 1;
    }

    return flag;
}

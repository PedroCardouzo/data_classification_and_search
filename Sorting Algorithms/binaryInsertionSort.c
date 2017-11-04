#include "binaryInsertionSort.h"

extern char OVERTIME_FLAG;
extern int comps;
extern int swaps;

//binaryInsertionSort:Integer[], Integer -> void
// obj.: recieves a vector and orders it in a crescent order 
void binaryInsertionSort(int vector[], int size){

    for(int i=1; i<size && !OVERTIME_FLAG; i++){
        if(vector[i]< vector[i-1])
            binaryInsertion(vector, i+1, vector[i]);
    }
}


// binaryInsertion: Integer[], Integer -> void
// obj.: recieves a vector and makes the swaps to put it in a crescent order
void binaryInsertion(int vector[], int size, int n){
    int temp;
    int start = binaryResearch(vector, size, n);

    for(int i= start;i<size && !OVERTIME_FLAG;i++){
        swaps++;
        temp = n;
        n = vector[i];
        vector[i] = temp;
    }
}


// binarySearch: Integer[], Integer -> Interger
// obj.: returns the position where the number should be located
int binaryResearch(int vector[], int size, int n){
    int i, start=0, end = size-1;

    while(end!= start){
        i = (start + end)/2;
        comps++;

        if(n > vector[i]){
            if(i == start)
                i++;
            
            start = i;
        }else{
            if(i == end)
                i++;
            
            end = i;
        }
    }

    return end;
}
#include "linearSearch.h"

extern int swaps;
extern int comps;

// linearSearch: Integer[], Integer , Integer -> Integer 
// given an array, its length and a number search for the number and return it's index
// in case the number isn't found, returns -1
int linearSearch(int vector[], int size, int search){
    int i;

    for(i=0;i<size;i++){
    	comps++;
        if(vector[i] == search){
            return i;
        }
    }

    return -1;
}

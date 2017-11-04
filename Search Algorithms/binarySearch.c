extern int swaps;
extern int comps;

// binarySearch: Integer[], Integer, Integer, Integer -> Integer 
// given an array, a number and the first and last index, search for the number and return it's position
// in case the number isn't found, returns -1
int binarySearch(int vector[], int size, int value){
    int mid, left = 0, right = size-1;

    while(right >= left){
        mid = (left+right)/2;
        comps++;
        if(value < vector[mid])
            right = mid-1;

        else if(value > vector[mid]){
            comps++;
            left = mid+1;
        }else // then n is equal to vector[mid]
            return mid;
    }

    return -1;

}

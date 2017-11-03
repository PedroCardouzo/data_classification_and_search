extern int comps;
extern int swaps;

//binaryInsertionSort:Integer[], Integer -> void
// obj.: recieves a vector and orders it in a crescent order 
void bubbleSort(int vector[], int size){
    int flag;

    while(flag == 0){
        flag = pass(vector, size);
    }
}

//binaryInsertionSort:Integer[], Integer -> Interger
// obj.: recieves a vector and orders it in a crescent order 
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
    }

    return flag;
}

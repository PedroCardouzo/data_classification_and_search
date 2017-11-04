// heapfy: Integer[], Integer, Integer -> void
// obj.: recieves an array, the heap_size, and the index which 
// we want to make sure that it and its left and right children
//  form a heap and makes it a heap
void heapfy(int arr[], int heap_size, int i);

// build_heap: Integer[], Integer -> void
// given an array and its length, transform it into a maxheap
void build_heap(int arr[], int heap_size);

// heapExtract: Integer[], Integer* -> void
// recieves a heap and the pointer to the heap_size 
// then takes the first element of the heap and swaps it 
// with the last of the heap, then heap_size is decreased by one
// (now the last element is not in the array anymore) 
// and heapfy is called on the first element to make the array a heap again
void heapExtract(int heap[], int *heap_size);

// heapsort: Integer[], Integer -> void
// recieves an array and its size and returns it ordered in crescenting order
void heapsort(int heap[], int heap_size);
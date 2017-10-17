STACK** initializeStack();
void push(int *baseAddr, int length, STACK **stack);
void destroyStack(STACK **stack);
int getMinrun(int n);
void invertVector(int vector[], int leftIndex, int rightIndex);
void merge(int vec[], int len1, int len2);
void mergeStacks(STACK **stack);
void timsort(int vector[], int size);

int binarySearch(int a[], int item, int low, int high);
void insertionSort(int a[], int n);
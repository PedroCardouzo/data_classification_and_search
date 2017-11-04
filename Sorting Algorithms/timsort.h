typedef struct STRUCT_STACK STACK;
struct STRUCT_STACK{
	int *baseAddr;
	int length;
	STACK *next;
};

// initializeStack: void -> STACK**
// obj.: this function returns a default initialized STACK** (pointer to a stack that it initializes)
STACK** initializeStack();

// push: Integer*, Integer, STACK** -> void
// obj.: pushes a STACK element with values baseAddr and length into the stack
void push(int *baseAddr, int length, STACK **stack);

// destroyStack: STACK** -> void
// obj.: frees allocated memory for the stack
void destroyStack(STACK **stack);

// getMinrun: Integer -> Integer
// obj.: returns the optimal value of the minrun to an array of size n
int getMinrun(int n);

// invertVector: Integer[], Integer, Integer -> void
// obj.: recieves an array and its leftmost and rightmost indexes and invert the array order
void invertVector(int vector[], int leftIndex, int rightIndex);

// merge: Integer[], Integer, Integer -> void
// obj.: recieves one vector that has two subvectors that are ordered, and the 
// length of the first and second subvectors. Then it merges them both together
// so we have the full vector ordered
void merge(int vec[], int len1, int len2);

// mergeStacks: STACK** -> void
// takes a pass throught the stack merging each pair of stacks so that
// we are left with half (or half+1 if odd number of stacks) at the end
// of each iteration. It keeps doing it until all stacks are merged
void mergeStacks(STACK **stack);

// timsort: Integer[] Integer -> void
// obj.: sorts a vector using timsort sorting algorithm
void timsort(int vector[], int size);
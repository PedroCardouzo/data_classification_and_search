
//timsort exclusives

int validateStack(STACK *stack){
	while(stack != NULL){
		if(belongs(stack->baseAddr) == 0) return 0;
		stack = stack->next;
	}
	return 1;
}

int belongs(int arr[]){
	return arr-array <= SIZE-1; 
}

void debug(char n){
	if(global_ss == 256){
		printf("IM HERE = %d\n", n);
	}
}

void prints(STACK *s){
	int *arr = s->baseAddr;
	int i = 0;
	
	printf("arr[0] = %d\n", arr[0]);

	while(array != arr) if(i++ > SIZE) break;
	
	printf("position = %d\n", i);
	for(i; i<SIZE; i++)
		printf("%d ", arr[i]);

}

void printRun(int arr[], int size){
	printf("\nPrinting Run:\n");
	for(int i=0; i<size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void printRuns(STACK *stack){
	while(stack != NULL){
		printRun(stack->baseAddr, stack->length);
		stack = stack->next;
	}
}
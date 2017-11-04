############################# Makefile ##########################

#builds all the .o files needed
all: linearInsertionSort.o binaryInsertionSort.o selectionSort.o bubbleSort.o combsort.o shellsort.o quicksort.o mergesort.o heapsort.o timsort.o util.o

util.o: util.c util.h
		gcc -c util.c

linearInsertionSort.o: linearInsertionSort.c linearInsertionSort.h
		gcc -c linearInsertionSort.c

binaryInsertionSort.o: binaryInsertionSort.c binaryInsertionSort.h
		gcc -c binaryInsertionSort.c

selectionSort.o: selectionSort.c selectionSort.h
		gcc -c selectionSort.c

bubbleSort.o: bubbleSort.c bubbleSort.h
		gcc -c bubbleSort.c

combsort.o: combsort.c combsort.h
		gcc -c combsort.c

shellsort.o: shellsort.c shellsort.h
		gcc -c shellsort.c

quicksort.o: quicksort.c quicksort.h
		gcc -c quicksort.c

mergesort.o: mergesort.c mergesort.h
		gcc -c mergesort.c
		
heapsort.o: heapsort.c heapsort.h
		gcc -c heapsort.c

timsort.o: timsort.c timsort.h binaryInsertionSort.h 
		gcc -c timsort.c

clean:
		rm -rf *.o
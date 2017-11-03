#Para escrever comentários ##
############################# Makefile ##########################
all: main

main: SortingAlgorithms main.o main.h
		gcc -o exec Sorting\ Algorithms/util.o Sorting\ Algorithms/binaryInsertionSort.o Sorting\ Algorithms/linearInsertionSort.o Sorting\ Algorithms/selectionSort.o Sorting\ Algorithms/bubbleSort.o Sorting\ Algorithms/quicksort.o Sorting\ Algorithms/mergesort.o Sorting\ Algorithms/heapsort.o Sorting\ Algorithms/timsort.o main.o
		@echo # for blank line
		@echo "build was successful!"

main.o: main.c Sorting\ Algorithms/util.h Sorting\ Algorithms/binaryInsertionSort.h Sorting\ Algorithms/linearInsertionSort.h Sorting\ Algorithms/selectionSort.h Sorting\ Algorithms/bubbleSort.h Sorting\ Algorithms/quicksort.h Sorting\ Algorithms/mergesort.h Sorting\ Algorithms/heapsort.h Sorting\ Algorithms/timsort.h 
		gcc -c main.c

SortingAlgorithms: 
		+$(MAKE) -C Sorting\ Algorithms

clean:
		rm -rf main.o

cleanall:
		rm -rf main.o exec ./Sorting\ Algorithms/*.o

cleanr: cleanall
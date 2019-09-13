#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <thread>

#define DEPTH 4

void mergeSort(int* array, int length);
void mergeSortThreaded(int* array, int length);
void mergeSortThreadedInner(int* array, int leftIndex, int rightIndex, int length, int depth);
void mergeSortInner(int* array, int leftIndex, int rightIndex, int length);
void fillArray(int* array, int length);
void printArray(int* array, int length);
int randInt(int min, int max);
void copyArray(int* source, int* target, int length);
int checkIfEqual(int* left, int* right, int length);

void copyArray(int* source, int* target, int length) {
	int i;

	for(i = 0; i < length; i++) {
		target[i] = source[i];
	}
}

int checkIfEqual(int* left, int* right, int length) {
	int i;

	for(i = 0; i < length; i++) {
		if(left[i] != right[i])
			return 0;
	}

	return 1;
}

int main(int argc, char const *argv[])
{
	int length;
	int* array;
	int* arrayCopy;
	int result;
	clock_t begin, end;
	double elapsed;
	double normalTime = 0;
	double threadTime = 0;
	srand(time(0));

	if(argc == 1) {
		printf("Usage: mergeSort <number>\n");
		return 1;
	}
	else {
		length = atoi(argv[1]);
		array = new int[length];
		arrayCopy = new int[length];
	}

	for(int i = 0; i < 100; i++) {
		fillArray(array, length);
		copyArray(array, arrayCopy, length);

		begin = clock();
		mergeSort(array, length);
		end = clock();
		elapsed = (double) (end - begin) / CLOCKS_PER_SEC;
		normalTime += elapsed;
		//printf("Mergesort normal took: %lf seconds.\n", elapsed);

		begin = clock();
		mergeSortThreaded(arrayCopy, length);
		end = clock();
		elapsed = (double) (end - begin) / CLOCKS_PER_SEC;
		threadTime += elapsed;
		//printf("Mergesort threaded took: %lf seconds.\n", elapsed);

		result = checkIfEqual(array, arrayCopy, length);
		
	}

	printf("Total normal time: %lf\tTotal threaded time: %lf\n", normalTime, threadTime);

	delete array;
	delete arrayCopy;
	return 0;
}

int randInt(int min, int max) {
	int diff = max - min;
	int random = rand() % diff;
	random += min;

	return random;
}

void fillArray(int* array, int length) {
	int i;

	for(i = 0; i < length; i++) {
		array[i] = randInt(0, 100);
	}
}

void printArray(int* array, int length) {
	int i;

	for(i = 0; i < length; i++) {
		if(i == 0)
			printf("%d", array[i]);
		else
			printf(", %d", array[i]);
	}

	printf("\n");
}

void mergeSort(int* array, int length) {
	mergeSortInner(array, 0, length - 1, length);
}

void mergeSortInner(int* array, int indexLeft, int indexRight, int length) {
	int l1, r1, l2, r2, c1, c2;
	int left, right, arrayPos;
	int tempArr[length];

	if(length == 1 || length == 0)
		return;

	if(length % 2 == 0) {
		l1 = indexLeft;
		r1 = indexLeft + ((length / 2) - 1);
		l2 = r1 + 1;
		r2 = indexRight;
		c1 = (r1 - l1) + 1;
		c2 = c1;
	}
	else {
		l1 = indexLeft;
		r1 = indexLeft + ((length / 2));
		l2 = r1 + 1;
		r2 = indexRight;
		c1 = (r1 - l1) + 1;
		c2 = length - c1;
	}

	/*
	printf("\nL1: %d R1: %d\tL2: %d R2: %d\tC1: %d C2: %d\n", l1, r1, l2, r2, c1, c2);
	printf("%s\n", "Printing Left: ");
	for(left = l1; left <= r1; left++) {
		printf("%d, ", array[left]);
	}
	printf("\n%s\n", "Printing Right: ");
	for(right = l2; right <= r2; right++) {
		printf("%d, ", array[right]);
	}
	printf("\n\n");
	*/
	mergeSortInner(array, l1, r1, c1);
	mergeSortInner(array, l2, r2, c2);


	arrayPos = 0;
	while(arrayPos < length) {
		if(l1 > r1) {
			tempArr[arrayPos] = array[l2];
			l2++;
		}
		else if(l2 > r2) {
			tempArr[arrayPos] = array[l1];
			l1++;
		}
		else {
			left = array[l1];
			right = array[l2];
			if(left <= right) {
				tempArr[arrayPos] = left;
				l1++;
			}
			else {
				tempArr[arrayPos] = right;
				l2++;
			}
		}

		arrayPos++;
	}

	arrayPos = 0;
	while(arrayPos < length && indexLeft <= indexRight) {
		array[indexLeft] = tempArr[arrayPos];
		arrayPos++;
		indexLeft++;
	}
}

void mergeSortThreaded(int* array, int length) {
	mergeSortThreadedInner(array, 0, length - 1, length, 0);
}

void mergeSortThreadedInner(int* array, int indexLeft, int indexRight, int length, int depth) {
	int l1, r1, l2, r2, c1, c2;
	int left, right, arrayPos;
	int tempArr[length];

	if(length == 1 || length == 0)
		return;

	if(length % 2 == 0) {
		l1 = indexLeft;
		r1 = indexLeft + ((length / 2) - 1);
		l2 = r1 + 1;
		r2 = indexRight;
		c1 = (r1 - l1) + 1;
		c2 = c1;
	}
	else {
		l1 = indexLeft;
		r1 = indexLeft + ((length / 2));
		l2 = r1 + 1;
		r2 = indexRight;
		c1 = (r1 - l1) + 1;
		c2 = length - c1;
	}

	if(depth <= DEPTH) {
		std::thread first(mergeSortThreadedInner, array, l1, r1, c1, depth + 1);
		std::thread second (mergeSortThreadedInner, array, l2, r2, c2, depth + 1);
		first.join();
		second.join();
	}
	else {
		mergeSortInner(array, l1, r1, c1);
		mergeSortInner(array, l2, r2, c2);
	}

	arrayPos = 0;
	while(arrayPos < length) {
		if(l1 > r1) {
			tempArr[arrayPos] = array[l2];
			l2++;
		}
		else if(l2 > r2) {
			tempArr[arrayPos] = array[l1];
			l1++;
		}
		else {
			left = array[l1];
			right = array[l2];
			if(left <= right) {
				tempArr[arrayPos] = left;
				l1++;
			}
			else {
				tempArr[arrayPos] = right;
				l2++;
			}
		}

		arrayPos++;
	}

	arrayPos = 0;
	while(arrayPos < length && indexLeft <= indexRight) {
		array[indexLeft] = tempArr[arrayPos];
		arrayPos++;
		indexLeft++;
	}
}
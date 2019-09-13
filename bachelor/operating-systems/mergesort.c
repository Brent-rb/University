#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>

#define DEPTH 4

void mergeSort(int* array, int length);
void mergeSortThreaded(int* array, int length);
void* mergeSortThreadedInner(void* args);
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

	if(argc == 1) {
		printf("Usage: mergeSort <number>\n");
		return 1;
	}
	else {
		length = atoi(argv[1]);
		array = malloc(sizeof(int) * length);
		arrayCopy = malloc(sizeof(int) * length);
	}
	srand(time(0));
	fillArray(array, length);
	copyArray(array, arrayCopy, length);

	begin = clock();
	mergeSort(array, length);
	end = clock();
	elapsed = (double) (end - begin) / CLOCKS_PER_SEC;

	printf("Mergesort normal took: %lf seconds.\n", elapsed);

	begin = clock();
	mergeSortThreaded(arrayCopy, length);
	end = clock();
	elapsed = (double) (end - begin) / CLOCKS_PER_SEC;

	printf("Mergesort threaded took: %lf seconds.\n", elapsed);

	result = checkIfEqual(array, arrayCopy, length);

	if(result == 1) {
		printf("Arrays are equal.\n");
	}
	else {
		printf("Arrays were different.\n");
		printArray(array, length);
		printArray(arrayCopy, length);
	}

	free(array);
	free(arrayCopy);
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

	//Bereken de indexes voor 'sub arrays'
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

	//Mergesort linker deel array
	mergeSortInner(array, l1, r1, c1);
	//Mergesort rechter deel array;
	mergeSortInner(array, l2, r2, c2);


	arrayPos = 0;

	//Join de arrays, dit doen we in tempArray omdat we anders problemen gaan krijgen
	while(arrayPos < length) {
		//Als we de linker array helemaal gehad hebben, uit rechter array halen
		if(l1 > r1) {
			tempArr[arrayPos] = array[l2];
			l2++;
		}
		//Vice versa
		else if(l2 > r2) {
			tempArr[arrayPos] = array[l1];
			l1++;
		}
		//Kijken welk van de 2 kleiner is en dit in de array stoppen
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

	//Subarray naar orginele array
	arrayPos = 0;
	while(arrayPos < length && indexLeft <= indexRight) {
		array[indexLeft] = tempArr[arrayPos];
		arrayPos++;
		indexLeft++;
	}
}

void mergeSortThreaded(int* array, int length) {
	//Parameters naar array voor dan als void pointer mee te kunnen geven
	int* args[5];
	int left = 0, right = length - 1, depth = 0;
	args[0] = array;
	args[1] = &left;
	args[2] = &right;
	args[3] = &length;
	args[4] = &depth;
	mergeSortThreadedInner(args);
}

void* mergeSortThreadedInner(void* args) {
	//Pointer omzetting zzzzzzz
	int** arrayPtr = (int**) args;
	int* array = arrayPtr[0];
	int indexLeft = *arrayPtr[1];
	int indexRight = *arrayPtr[2];
	int length = *arrayPtr[3]; 
	int depth = *arrayPtr[4];
	//Depth nodig als variabele voor als pointer mee te kunne geven 
	int depth2 = depth + 1;
	//Einde pointer omzettings
	int l1, r1, l2, r2, c1, c2;
	int left, right, arrayPos;
	int tempArr[length];
	//Array aanmaken voor mee te geven aan child calls
	int* leftArgs[5];
	int* rightArgs[5];
	//Child threads aanmaken
	pthread_t leftThread, rightThread;
	//resultaat van thread starten
	int leftSucces = 0, rightSucces = 0;

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

	//Child array correct vullen
	leftArgs[0] = array;
	leftArgs[1] = &l1;
	leftArgs[2] = &r1;
	leftArgs[3] = &c1;
	leftArgs[4] = &depth2;
	rightArgs[0] = array;
	rightArgs[1] = &l2;
	rightArgs[2] = &r2;
	rightArgs[3] = &c2;
	rightArgs[4] = &depth2;

	//Op bepaalde diepte stoppen met threads aan te maken
	if(depth <= DEPTH) {
		//printf("Creating thread\n");
		if(pthread_create(&leftThread, NULL, mergeSortThreadedInner, leftArgs) == 0)
			leftSucces = 1;
		if(pthread_create(&rightThread, NULL, mergeSortThreadedInner, rightArgs) == 0)
			rightSucces = 1;
		//Als thread aanmaken mislukt it, uitvoeren in deze thread
		if(leftSucces == 0) {
			mergeSortThreadedInner(leftArgs);
		}
		if(rightSucces == 0) {
			mergeSortThreadedInner(rightArgs);
		}
		//Zo niet wachten op child threads
		if(leftSucces == 1)
			pthread_join(leftThread, NULL);
		if(rightSucces == 1)
			pthread_join(rightThread, NULL);
	}
	//We zitten te diep, geen thread meer aanmaken maar uitvoeren in deze thread
	else {
		mergeSortInner(array, l1, r1, c1);
		mergeSortInner(array, l2, r2, c2);
	}

	//Arrays mergen
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

	//Subarray naar orginele array
	arrayPos = 0;
	while(arrayPos < length && indexLeft <= indexRight) {
		array[indexLeft] = tempArr[arrayPos];
		arrayPos++;
		indexLeft++;
	}
}
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


void* consume(void* args);
void* produce(void* args);
int getRand(int min, int max);

#define MAX 20

int count;
int inCounter;
int outCounter;
int buffer[MAX];

int main(int argc, char const *argv[])
{
	pthread_t p1, p2;
	srand(time(NULL));
	pthread_create(&p1, NULL, consume, NULL);
	pthread_create(&p2, NULL, produce, NULL);
	while(1);
	return 0;
}

void* produce(void* args) {
	printf("Produce started.\n");
	int randNum;
	int sleepTime;

	while(1) {
		randNum = getRand(0, 100);
		sleepTime = getRand(10000, 100000);

		while(count == MAX);

		buffer[inCounter] = randNum;
		inCounter = (inCounter + 1) % MAX;
		count++;
		usleep(sleepTime);
	}
}

void* consume(void* args) {
	printf("Consume started.\n");
	int number;
	int sleepTime;

	while(1) {
		while(count == 0);
		number = buffer[outCounter];
		sleepTime = getRand(100, 100000);
		printf("Count: %d\tConsumed: %d\n", count, number);
		outCounter = (outCounter + 1) % MAX;
		count--;
		usleep(sleepTime);
	}

}

int getRand(int min, int max) {
	int diff = max - min;
	int random = rand() % diff;
	random += min;

	return random;
}
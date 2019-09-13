#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

#define BUFFERSIZE 20
#define SAFE //Comment out this define to make it thread unsafe.

int buffer[BUFFERSIZE];
sem_t full, empty, mutex;
int counter;

void* produce(void* args);
void* consume(void* args);



int main(int argc, char const *argv[])
{
	srand(time(0));
	pthread_t ent1, ent2;
	void* result;
	counter = 0;
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, BUFFERSIZE);
	sem_init(&mutex, 0, 1);

	pthread_create(&ent1, NULL, produce, NULL);
	pthread_create(&ent2, NULL, consume, NULL);

	pthread_join(ent1, &result);
	pthread_join(ent2, &result);
	return 0;
}

void* produce(void* args) {
	int random;
	int i = 0;

	do {
		random = rand() % 100;
	#ifdef SAFE
		//Wait for empty spot
		sem_wait(&empty);
		//Wait for mutex -> no dirty read on counter
		sem_wait(&mutex);
	#endif
		//Add produced item
		buffer[counter] = random;
	#ifdef SAFE
		//Singal mutex we're done
		sem_post(&mutex);
		//Signal we added an item
		sem_post(&full);
	#endif
		i++;
	} while(i < 10000);
}

void* consume(void* args) {
	int number;
	int i = 0;

	do {
		//Wait till an item has been added
	#ifdef SAFE
		sem_wait(&full);
		//Wait for mutex -> no dirty read / write on counter
		sem_wait(&mutex);
	#endif
		//Consume item
		number = buffer[counter];
		//Increase counter here while in mutex
		counter++;
		counter %= BUFFERSIZE;
	#ifdef SAFE
		//Singal we're done
		sem_post(&mutex);
		//Signal an empty spot have come avaible
		sem_post(&empty);
	#endif
		//Do something with consumed item
		printf("Consumed %d\n", number);
		i++;
	} while(i < 10000);
}
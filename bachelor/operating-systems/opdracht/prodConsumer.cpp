#define BUFFERSIZE 5
#include "library.h"

void init();
void run();
void* consume(void* args);
void* produce(void* args);
int buffer[BUFFERSIZE];
int bufferIndex;

int main(int argc, char const *argv[])
{
	init();
	run();
	return 0;
}

void init() {
	//Init the random seed and buffer
	srand(time(NULL));
	for(bufferIndex = 0; bufferIndex < BUFFERSIZE; bufferIndex++) {
		buffer[bufferIndex] = 0;
	}

	bufferIndex = 0;
}

void run() {
	//Allocate thread
	usthread_t threads[2];

	//Init
	usthread_init();
	//Create threads
	usthread_spawn(&threads[0], produce, 0);
	usthread_spawn(&threads[1], consume, 0);
	//Run first thread
	usthread_yield();
	//Wait for threads
	usthread_join(&threads[0]);
	usthread_join(&threads[1]);
}

void* produce(void* args) {
	int random;
	int i;
	for(i = 0; i < 10000; i++) {
		//Get random number
		random = rand();
		//Print (for visual output)
		std::cout << "Produced: " << random << std::endl;
		//Put in buffer
		buffer[bufferIndex] = random;
		//switch to consume/main (main will switch to consume)
		usthread_yield();
	}

	return 0;
}

void* consume(void* args) {
	int result;
	int i;

	for(i = 0; i < 10000; i++) {
		//Get output from producer
		result = buffer[bufferIndex];
		//Print result
		std::cout << "Consumed: " << result << std::endl;
		//Increment index no need to watch out for race conditions etc because we do not use real threads
		bufferIndex++;
		bufferIndex %= BUFFERSIZE;
		//Switch to produce
		usthread_yield();
	}

	return 0;
}



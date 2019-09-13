#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <list>
#include <stdlib.h>


void* fac(void *arg) {
	int* ptr = (int*) arg;
	int number = (*ptr);
	int i;
	unsigned long long total = 1;

	for(i = 1; i <= number; i++) {
		total *= i;
		//Anders is het algoritme veel te fucking snel.
		usleep(100000);
	}

	printf("Faculteit van %d is %llu\n", number, total);
	//Geheugen vrijmaken
	delete ptr;
}

int main(int argc, char *argv[]) {
	/*#############*\
	#     DEEL 1    #
	\*#############*/

	int number;
	int* passNumber;
	char buffer[128];
	pthread_t tempThread;
	std::list<pthread_t> threadList;

	do {
		printf("Enter a positive number to calculate the faculty, enter a negative number to quit.\n");

		fgets(buffer, 128, stdin);
		number = atoi(buffer);
		passNumber = new int;
		*passNumber = number;

		if(number <= 0)
			break;
		else {
			tempThread = pthread_t();
			pthread_create(&tempThread, NULL, fac, passNumber);
			threadList.push_back(tempThread);
		}
	} while(true);

	/*#############*\
	#     DEEL 2    #
	\*#############*/
	printf("Waiting for threads to finish before we quit...\n");
	std::list<pthread_t>::const_iterator it;
	for(it = threadList.begin(); it != threadList.end(); it++) {
		pthread_join((*it), NULL);
	}
	printf("Threads are doing. Quiting.\n");

	return 0;
}
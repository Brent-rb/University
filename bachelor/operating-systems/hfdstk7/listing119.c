#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

double bedragA, bedragB;
sem_t safetrans;

void* bankier1Safe(void* arg);
void* bankier2Safe(void* arg);
void* bankier1Unsafe(void* arg);
void* bankier2Unsafe(void* arg);
void initSafe();
void initUnsafe();

int main(int argc, char const *argv[])
{
	srand(time(0));
	if(argc == 2) {
		if(strcmp(argv[1], "safe") == 0)
			initSafe();
		else if(strcmp(argv[1], "unsafe") == 0)
			initUnsafe();
		else 
			printf("Unkown option: %s\n", argv[1]);
	}
	return 0;
}

/*
Deze functie gaf geen errors bij helgrind.
Deze functie gaf geen errors bij DRD.
*/
void initSafe() {
	pthread_t ent1, ent2;
	void* tResult;
	bedragA = 100;
	bedragB = 100;

	if(sem_init(&safetrans, 0, 0)) {
		printf("Kan de sempahore niet aanmaken.\n");
		return;
	}
	if((pthread_create(&ent1, NULL, bankier1Safe, NULL) || pthread_create(&ent2, NULL, bankier2Safe, NULL)) != 0) {
		printf("Kan threads niet aanmaken\n");
		return;
	}

	printf("Voer transacties uit.\n");
	sem_post(&safetrans);

	if((pthread_join(ent1, &tResult) || pthread_join(ent2, &tResult)) != 0) {
		printf("Kan de threads niet samenvoegen.\n");
		return;
	}

	printf("Rekening A = %g, Rekening B = %g\n", bedragA, bedragB);
}

/*
Deze functie gaf 98 errors bij helgrind, voornamelijke (of mogelijke alle errors) race condities. In functies bankier1Unsafe en bankier2Unsafe.
Deze functie gaf 116 errors bij DRD, voornamelijk conflicting loads en conflicting stores in functies bankier1Unsafe en bankier2Unsafe.
*/
void initUnsafe() {
	pthread_t ent1, ent2;
	void* tResult;
	bedragA = 100;
	bedragB = 100;

	if(sem_init(&safetrans, 0, 0)) {
		printf("Kan de sempahore niet aanmaken.\n");
		return;
	}
	if((pthread_create(&ent1, NULL, bankier1Unsafe, NULL) || pthread_create(&ent2, NULL, bankier2Unsafe, NULL)) != 0) {
		printf("Kan threads niet aanmaken\n");
		return;
	}

	printf("Voer transacties uit.\n");
	sem_post(&safetrans);

	if((pthread_join(ent1, &tResult) || pthread_join(ent2, &tResult)) != 0) {
		printf("Kan de threads niet samenvoegen.\n");
		return;
	}

	printf("Rekening A = %g, Rekening B = %g\n", bedragA, bedragB);
}

void* bankier1Safe(void* arg) {
	int i = 0, teken = 1;
	double a, b, verhoging;

	for(i = 0; i < 10; i++) {
		sleep(1.1);
		//Wait until a sem_post occurs (a free sem slot occurs)
		sem_wait(&safetrans);
		//Save locally
		a = bedragA;
		b = bedragB;
		//Random verhoging krijgen
		verhoging = teken * (rand() % 100);
		teken = -teken;
		a += verhoging;
		b += verhoging;
		//Changes pushen
		bedragA = a;
		bedragB = b;
		//Notify we are done
		printf("Bankier 1: Verhoogt met %g euro\n", verhoging);
		printf("Rekening A = %g, Rekening B = %g\n", bedragA, bedragB);
		sem_post(&safetrans);
	}
}

void* bankier2Safe(void* arg) {
	int i = 0, teken = 1;
	double a, b, verplaatsing;

	for(i = 0; i < 10; i++) {
		sleep(1.2);
		//Wait until a sem_post occurs (a free sem slot occurs)
		sem_wait(&safetrans);
		//Save locally
		a = bedragA;
		b = bedragB;
		//Random verhoging krijgen
		verplaatsing = teken * (rand() % 100);
		teken = -teken;
		a += verplaatsing;
		b -= verplaatsing;
		//Changes pushen
		bedragA = a;
		bedragB = b;
		//Notify we are done
		printf("Bankier 2: %g euro verplaatst van A naar B\n", verplaatsing);
		printf("Rekening A = %g, Rekening B = %g\n", bedragA, bedragB);
		sem_post(&safetrans);
	}	
}

void* bankier1Unsafe(void* arg) {
	int i = 0, teken = 1;
	double a, b, verhoging;

	for(i = 0; i < 10; i++) {
		sleep(1.1);
		//Wait until a sem_post occurs (a free sem slot occurs)
		//sem_wait(&safetrans);
		//Save locally
		a = bedragA;
		b = bedragB;
		//Random verhoging krijgen
		verhoging = teken * (rand() % 100);
		teken = -teken;
		a += verhoging;
		b += verhoging;
		//Changes pushen
		bedragA = a;
		bedragB = b;
		//Notify we are done
		//sem_post(&safetrans);
		printf("Bankier 1: Verhoogt met %g euro\n", verhoging);
		printf("Rekening A = %g, Rekening B = %g\n", bedragA, bedragB);
	}
}

void* bankier2Unsafe(void* arg) {
	int i = 0, teken = 1;
	double a, b, verplaatsing;

	for(i = 0; i < 10; i++) {
		sleep(1.2);
		//Wait until a sem_post occurs (a free sem slot occurs)
		//sem_wait(&safetrans);
		//Save locally
		a = bedragA;
		b = bedragB;
		//Random verhoging krijgen
		verplaatsing = teken * (rand() % 100);
		teken = -teken;
		a += verplaatsing;
		b -= verplaatsing;
		//Changes pushen
		bedragA = a;
		bedragB = b;
		//Notify we are done
		//sem_post(&safetrans);
		printf("Bankier 2: %g euro verplaatst van A naar B\n", verplaatsing);
		printf("Rekening A = %g, Rekening B = %g\n", bedragA, bedragB);
	}	
}
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

struct Param {
	char c;
};

void *threadTest(void *p) {
	int i;
	struct Param *param = (struct Param*) p;

	for(i = 0; i < 1000; ++i)
		printf("[%c]\n", param->c);
	return NULL;
}

int main(int argc, char *argv[]) {
	int i;
	pthread_t t1, t2, t3;
	struct Param p1, p2, p3;
	p1.c = 'b';
	p2.c = 'c';
	p3.c = 'd';

	if(pthread_create(&t1, NULL, threadTest, &p1) || pthread_create(&t2, NULL, threadTest, &p2) || pthread_create(&t3, NULL, threadTest, &p3)) {
		printf("Fout bij aanmaken thread!\n");
		return 1;
	}

	for(i = 0; i < 250; ++i)
		printf("a\n");

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

	return 0;
}
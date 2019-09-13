#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
	int id;
	printf("Process 2.\n");
	sleep(1);
	execl("./h3_1", "h3_1", argv, NULL);
	

	return 0;
}
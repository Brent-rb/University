#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
	int id;
	printf("Process 1.\n");
	//sleep(1);
	execl("./h3_2", "h3_2", argv, NULL);
	

	return 0;
}
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(int argc, const char* argv[]) {
	int n = 0;
	pid_t id;
	int i = 0, f1, f2, fn, status;

	if(argc == 2) {
		n = atoi(argv[1]);
		id = fork();

		if(id == 0) {
			f1 = 0;
			f2 = 1;
			fn = 0;
			printf("0, 1");
			for(i = 2; i <= n; i++) {
				fn = f1 + f2;
				f1 = f2;
				f2 = fn;
				printf(", %d", fn);
			}
			printf("\n");
		}
		else {
			waitpid(id, &status, WSTOPPED);
		}
	}

	return 0;
}
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	execlp("echo", "echo", "test", (char*) NULL);
	return 0;
}
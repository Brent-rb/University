#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	char* const args[1] = {"rechts"};
	execvp("./rechts", args);
	return 0;
}
#include <fcntl.h>

int main() {
	int fd = open("/tmp/strtest", O_RDWR | O_CREAT | O_APPEND);
	char buffer[10] = "*********";

	if(fd < 0)
		return -1;
	else
		write(fd, (void*) buffer, 9);

	close(fd);
	return 0;
}